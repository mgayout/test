/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:27:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/11 17:13:56 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_lst(t_arg **lst, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		fill_list(lst, arg[i]);
		i++;
	}
	init_status(*lst);
	init_files(*lst);
}

void	init_status(t_arg *lst)
{
	while (lst != NULL)
	{
		lst->status = status_lst(lst);
		lst = lst->next;
	}
}

void	init_files(t_arg *lst)
{
	while (lst != NULL)
	{
		if (!ft_strncmp(lst->status, "cmd", 4))
		{
			start_cmd(lst);
			end_cmd(lst);
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
	new->data = str;
	new->token = token_lst(new->data);
	new->id = lstsize(*lst) + 1;
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

void	print_lst(t_arg *lst)
{
	if (lst == NULL)
		ft_printf("lst is NULL\n");
	while (lst != NULL)
	{
		printf("id = %d\nstatus = %s\ndata = %s\n", lst->id, lst->status, lst->data);
		if (!ft_strncmp(lst->status, "cmd", 4))
		{
			printf("infile = %s\noutfile = %s\n", lst->infile, lst->outfile);
			if (lst->pipein == true)
				printf("pipein = true\n");
			else
				printf("pipein = false\n");
			if (lst->pipeout == true)
				printf("pipeout = true\n");
			else
				printf("pipeout = false\n");
		}
		if (!ft_strncmp(lst->status, "token", 6))
			printf("token = %d\n", lst->token);
		printf("\n");
		lst = lst->next;
	}
}

void	free_lst(t_arg **s)
{
	t_arg	*clean;

	while (*s != NULL)
	{
		clean = *s;
		*s = (*s)->next;
		free(clean);
	}
}
