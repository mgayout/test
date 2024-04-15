/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:21:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/15 17:56:17 by mgayout          ###   ########.fr       */
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
		{
			free(path_cmd);
			free_tab(path);
			return (1);
		}
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
	else if (tmp->prev->prev == NULL)
		return (0);
	else if (!ft_strncmp(tmp->prev->status, "flag", 5)
			&& !ft_strncmp(tmp->prev->prev->status, "cmd", 4))
				return (1);
	return (0);
}

int	is_a_limiter(t_arg **lst)
{
	t_arg	*tmp;
	
	tmp = *lst;
	if (tmp->prev == NULL)
		return (0);
	else if (!ft_strncmp(tmp->prev->data, "<<", 3))
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
	return (0);
}

void	print_lst(t_arg *lst)
{
	if (lst == NULL)
		ft_printf("lst is NULL\n");
	while (lst != NULL)
	{
		printf("id = %d\ndata = %s\nstatus = %s\n", lst->id, lst->data, lst->status);
		if (!ft_strncmp(lst->status, "cmd", 4))
		{
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