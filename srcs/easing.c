/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:22:04 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/07 17:23:20 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	ease_linear(double t)
{
	return (t);
}

double	ease_out_quad(double t)
{
	return (t * (2 - t));
}

double	ease_in_quad(double t)
{
	return (t * t);
}

double	ease_in_out_cubic(double t)
{
	if (t < 0.5)
		return (4 * t * t * t);
	else
		return (1 - pow(-2 * t + 2, 3) / 2);
}
