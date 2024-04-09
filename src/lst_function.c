/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:51:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/09 15:21:42 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lstadd_back(t_mini **lst, t_mini *new)
{
	t_mini	*back;

	if (!*lst)
		*lst = new;
	else
	{
		back = lstlast(*lst);
		back->next = new;
	}
}

t_mini	*lstlast(t_mini *lst)
{
	t_mini	*last;
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

int	lstsize(t_mini *lst)
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
