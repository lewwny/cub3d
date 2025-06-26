/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:38:18 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/12 15:57:20 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t				i;
	unsigned char		d;
	size_t				size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	i = 0;
	d = (unsigned char) c;
	while (i < size + 1)
	{
		if (d == s[i])
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("%s", ft_strchr(argv[1], 'e'));
	return (0);
}*/
