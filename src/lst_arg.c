/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:27:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/10 16:57:18 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_lst(t_mini **lst, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		fill_list(lst, arg[i]);
		i++;
	}
}

void	fill_list(t_mini **lst, char *str)
{
	t_mini	*new;
	t_mini	*tmp;

	if (!lst)
		return ;
	new = malloc(sizeof(t_mini));
	if (!new)
		return ;
	new->data = str;
	new->builtins = 0;
	new->token = token_lst(new->data);
	new->id = lstsize(*lst) + 1;
	new->status = status_lst(new);
	new->next = NULL;
	new->prev = NULL;
	if (!(*lst))
		*lst = new;
	else
	{
		tmp = lstlast(*lst);
		new->prev = tmp;
		tmp->next = new;
	}
}

void	print_lst(t_mini *lst)
{
	if (lst == NULL)
		ft_printf("lst is NULL\n");
	while (lst != NULL)
	{
		ft_printf("id = %d\nstatus = %s\ndata = %s\nbuiltins = %d\ntoken = %d\n\n", lst->id, lst->status, lst->data, lst->builtins, lst->token);
		lst = lst->next;
	}
}

void	free_lst(t_mini **s)
{
	t_mini	*clean;

	while (*s != NULL)
	{
		clean = *s;
		*s = (*s)->next;
		free(clean);
	}
}
