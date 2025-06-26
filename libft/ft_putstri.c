/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:29:57 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/04 10:11:15 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstri(int fd, char const *s)
{
	int	i;
	int	tmp;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
		i++;
	tmp = write(fd, s, i);
	if (tmp < 0)
		return (-1);
	return (i);
}
