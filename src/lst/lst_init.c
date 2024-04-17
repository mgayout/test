/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:27:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/17 12:39:02 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_lst(t_arg **lst, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		fill_list(lst, arg[i]);
		i++;
	}
	fill_status(*lst);
	fill_cmd(*lst);
}

void	fill_status(t_arg *lst)
{
	while (lst != NULL)
	{
		lst->status = status_lst(lst);
		lst = lst->next;
	}
}

void	fill_cmd(t_arg *lst)
{
	while (lst != NULL)
	{
		if (!ft_strncmp(lst->status, "cmd", 4))
		{
			is_a_builtins(lst);
			flag_arg(lst);
			before_cmd(lst);
			after_cmd(lst);
		}
		lst = lst->next;
	}
}

void	fill_list(t_arg **lst, char *str)
{
	t_arg	*new;
	t_arg	*tmp;

	if (!lst)
		return ;
	new = malloc(sizeof(t_arg));
	if (!new)
		return ;
	set_lstargs(lst, new, str);
	if (!(*lst))
		*lst = new;
	else
	{
		tmp = lstlast(*lst);
		new->prev = tmp;
		tmp->next = new;
	}
}

void	set_lstargs(t_arg **lst, t_arg *new, char *str)
{
	new->id = lstsize(*lst) + 1;
	new->data = str;
	new->flag = NULL;
	new->arg = NULL;
	new->builtins = 0;
	new->infile = NULL;
	new->outfile = NULL;
	new->pipein = false;
	new->pipeout = false;
	new->append = false;
	new->heredoc = NULL;
	new->token = token_lst(new->data);
	new->next = NULL;
	new->prev = NULL;
}
