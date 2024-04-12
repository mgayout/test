/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/12 11:16:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_arg(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	init_exec(data);
	while(data->exec->status < data->exec->nb_cmd)
	{
		//if (data->exec->nb_cmd > 1)
			//pipe(data->exec->pipefd);
		data->exec->pid[data->exec->status] = fork();
		if (!data->exec->pid[data->exec->status])
		{
			init_child(data);
			children(data);
		}
		//open_pipe(data);
		waitpid(data->exec->pid[data->exec->status], NULL, 0);
		data->exec->status += 1;
	}
	free(data->exec->pid);
	free(data->exec->child);
}

/*void	open_pipe(t_data *data)
{
	int	i;

	i = data->exec->status;
	if (!data->exec->pid[i])
	{
		if (data->exec->nb_cmd > 1)
		{
			init_child(data);
			children(data);
		}
		else
		{
			init_child(data);
			if (data->exec->child[i].pipein)
				//dup2(data->exec->pipefd[0], STDIN_FILENO);
			if (data->exec->child[i].pipeout)
				//dup2(data->exec->pipefd[1], STDOUT_FILENO);
			children(data);
		}
	}
	else
	{
		//dup2(data->exec->pipefd[0], STDIN_FILENO);
		//close(data->exec->pipefd[1]);
		waitpid(data->exec->pid[i], NULL, 0);
	}
}*/

void	children(t_data *data)
{
	t_exec	*exec;
	int		i;
	int		j;
	
	j = 0;
	i = data->exec->status;
	exec = data->exec;
	exec->child[i].arg1 = ft_arg1(exec->child[i].cmd);
	//printf("arg1 = %s\n", exec->child[i].arg1);
	exec->child[i].arg2 = ft_arg2(data);
	while (exec->child[i].arg2[j])
	{
		//printf("arg2 = %s\n", exec->child[i].arg2[j]);
		j++;
	}
	execve(exec->child[i].arg1, exec->child[i].arg2, data->envp);
}

char	*ft_arg1(char *str)
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

char	**ft_arg2(t_data *data)
{
	char	**arg2;
	char	*tmp;
	int		i;

	i = data->exec->status;
	if (data->exec->child[i].arg)
	{
		tmp = ft_strjoin(data->exec->child[i].cmd, " ");
		tmp = ft_strjoin(tmp, data->exec->child[i].arg);
		arg2 = ft_split(tmp, ' ');
	}
	else if (data->exec->child[i].flag)
	{
		tmp = ft_strjoin(data->exec->child[i].cmd, " ");
		tmp = ft_strjoin(tmp, data->exec->child[i].flag);
		arg2 = ft_split(tmp, ' ');
	}
	else
		arg2 = ft_split(data->exec->child[i].cmd, ' ');
	return (arg2);
	/*if (lst->next != NULL && !ft_strncmp(lst->next->status, "flag", 5))
	{
		tmp = ft_strdup(lst->data);
		lst = lst->next;
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, lst->data);
		tmp = ft_strjoin(tmp, " ");
		arg2 = ft_split(tmp, ' ');
	}
	else
	{
		arg2 = malloc(sizeof(char *) * 2);
		arg2[0] = ft_strdup(lst->data);;
		arg2[1] = NULL;
	}
	return (arg2);*/
}

t_arg	*good_cmd(t_data *data)
{
	t_arg	*tmp;
	int		nb;

	tmp = data->lst;
	nb = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->status, "cmd", 4) && nb == data->exec->status)
			return (tmp);
		else if (!ft_strncmp(tmp->status, "cmd", 4) && nb != data->exec->status)
			nb++;
		tmp = tmp->next;
	}
	return (tmp->prev);
}
