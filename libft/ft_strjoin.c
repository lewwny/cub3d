/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:18:17 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/12 17:15:59 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpycat(char *dest, const char *src, size_t *j)
{
	size_t	i;

	i = 0;
	if (src)
	{
		while (src[i])
			dest[(*j)++] = src[i++];
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int				size_s1;
	int				size_s2;
	char			*res;
	size_t			j;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	j = 0;
	res = (char *) malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (!res)
		return (NULL);
	ft_strcpycat(res, s1, &j);
	ft_strcpycat(res, s2, &j);
	res[j] = '\0';
	return (res);
}
