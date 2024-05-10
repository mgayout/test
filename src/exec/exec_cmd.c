/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/10 16:51:15 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	children(t_data *data)
{
	t_exe	*exec;
	int		i;
	int		j;

	j = 0;
	i = data->exec->status;
	exec = data->exec;
	exec->child[i].arg1 = create_arg1(exec->child[i].lst->cmd);
	//printf("arg1 = %s\n", exec->child[i].arg1);
	exec->child[i].arg2 = create_arg2(data);
	while (exec->child[i].arg2[j])
	{
		//printf("arg2 = %s\n", exec->child[i].arg2[j]);
		j++;
	}
	execve(exec->child[i].arg1, exec->child[i].arg2, data->envp);
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

char	**create_arg2(t_data *data)
{
	char	**arg2;
	char	*tmp;
	int		i;

	i = data->exec->status;
	tmp = data->exec->child[i].lst->cmd;
	if (data->exec->child[i].lst->arg)
	{
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, data->exec->child[i].lst->arg);
	}
	arg2 = ft_split(tmp, ' ');
	return (arg2);
}
