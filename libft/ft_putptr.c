/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:35:19 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/12 15:57:09 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(int fd, unsigned long n)
{
	size_t				count;
	char				*hex;

	hex = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		count += ft_puthex(fd, n / 16);
		count += ft_puthex(fd, n % 16);
	}
	else
		count += ft_putchari(fd, hex[n]);
	return (count);
}

int	ft_putptr(int fd, void	*ptr)
{
	size_t			count;
	unsigned long	addr;

	if (ptr == 0)
		return (ft_putstri(fd, "(nil)"));
	addr = (unsigned long)ptr;
	count = 0;
	count += ft_putstri(fd, "0x");
	if (addr == 0)
		count += ft_putchari(fd, '0');
	else
		count += ft_puthex(fd, addr);
	return (count);
}
