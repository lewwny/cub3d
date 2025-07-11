/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:34:01 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 09:18:18 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	read_position_from_server(t_game *game, char *buffer)
{
	fd_set			readfds;
	struct timeval	timeout;
	int				bytes_received;

	FD_ZERO(&readfds);
	FD_SET(game->sock, &readfds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;
	if (select(game->sock + 1, &readfds, NULL, NULL, &timeout) <= 0)
		return (0);
	if (!FD_ISSET(game->sock, &readfds))
		return (0);
	bytes_received = read(game->sock, buffer, BUFFER_SIZE - 1);
	if (bytes_received <= 0)
		return (-1);
	buffer[bytes_received] = '\0';
	return (bytes_received);
}

static void	update_other_player_position(t_game *game, char *buffer)
{
	char	**pos;
	t_other	*other;

	other = _other();
	pos = ft_split(buffer, '|');
	if (!pos || !pos[0])
		destroy_game_failure(game, "Failed to parse position data from server");
	pthread_mutex_lock(&game->server.mutex);
	other->otherposx = strtod(pos[0], NULL);
	other->otherposy = strtod(pos[1], NULL);
	free_split(pos);
	pthread_mutex_unlock(&game->server.mutex);
}

void	*join_read(void *arg)
{
	t_game			*game;
	char			buffer[BUFFER_SIZE];
	int				ret;

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
		ret = read_position_from_server(game, buffer);
		if (ret == 0)
			continue ;
		if (ret < 0)
			break ;
		update_other_player_position(game, buffer);
	}
	close(game->sock);
	return (NULL);
}
