/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:21:56 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 18:14:26 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copystring(char const *s, int start, int end)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *) malloc(sizeof(char) * (end - start + 2));
	if (!res)
		return (NULL);
	while (start < end)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

static char	*free_array(char **res, int j, char *tmp)
{
	int	i;

	if (!tmp)
	{
		i = 0;
		while (i < j)
			free(res[i++]);
		free(res);
		return (NULL);
	}
	return (tmp);
}

static int	count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**machination(char const *s, char c, int *i, int *j)
{
	int		debut;
	char	*tmp;
	char	**res;

	res = (char **) malloc(sizeof(char *) * (count(s, c) + 1));
	if (!res)
		return (NULL);
	while (s[*i])
	{
		while (s[*i] == c)
			(*i)++;
		debut = *i;
		while (s[*i] && s[*i] != c)
			(*i)++;
		if (*i > debut)
		{
			tmp = copystring(s, debut, *i);
			if (!free_array(res, *j, tmp))
				return (NULL);
			res[(*j)++] = tmp;
		}
	}
	res[*j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = machination(s, c, &i, &j);
	if (!res)
		return (NULL);
	return (res);
}
/*
int	main(void)
{
	ft_split("bonjourzzaa", 'z');

}*/
