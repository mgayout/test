/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/10 17:51:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_arg(t_mini *lst, char **envp)
{
	t_exec	exec;

	exec.lst = malloc(sizeof(t_mini));
	exec.lst = lst;
	init_exec(&exec);
	dup2(exec.infile, STDIN_FILENO);
	while(exec.status < exec.nb_cmd)
	{
		pipe(exec.pipefd);
		exec.pid[exec.status] = fork();
		open_pipe(&exec, envp);
		exec.status += 1;
	}
}

void	open_pipe(t_exec *exec, char **envp)
{
	if (!exec->pid[exec->status])
	{
		if (exec->status < exec->nb_cmd - 1)
		{
			close(exec->pipefd[0]);
			dup2(exec->pipefd[1], STDOUT_FILENO);
			children(exec, envp);
		}
		else
		{
			dup2(exec->outfile, STDOUT_FILENO);
			children(exec, envp);
		}
	}
	else
	{
		dup2(exec->pipefd[0], STDIN_FILENO);
		close(exec->pipefd[1]);
		waitpid(exec->pid[exec->status], NULL, 0);
	}
}

void	children(t_exec *exec, char **envp)
{
	t_mini	*lst;

	lst = good_cmd(exec);
	exec->arg1 = ft_arg1(lst->data);
	exec->arg2 = ft_arg2(lst);
	printf("%s\n", exec->arg1);
	execve(exec->arg1, exec->arg2, envp);
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
	printf("ok\n");
	return (NULL);
}

char	**ft_arg2(t_mini *lst)
{
	char	**arg2;
	char	*tmp;

	tmp = ft_strjoin(lst->data, " ");
	if (!ft_strncmp(lst->next->status, "flag", 5))
	{
		lst = lst->next;
		tmp = ft_strjoin(tmp, lst->data);
		tmp = ft_strjoin(tmp, " ");
	}
	tmp = ft_strjoin(tmp, "NULL");
	arg2 = ft_split(tmp, ' ');
	return (arg2);
}

t_mini	*good_cmd(t_exec *exec)
{
	t_mini	*tmp;
	int		nb;

	tmp = exec->lst;
	nb = -1;
	while (nb != exec->status)
	{
		if (!ft_strncmp(tmp->status, "cmd", 4))
			nb++;
		tmp = tmp->next;
	}
	return (tmp->prev);
}

void	init_exec(t_exec *exec)
{
	t_mini	*tmp;
	int		first_file;

	first_file = 0;
	tmp = exec->lst;
	exec->status = 0;
	exec->nb_arg = lstsize(tmp);
	exec->nb_cmd = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->status, "file", 5))
		{
			if (first_file == 0)
			{
				printf("infile\n");
				exec->infile = open(tmp->data, O_RDONLY);
			}
			else
			{
				printf("outfile\n");
				exec->outfile = open(tmp->data, O_CREAT
				| O_RDWR | O_TRUNC, 0777);
			}
			first_file++;
		}
		else if (!ft_strncmp(tmp->status, "cmd", 4))
			exec->nb_cmd += 1;
		tmp = tmp->next;
	}
	if (exec->infile == -1)
		printf("error\n");
	if (exec->outfile == -1)
		printf("error\n");
	exec->pid = malloc(sizeof(int) * exec->nb_cmd);
}