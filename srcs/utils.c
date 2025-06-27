/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:38:47 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/27 14:41:34 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(char **map)
{
	int	i;

	if (!map)
	{
		ft_dprintf(2, "Error: Map is NULL.\n");
		return ;
	}
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}
