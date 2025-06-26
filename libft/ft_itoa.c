/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:14:43 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 18:14:04 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put(char *str, char c, int *index)
{
	str[*index] = c;
	(*index)++;
}

static int	ft_size_int(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	calcul(int n, char *res, int *index)
{
	if (n == -2147483648)
	{
		ft_put(res, '-', index);
		ft_put(res, '2', index);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_put(res, '-', index);
		n = n * -1;
	}
	if (n >= 10)
	{
		calcul(n / 10, res, index);
		calcul(n % 10, res, index);
	}
	else
		ft_put(res, n + 48, index);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		size;
	int		index;

	index = 0;
	size = ft_size_int(n);
	res = (char *) malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	calcul(n, res, &index);
	res[index] = '\0';
	return (res);
}
/*
#include <stdio.h>
int	main()
{
	printf("%s", ft_itoa(-485));
}*/
