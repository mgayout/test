/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 12:04:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	children(t_data *data, t_pid child)
{
	int		i;

	if (child.lst->builtin > 0)
		exec_builtins(data, child);
	else
	{
		i = 0;
		child.arg1 = create_arg1(child.lst->cmd);
		//printf("arg1 = %s\n", child.arg1);
		child.arg2 = create_arg2(child);
		while (child.arg2[i])
		{
			//printf("arg2 = %s\n", child.arg2[i]);
			i++;
		}
		if (child.arg1 && child.arg2)
			execve(child.arg1, child.arg2, data->envp);
		else
		{
			ft_putstr_fd(child.lst->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			data->error = 127;
		}
	}
}

char	*create_arg1(char *str)
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
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	if (access(str, 0) == 0)
		return (str);
	return (NULL);
}

char	**create_arg2(t_pid child)
{
	char	**arg2;
	char	*tmp;

	tmp = child.lst->cmd;
	if (child.lst->arg)
	{
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, child.lst->arg);
	}
	arg2 = ft_split(tmp, ' ');
	return (arg2);
}
