/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:46:56 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/23 14:49:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*lexlast(t_lex *lst)
{
	t_lex	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = lexsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

int	lexsize(t_lex *lst)
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

void	lexadd_back(t_lex **lst, t_lex *new)
{
	t_lex	*last;

	if (*lst != NULL)
	{
		last = *lst;
		last = lexlast(*lst);
		last->next = new;
		return ;
	}
	*lst = new;
}