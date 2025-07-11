/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:13:52 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 18:23:04 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	send_position_if_changed(t_game *game, double *last_posx,
		double *last_posy)
{
	char	buffer[64];
	ssize_t	bytes_sent;
	double	current_x;
	double	current_y;

	pthread_mutex_lock(&game->server.mutex);
	current_x = _other()->posx;
	current_y = _other()->posy;
	pthread_mutex_unlock(&game->server.mutex);
	if (current_x != *last_posx || current_y != *last_posy)
	{
		snprintf(buffer, sizeof(buffer), "%.6f|%.6f", current_x, current_y);
		bytes_sent = write(game->sock, buffer, strlen(buffer));
		if (bytes_sent < 0)
			return (-1);
		*last_posx = current_x;
		*last_posy = current_y;
	}
	return (0);
}

static int	should_end(t_game *game)
{
	int	end_flag;

	pthread_mutex_lock(&game->server.mutex);
	end_flag = (_other()->end || _other()->end2);
	pthread_mutex_unlock(&game->server.mutex);
	return (end_flag);
}

static void	*join_write(void *arg)
{
	t_game	*game;
	double	last_posx;
	double	last_posy;

	game = (t_game *)arg;
	last_posx = -1.0;
	last_posy = -1.0;
	while (1)
	{
		if (should_end(game))
			break ;
		if (send_position_if_changed(game, &last_posx, &last_posy) < 0)
		{
			pthread_mutex_lock(&game->server.mutex);
			if (!_other()->end2)
				_other()->end2 = 1;
			pthread_mutex_unlock(&game->server.mutex);
			break ;
		}
		usleep(10000);
	}
	close(game->sock);
	return (NULL);
}

static void	receive_map_and_start_threads(t_game *game)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_received;

	ft_bzero(buffer, BUFFER_SIZE);
	bytes_received = read(game->sock, buffer, BUFFER_SIZE - 1);
	if (bytes_received <= 0)
		destroy_game_failure(game, "Failed to read map from server");
	buffer[bytes_received] = '\0';
	game->map = ft_split(buffer, '|');
	if (!game->map || !game->map[0])
		destroy_game_failure(game, "Failed to parse map from server");
	pthread_create(&_other()->join_reade, NULL, join_read, game);
	pthread_create(&_other()->join_writee, NULL, join_write, game);
}

void	join_server(t_game *game, char **argv)
{
	connect_to_server(game, argv);
	receive_map_and_start_threads(game);
}
