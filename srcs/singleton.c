/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:33:28 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/09 16:14:51 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_other	*_other(void)
{
	static t_other			other;
	static int				initialized = 0;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (!initialized)
	{
		pthread_mutex_lock(&mutex);
		if (!initialized)
		{
			other.otherposx = 0.0;
			other.otherposy = 0.0;
			other.posx = 0.0;
			other.posy = 0.0;
			initialized = 1;
		}
		pthread_mutex_unlock(&mutex);
	}
	return (&other);
}
