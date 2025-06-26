/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:57:11 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/10 11:15:34 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_process(int fd, char conv, va_list *args)
{
	int	count;

	count = 0;
	if (conv == 'd' || conv == 'i')
		count += ft_putnbri(fd, va_arg(*args, int));
	else if (conv == 's')
		count += ft_putstri(fd, va_arg(*args, char *));
	else if (conv == 'c')
		count += ft_putchari(fd, va_arg(*args, int));
	else if (conv == 'u')
		count += ft_putnbrui(fd, va_arg(*args, size_t));
	else if (conv == '%')
		count += ft_putchari(fd, '%');
	else if (conv == 'x')
		count += ft_putnbrhexmin(fd, va_arg(*args, int));
	else if (conv == 'X')
		count += ft_putnbrhexmaj(fd, va_arg(*args, int));
	else if (conv == 'p')
		count += ft_putptr(fd, va_arg(*args, void *));
	else
		count += ft_putchari(fd, conv);
	return (count);
}

static int	vprintf_loop(int fd, const char *format, va_list *args)
{
	size_t	count;
	size_t	tmp;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			tmp = ft_process(fd, *format, args);
		}
		else
			tmp = ft_putchari(fd, *format);
		count += tmp;
		format++;
	}
	return (count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = vprintf_loop(fd, format, &args);
	va_end(args);
	return (ret);
}
