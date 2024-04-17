/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:21:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/17 12:42:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_lst(t_arg *lst)
{
	if (lst == NULL)
		ft_printf("lst is NULL\n");
	while (lst != NULL)
	{
		printf("id = %d\ndata = %s\nstatus = %s\n",
			lst->id, lst->data, lst->status);
		if (!ft_strncmp(lst->status, "cmd", 4))
		{
			if (lst->builtins > 0)
				printf("builtins = %d", lst->builtins);
			if (lst->flag)
				printf("flag = %s\n", lst->flag);
			if (lst->arg)
				printf("arg = %s\n", lst->arg);
			if (lst->infile)
				printf("infile = %s\n", lst->infile);
			else if (lst->pipein == true)
				printf("pipein = true\n");
			else if (lst->heredoc)
				printf("heredoc mode = true\nlimiter = %s\n", lst->heredoc);
			else
				printf("stdin = true\n");
			if (lst->outfile)
				printf("outfile = %s\n", lst->outfile);
			else if (lst->pipeout == true)
				printf("pipeout = true\n");
			else
				printf("stdout = true\n");
			if (lst->append == true)
				printf("append mode = true\n");
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
		if (!ft_strncmp(clean->status, "cmd", 4))
		{
			free(clean->arg);
			free(clean->flag);
			if (clean->infile)
				free(clean->infile);
			if (clean->outfile)
				free(clean->outfile);
			if (clean->heredoc)
				free(clean->heredoc);
		}
		free(clean->status);
		free(clean);
	}
}

void	free_tab(char **tabtab)
{
	int	i;

	i = 0;
	while (tabtab[i] != NULL)
	{
		free(tabtab[i]);
		i++;
	}
	free(tabtab);
}
