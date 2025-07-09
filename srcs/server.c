/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:09:05 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/09 16:14:37 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	create_server_socket(t_game *game)
{
	int	server_fd;
	int	opt;

	opt = 1;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		destroy_game_failure(game, "Failed to create socket");
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		destroy_game_failure(game, "setsockopt failed");
	return (server_fd);
}

static void	bind_and_listen(int server_fd, struct sockaddr_in *server_addr,
		t_game *game)
{
	if (bind(server_fd, (struct sockaddr *)server_addr,
			sizeof(*server_addr)) < 0)
		destroy_game_failure(game, "Failed to bind socket");
	if (listen(server_fd, 1) < 0)
		destroy_game_failure(game, "Failed to listen on socket");
}

void	init_server(t_game *game)
{
	game->server.addr_len = sizeof(game->server.client_addr);
	game->server.server_fd = create_server_socket(game);
	ft_bzero(&game->server.server_addr, sizeof(game->server.server_addr));
	game->server.server_addr.sin_family = AF_INET;
	game->server.server_addr.sin_port = htons(PORT);
	game->server.server_addr.sin_addr.s_addr = INADDR_ANY;
	bind_and_listen(game->server.server_fd, &game->server.server_addr, game);
	printf("Server waiting on %d...\n", PORT);
}

void	close_server(t_game *game)
{
	if (!game->host)
		return ;
	close(game->server.client_fd);
	close(game->server.server_fd);
	printf("Server stopped.\n");
	pthread_mutex_destroy(&game->server.mutex);
}
