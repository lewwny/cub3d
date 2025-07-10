/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:29:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 12:01:09 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_client(int client_fd, t_game *game, double *old_posx,
		double *old_posy)
{
	char	buffer[BUFFER_SIZE];

	ft_bzero(buffer, BUFFER_SIZE);
	pthread_mutex_lock(&game->server.mutex);
	if (*old_posx != _other()->posx || *old_posy != _other()->posy)
	{
		snprintf(buffer, BUFFER_SIZE, "%.2f|%.2f",
			game->player.posx, game->player.posy);
		write(client_fd, buffer, ft_strlen(buffer));
		*old_posx = _other()->posx;
		*old_posy = _other()->posy;
	}
	pthread_mutex_unlock(&game->server.mutex);
}

static void	send_map(int client_fd, t_game *game)
{
	int		i;
	char	buffer[BUFFER_SIZE];

	i = 0;
	ft_bzero(buffer, BUFFER_SIZE);
	while (game->map[i])
	{
		ft_strcat(buffer, game->map[i]);
		ft_strcat(buffer, "|");
		i++;
	}
	write(client_fd, buffer, ft_strlen(buffer));
	free_oldmap(game->map, &game->garbage);
}

static void	*read_thread_func(void *arg)
{
	t_game			*game;
	int				bytes_received;
	char			buffer[BUFFER_SIZE];
	char			**pos;
	fd_set			readfds;
	struct timeval	timeout;

	game = (t_game *)arg;
	while (1)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end)
		{
			pthread_mutex_unlock(&game->server.mutex);
			break ;
		}
		pthread_mutex_unlock(&game->server.mutex);
		FD_ZERO(&readfds);
		FD_SET(game->server.client_fd, &readfds);
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;
		if (select(game->server.client_fd + 1, &readfds, NULL, NULL,
				&timeout) <= 0)
			continue ;
		if (!FD_ISSET(game->server.client_fd, &readfds))
			continue ;
		bytes_received = read(game->server.client_fd, buffer, BUFFER_SIZE - 1);
		if (bytes_received <= 0)
			break ;
		buffer[bytes_received] = '\0';
		pos = ft_split(buffer, '|');
		if (!pos || !pos[0])
			destroy_game_failure(game,
				"Failed to parse position data from client");
		pthread_mutex_lock(&game->server.mutex);
		_other()->otherposx = strtod(pos[0], NULL);
		_other()->otherposy = strtod(pos[1], NULL);
		free_split(pos);
		printf("Player position updated: (%.2f, %.2f)\n",
			_other()->otherposx, _other()->otherposy);
		pthread_mutex_unlock(&game->server.mutex);
	}
	return (NULL);
}

void	*server_thread(void *data)
{
	t_game			*game;
	double			old_posx;
	double			old_posy;
	fd_set			readfds;
	struct timeval	timeout;

	game = (t_game *)data;
	while (1)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end)
		{
			pthread_mutex_unlock(&game->server.mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&game->server.mutex);
		FD_ZERO(&readfds);
		FD_SET(game->server.server_fd, &readfds);
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;
		if (select(game->server.server_fd + 1, &readfds, NULL, NULL,
				&timeout) > 0)
		{
			if (FD_ISSET(game->server.server_fd, &readfds))
				break ;
		}
	}
	game->server.client_fd = accept(game->server.server_fd,
			(struct sockaddr *)&game->server.client_addr,
			&game->server.addr_len);
	if (game->server.client_fd < 0)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end)
		{
			pthread_mutex_unlock(&game->server.mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&game->server.mutex);
		destroy_game_failure(game, "Failed to accept client connection");
	}
	printf("Client connected.\n");
	pthread_mutex_lock(&game->server.mutex);
	old_posx = _other()->posx;
	old_posy = _other()->posy;
	pthread_mutex_unlock(&game->server.mutex);
	send_map(game->server.client_fd, game);
	pthread_create(&_other()->read_thread, NULL, read_thread_func, game);
	while (1)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end)
		{
			pthread_mutex_unlock(&game->server.mutex);
			break ;
		}
		pthread_mutex_unlock(&game->server.mutex);
		handle_client(game->server.client_fd, game, &old_posx, &old_posy);
		usleep(100000);
	}
	return (NULL);
}
