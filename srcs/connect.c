/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:22:08 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 18:22:20 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	connect_to_server(t_game *game, char **argv)
{
	struct sockaddr_in	server_addr;

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
		destroy_game_failure(game, "Invalid address/ Address not supported");
	if (connect(game->sock, (struct sockaddr *)&server_addr,
			sizeof(server_addr)) < 0)
		destroy_game_failure(game, "Connection failed");
	printf("Connected to server %s:%s\n", argv[2], argv[3]);
}
