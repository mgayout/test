/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:21:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/12 11:24:49 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_a_cmd(char *str)
{
	char	**path;
	char	*tmp;
	char	*path_cmd;
	int		i;

	path = ft_split(getenv("PATH"), ':');	
	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(path_cmd, 0) == 0)
			return (1);
		free(path_cmd);
		i++;
	}
	/*if (access(str, 0) == 0)
	{
		printf("%s\n", str);
		return (1);
	}*/
	return (0);
}

int	is_an_arg(t_arg **lst)
{
	t_arg	*tmp;

	tmp = *lst;
	if (tmp->prev == NULL)
		return (0);
	else if (!ft_strncmp(tmp->prev->status, "cmd", 3))
		return (1);
	return (0);
}

int	is_a_file(t_arg **lst)
{
	t_arg	*tmp;
	
	tmp = *lst;
	if (tmp->prev == NULL)
		return (0);
	else if (tmp->prev->token > 0 && tmp->prev->token < 5)
		return (1);
	else
		return (0);
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
