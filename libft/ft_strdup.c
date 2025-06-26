/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:11:06 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 18:14:26 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*dup;

	size = 0;
	while (s1[size])
		size++;
	dup = (char *) malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	size = 0;
	while (s1[size])
	{
		dup[size] = s1[size];
		size++;
	}
	dup[size] = '\0';
	return (dup);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*test;

	if (argc !=2)
		return (1);
	test = ft_strdup(argv[1]);
	printf("%s\n", test);
	free(test);
	return (0);
}*/
