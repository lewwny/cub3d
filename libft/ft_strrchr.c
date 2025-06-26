/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:04:04 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/03/11 19:36:16 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	d;

	d = (unsigned char) c;
	i = ft_strlen(s);
	if (d == '\0')
		return ((char *)(s + i));
	while (i > 0)
	{
		i--;
		if (d == s[i])
			return ((char *)(s + i));
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("%s", ft_strrchr(argv[1], '\0'));
	return (0);
}*/
