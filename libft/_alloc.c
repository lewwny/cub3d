/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:42:46 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 18:09:38 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*_malloc(size_t size, t_gb **garbage)
{
	void		*ptr;
	t_gb		*new_node;

	ptr = malloc(size);
	if (!ptr)
		malloc_error(garbage);
	new_node = ft_lstnew(ptr);
	if (!new_node)
	{
		free(ptr);
		malloc_error(garbage);
	}
	if (!garbage)
		garbage = &new_node;
	else
		ft_lstadd_back(garbage, new_node);
	return (ptr);
}

void	_free(void *ptr, t_gb **garbage)
{
	t_gb	*current;
	t_gb	*prev;

	if (!ptr || !garbage)
		return ;
	current = *garbage;
	prev = NULL;
	while (current)
	{
		if (current->content == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*garbage = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	free(ptr);
}

void	free_all(t_gb **garbage)
{
	t_gb	*current;
	t_gb	*next;

	if (!garbage || !*garbage)
		return ;
	current = *garbage;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*garbage = NULL;
}

void	malloc_error(t_gb **garbage)
{
	write(2, "Memory allocation error\n", 25);
	free_all(garbage);
	exit(EXIT_FAILURE);
}
