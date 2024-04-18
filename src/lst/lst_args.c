/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:25:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/18 17:47:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*status_lst(t_lst *lst)
{
	if (lst->token > 0)
		return (ft_strdup("token"));
	if (is_a_cmd(lst->data))
		return (ft_strdup("cmd"));
	else if (!ft_strncmp(lst->data, "-", 1))
		return (ft_strdup("flag"));
	else if (is_an_arg(&lst))
		return (ft_strdup("arg"));
	else if (is_a_limiter(&lst))
		return (ft_strdup("limiter"));
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

void	flag_arg(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst->next;
	if (!tmp)
		return ;
	if (!ft_strncmp(tmp->status, "flag", 5))
		lst->flag = ft_strdup(tmp->data);
	if (!ft_strncmp(tmp->status, "arg", 4))
		lst->arg = ft_strdup(tmp->data);
	else
		if (tmp->next != NULL)
			if (!ft_strncmp(tmp->next->status, "arg", 4))
				lst->arg = ft_strdup(tmp->next->data);
}

void	before_cmd(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token > 0)
		{
			if (!ft_strncmp(tmp->data, "<", 2))
				lst->infile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">", 2))
				lst->outfile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, "<<", 3))
				lst->heredoc = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">>", 3))
			{
				lst->append = true;
				lst->outfile = ft_strdup(tmp->next->data);
			}
			else if (!ft_strncmp(tmp->data, "|", 2))
				lst->pipein = true;
			return ;
		}
		tmp = tmp->prev;
	}
}

void	after_cmd(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token > 0)
		{
			if (!ft_strncmp(tmp->data, "<", 2))
				lst->infile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">", 2))
				lst->outfile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, "<<", 3))
				lst->heredoc = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">>", 3))
			{
				lst->append = true;
				lst->outfile = ft_strdup(tmp->next->data);
			}
			else if (!ft_strncmp(tmp->data, "|", 2))
				lst->pipeout = true;
			return ;
		}
		tmp = tmp->next;
	}
}
