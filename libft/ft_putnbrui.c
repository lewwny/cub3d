/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:43:08 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/10 11:15:34 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrui(int fd, size_t n)
{
	size_t	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putnbrui(fd, n / 10);
		count += ft_putnbrui(fd, n % 10);
	}
	else
		count += ft_putchari(fd, n + 48);
	return (count);
}
