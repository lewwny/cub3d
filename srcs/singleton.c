/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:33:28 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 18:04:08 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_other	*_other(void)
{
	static t_other			other;
	static int				initialized = 0;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	if (!initialized)
	{
		other.otherposx = 0.0;
		other.otherposy = 0.0;
		other.posx = 0.0;
		other.posy = 0.0;
		other.end = 0;
		other.connected = 0;
		other.lifebar_state = 0;
		other.end2 = 0;
		initialized = 1;
	}
	pthread_mutex_unlock(&mutex);
	return (&other);
}
