/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:13:52 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 12:27:57 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	*join_read(void *arg)
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
		FD_SET(game->sock, &readfds);
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;
		if (select(game->sock + 1, &readfds, NULL, NULL, &timeout) <= 0)
			continue ;
		if (!FD_ISSET(game->sock, &readfds))
			continue ;
		bytes_received = read(game->sock, buffer, BUFFER_SIZE - 1);
		if (bytes_received <= 0)
			break ;
		buffer[bytes_received] = '\0';
		pos = ft_split(buffer, '|');
		if (!pos || !pos[0])
			destroy_game_failure(game,
				"Failed to parse position data from server");
		pthread_mutex_lock(&game->server.mutex);
		_other()->otherposx = strtod(pos[0], NULL);
		_other()->otherposy = strtod(pos[1], NULL);
		free_split(pos);
		printf("Player position updated: (%.2f, %.2f)\n",
			_other()->otherposx, _other()->otherposy);
		pthread_mutex_unlock(&game->server.mutex);
	}
	close(game->sock);
	return (NULL);
}

static void	*join_write(void *arg)
{
	t_game	*game;
	double	last_posx;
	double	last_posy;
	char	buffer[64];
	ssize_t	bytes_sent;

	game = (t_game *)arg;
	last_posx = -1.0;
	last_posy = -1.0;
	while (1)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->posx != last_posx || _other()->posy != last_posy)
		{
			snprintf(buffer, sizeof(buffer), "%.6f|%.6f",
				_other()->posx, _other()->posy);
			bytes_sent = write(game->sock, buffer, strlen(buffer));
			if (bytes_sent < 0)
			{
				pthread_mutex_unlock(&game->server.mutex);
				break;
			}
			last_posx = _other()->posx;
			last_posy = _other()->posy;
		}
		if (_other()->end)
		{
			pthread_mutex_unlock(&game->server.mutex);
			break;
		}
		pthread_mutex_unlock(&game->server.mutex);
		usleep(10000);
	}
	close(game->sock);
	return (NULL);
}

void	join_server(t_game *game, char **argv)
{
	struct sockaddr_in	server_addr;
	char				buffer[BUFFER_SIZE];
	ssize_t				bytes_received;

	game->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (game->sock < 0)
		destroy_game_failure(game, "Failed to create socket");
	ft_bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(ft_atoi(argv[3]));
	printf("Connecting to server %s:%s\n", argv[2], argv[3]);
	if (ft_strcmp(argv[2], "localhost") == 0)
		server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	else if (inet_pton(AF_INET, argv[2], &server_addr.sin_addr) <= 0)
		destroy_game_failure(game,
			"Invalid address/ Address not supported");
	if (connect(game->sock, (struct sockaddr *)&server_addr,
			sizeof(server_addr)) < 0)
		destroy_game_failure(game, "Connection failed");
	printf("Connected to server %s:%s\n", argv[2], argv[3]);
	ft_bzero(buffer, BUFFER_SIZE);
	bytes_received = read(game->sock, buffer, BUFFER_SIZE - 1);
	if (bytes_received <= 0)
		destroy_game_failure(game, "Failed to read map from server");
	buffer[bytes_received] = '\0';
	game->map = ft_split(buffer, '|');
	if (!game->map || !game->map[0])
		destroy_game_failure(game, "Failed to parse map from server");
	printf("Map received successfully! Starting position thread...\n");
	pthread_create(&_other()->join_reade, NULL, join_read, game);
	pthread_create(&_other()->join_writee, NULL, join_write, game);
}
