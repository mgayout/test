/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/18 17:47:30 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	children(t_data *data)
{
	t_exec	*exec;
	int		i;
	int		j;

	j = 0;
	i = data->exec->status;
	exec = data->exec;
	exec->child[i].arg1 = ft_lst1(exec->child[i].lst->data);
	//printf("arg1 = %s\n", exec->child[i].arg1);
	exec->child[i].arg2 = ft_lst2(data);
	while (exec->child[i].arg2[j])
	{
		//printf("arg2 = %s\n", exec->child[i].arg2[j]);
		j++;
	}
	execve(exec->child[i].arg1, exec->child[i].arg2, data->envp);
}

char	*ft_lst1(char *str)
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

char	**ft_lst2(t_data *data)
{
	char	**arg2;
	char	*tmp;
	int		i;

	i = data->exec->status;
	tmp = data->exec->child[i].lst->data;
	if (data->exec->child[i].lst->flag)
	{
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, data->exec->child[i].lst->flag);
		arg2 = ft_split(tmp, ' ');
	}
	if (data->exec->child[i].lst->arg)
	{
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, data->exec->child[i].lst->arg);
		arg2 = ft_split(tmp, ' ');
	}
	else if (!data->exec->child[i].lst->flag && !data->exec->child[i].lst->arg)
		arg2 = ft_split(data->exec->child[i].lst->data, ' ');
	return (arg2);
}
