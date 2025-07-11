/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:37:29 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 18:20:21 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	read_from_client(int client_fd, char *buffer)
{
	fd_set			readfds;
	struct timeval	timeout;
	int				bytes_received;

	FD_ZERO(&readfds);
	FD_SET(client_fd, &readfds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;
	if (select(client_fd + 1, &readfds, NULL, NULL, &timeout) <= 0)
		return (0);
	if (!FD_ISSET(client_fd, &readfds))
		return (0);
	bytes_received = read(client_fd, buffer, BUFFER_SIZE - 1);
	if (bytes_received <= 0)
		return (-1);
	buffer[bytes_received] = '\0';
	return (bytes_received);
}

static void	update_player_position(t_game *game, char *buffer)
{
	char	**pos;
	t_other	*other;

	other = _other();
	pos = ft_split(buffer, '|');
	if (!pos || !pos[0] || !pos[1])
	{
		if (pos)
			free_split(pos);
		return ;
	}
	pthread_mutex_lock(&game->server.mutex);
	other->otherposx = strtod(pos[0], NULL);
	other->otherposy = strtod(pos[1], NULL);
	pthread_mutex_unlock(&game->server.mutex);
	free_split(pos);
}

static int	handle_client_read(t_game *game, char *buffer)
{
	int	bytes_read;

	bytes_read = read_from_client(game->server.client_fd, buffer);
	if (bytes_read == 0)
		return (0);
	if (bytes_read < 0)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (!_other()->end2)
			_other()->end2 = 1;
		pthread_mutex_unlock(&game->server.mutex);
		return (-1);
	}
	if (ft_strcmp(buffer, "END") == 0)
	{
		pthread_mutex_lock(&game->server.mutex);
		_other()->end2 = 1;
		pthread_mutex_unlock(&game->server.mutex);
		return (-1);
	}
	update_player_position(game, buffer);
	return (1);
}

void	*read_thread_func(void *arg)
{
	t_game	*game;
	char	buffer[BUFFER_SIZE];
	int		ret;

	game = (t_game *)arg;
	while (1)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end || _other()->end2)
		{
			pthread_mutex_unlock(&game->server.mutex);
			break ;
		}
		pthread_mutex_unlock(&game->server.mutex);
		ret = handle_client_read(game, buffer);
		if (ret == 0)
			continue ;
		if (ret < 0)
			break ;
	}
	return (NULL);
}

void	send_map(int client_fd, t_game *game)
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
