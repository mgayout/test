/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:53:27 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/25 17:34:10 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_pipe(t_data *data)
{
	int	i;

	i = data->exec->status;
	if (!data->exec->pid[i])
	{
		open_infile(data);
		open_outfile(data);
		if (data->exec->child[0].lst->builtin > 0)
			exec_builtins(data);
		else
			children(data);
	}
	else
	{
		waitpid(data->exec->pid[i], NULL, 0);
		if (data->exec->child[i].lst->pipeout)
		{
			dup2(data->exec->pipefd[0], STDIN_FILENO);
			close(data->exec->pipefd[1]);
		}
	}
}

void	open_infile(t_data *data)
{
	t_pid	pid;
	int		i;

	i = data->exec->status;
	pid = data->exec->child[i];
	if (pid.lst->infile)
	{
		pid.infile = open(pid.lst->infile, O_RDONLY);
		dup2(pid.infile, STDIN_FILENO);
	}
	else if (pid.lst->heredoc)
	{
		init_heredoc(data);
		pid.infile = open(".temp", O_RDONLY);
		dup2(pid.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else if (pid.lst->pipein)
		close(data->exec->pipefd[0]);
	else
		close(data->exec->pipefd[0]);
}

void	open_outfile(t_data *data)
{
	t_pid	pid;
	int		i;

	i = data->exec->status;
	pid = data->exec->child[i];
	if (pid.lst->outfile)
	{
		if (pid.lst->append)
			pid.outfile = open(pid.lst->outfile, O_WRONLY
					| O_CREAT | O_APPEND, 0640);
		else if (!pid.lst->append)
			pid.outfile = open(pid.lst->outfile, O_RDWR
					| O_TRUNC | O_CREAT, 0640);
		dup2(pid.outfile, STDOUT_FILENO);
	}
	else if (pid.lst->pipeout)
		dup2(data->exec->pipefd[1], STDOUT_FILENO);
	else
		close(data->exec->pipefd[1]);
}

void	open_files(t_data *data)
{
	t_pid	pid;

	pid = data->exec->child[0];
	if (pid.lst->infile || pid.lst->heredoc)
	{
		if (pid.lst->heredoc)
		{
			init_heredoc(data);
			pid.infile = open(".temp", O_RDONLY);
		}
		else
			pid.infile = open(pid.lst->infile, O_RDONLY);
		dup2(pid.infile, STDIN_FILENO);
	}
	if (pid.lst->outfile)
	{
		if (pid.lst->append)
			pid.outfile = open(pid.lst->outfile, O_WRONLY
					| O_CREAT | O_APPEND, 0640);
		else
			pid.outfile = open(pid.lst->outfile, O_RDWR
					| O_TRUNC | O_CREAT, 0640);
		dup2(pid.outfile, STDOUT_FILENO);
	}
}
