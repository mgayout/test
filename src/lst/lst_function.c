/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:51:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/19 12:00:58 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*back;

	if (!*lst)
		*lst = new;
	else
	{
		back = lstlast(*lst);
		back->next = new;
	}
}

t_lst	*lstlast(t_lst *lst)
{
	t_lst	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = lstsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

int	lstsize(t_lst *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}
