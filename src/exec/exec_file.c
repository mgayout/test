/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:53:27 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/03 16:43:30 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file_cmd(t_data *data)
{
	t_pid	pid;

	pid = data->exec->child[0];
	if (pid.lst->infile_count == 1 && pid.lst->heredoc_count == 0)
	{
		printf("1\n");
		pid.infile = open(pid.lst->infile[0], O_RDONLY);
	}
	else if (pid.lst->heredoc_count == 1 && pid.lst->infile_count == 0)
	{
		printf("2\n");
		pid.infile = init_heredoc(data);
	}
	else if (pid.lst->infile_count + pid.lst->heredoc_count > 1)
	{
		printf("3\n");
		pid.infile = open_infiles_cmd(data);
	}
	else
	{
		printf("4\n");
		pid.infile = data->exec->std_in;	
	}
	if (pid.lst->outfile_count > 0)
	{
		if (pid.lst->outfile_count == 1 && !ft_strncmp(pid.lst->append[0], "false", ft_strlen("false")))
		{
			printf("1\n");
			pid.outfile = open(pid.lst->outfile[0], O_RDWR | O_TRUNC | O_CREAT, 0640);
		}
		else if (!ft_strncmp(pid.lst->append[0], "true", ft_strlen("true")) && pid.lst->outfile_count == 1)
		{
			printf("2\n");
			pid.outfile = open(pid.lst->outfile[0], O_WRONLY | O_CREAT | O_APPEND, 0640);
		}
		else if (pid.lst->outfile_count > 1)
		{
			printf("3\n");
			pid.outfile = open_outfiles_cmd(data);
		}
	}
	else
		pid.outfile = data->exec->std_out;
	dup2(pid.infile, STDIN_FILENO);
	dup2(pid.outfile, STDOUT_FILENO);
}
/*
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
}*/

/*void	open_files(t_data *data)
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
}*/
