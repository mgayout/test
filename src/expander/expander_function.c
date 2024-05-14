/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:45:38 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/14 16:18:19 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	add_back_exp(t_exp **expander, t_exp *new)
{
	t_exp	*back;

	if (!*expander)
		*expander = new;
	else
	{
		back = explast(*expander);
		back->next = new;
	}
}

t_exp	*explast(t_exp *lst)
{
	t_exp	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = expsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

int	expsize(t_exp *lst)
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