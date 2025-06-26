/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:52:23 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/10 11:15:34 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count(char const *s1, char const *set)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (in_set(s1[i], set))
		i++;
	while (s1[i])
	{
		i++;
		count++;
	}
	while (i > 0 && in_set(s1[i - 1], set) && count != 0)
	{
		i--;
		count--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		length;
	char	*res;

	i = 0;
	j = 0;
	length = count(s1, set);
	res = (char *) malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	while (in_set(s1[i], set))
		i++;
	while (j < length)
		res[j++] = s1[i++];
	res[j] = '\0';
	return (res);
}
