/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_is_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:37:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/18 17:46:34 by mgayout          ###   ########.fr       */
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
	return (0);
}

void	is_a_builtins(t_lst *lst)
{
	if (!ft_strncmp(lst->data, "echo", 5))
		lst->builtins = 1;
	else if (!ft_strncmp(lst->data, "cd", 3))
		lst->builtins = 2;
	else if (!ft_strncmp(lst->data, "pwd", 4))
		lst->builtins = 3;
	else if (!ft_strncmp(lst->data, "export", 7))
		lst->builtins = 4;
	else if (!ft_strncmp(lst->data, "unset", 6))
		lst->builtins = 5;
	else if (!ft_strncmp(lst->data, "env", 4))
		lst->builtins = 6;
	else if (!ft_strncmp(lst->data, "exit", 5))
		lst->builtins = 7;
}

int	is_an_arg(t_lst **lst)
{
	t_lst	*tmp;

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

int	is_a_limiter(t_lst **lst)
{
	t_lst	*tmp;

	tmp = *lst;
	if (tmp->prev == NULL)
		return (0);
	else if (!ft_strncmp(tmp->prev->data, "<<", 3))
		return (1);
	return (0);
}

int	is_a_file(t_lst **lst)
{
	t_lst	*tmp;

	tmp = *lst;
	if (tmp->prev == NULL)
		return (0);
	else if (tmp->prev->token > 0 && tmp->prev->token < 5)
		return (1);
	return (0);
}
