/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:25:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/12 12:28:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*status_lst(t_arg *lst)
{
	//printf("data prev = %s && new = %s\n", lst->prev->data, lst->data);
	if (lst->token > 0)
		return (ft_strdup("token"));
	if (is_a_cmd(lst->data))
		return (ft_strdup("cmd"));
	else if (!ft_strncmp(lst->data, "-", 1))
		return (ft_strdup("flag"));
	else if (is_an_arg(&lst))
		return (ft_strdup("arg"));
	else if (is_a_file(&lst))
		return (ft_strdup("file"));
	else
		return (ft_strdup("IDK"));
}

int	token_lst(char *str)
{
	if (!ft_strncmp(str, "<<", 3))
		return (1);
	else if (!ft_strncmp(str, "<", 2))
		return (2);
	else if (!ft_strncmp(str, ">", 2))
		return (3);
	else if (!ft_strncmp(str, ">>", 3))
		return (4);
	else if (!ft_strncmp(str, "|", 2))
		return (5);
	else
		return (0);
}
void	before_cmd(t_arg *lst)
{
	t_arg	*tmp;
	
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token > 0)
		{
			if (!ft_strncmp(tmp->data, "<", 2))
				lst->infile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">", 2))
				lst->outfile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, "|", 2))
				lst->pipein = true;
			/*printf("BACK\ninfile = %s && outfile = %s\n", lst->infile, lst->outfile);
			if (lst->pipein == true)
				printf("true\n");
			else
				printf("false\n");*/
			return ;
		}
		tmp = tmp->prev;
	}
}

void	after_cmd(t_arg *lst)
{
	t_arg	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token > 0)
		{
			if (!ft_strncmp(tmp->data, "<", 2))
				lst->infile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">", 2))
				lst->outfile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, "|", 2))
				lst->pipeout = true;
			/*printf("FRONT\ninfile = %s && outfile = %s\n", lst->infile, lst->outfile);
			if (lst->pipein == true)
				printf("true\n");
			else
				printf("false\n");*/
			return ;
		}
		tmp = tmp->next;
	}
}
