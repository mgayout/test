/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:13:00 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/10 18:38:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file_pipeline(t_data *data)
{
	t_pid	child;

	child = data->exec->child[data->exec->status];
	if (!data->exec->pid[data->exec->status])
	{
		if (child.lst->infile_count > 1
			|| (child.lst->infile_count == 1 && child.lst->pipein == true))
			infiles_pipeline(data);
		else
			infile_pipeline(data);
		//if (child.lst->outfile_count > 1)
			//outfiles_pipeline(data);
		//else
		outfile_pipeline(data);
	}
	else
		if (child.lst->pipeout)
		{
			dup2(data->exec->pipefd[0], STDIN_FILENO);
			close(data->exec->pipefd[1]);
		}
}

void	infile_pipeline(t_data *data)
{
	t_pid	child;

	child = data->exec->child[data->exec->status];
	if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "false", ft_strlen("false")))
	{
		child.infile = open(child.lst->infile[0], O_RDONLY);
		dup2(child.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "true", ft_strlen("true")))
	{
		child.infile = init_heredoc(data, child.lst->infile[0]);
		dup2(child.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else
		close(data->exec->pipefd[0]);
}

void	infiles_pipeline(t_data *data)
{
	t_pid	child;
	int		infile;
	int		file;

	child = data->exec->child[data->exec->status];
	infile = 0;
	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (child.lst->pipein == true)
		write_pipe_temp(STDIN_FILENO, file);
	while (infile != child.lst->infile_count)
	{
		if (!ft_strncmp(child.lst->heredoc[infile], "false", ft_strlen("false")))
			write_infile_temp(data, infile, file);
		else
			write_heredoc_temp(data, infile, file);
		infile++;
	}
	close(file);
	child.infile = open(".temp", O_RDONLY);
	dup2(child.infile, STDIN_FILENO);
}

void	outfile_pipeline(t_data *data)
{
	t_pid	pid;

	pid = data->exec->child[data->exec->status];
	if (pid.lst->outfile_count == 1 && !ft_strncmp(pid.lst->append[0], "false", ft_strlen("false")))
	{
		pid.outfile = open(pid.lst->outfile[0], O_RDWR | O_TRUNC | O_CREAT, 0640);
		dup2(pid.outfile, STDOUT_FILENO);
	}
	else if (pid.lst->outfile_count == 1 && !ft_strncmp(pid.lst->append[0], "true", ft_strlen("true")))
	{
		pid.outfile = open(pid.lst->outfile[0], O_WRONLY | O_CREAT | O_APPEND, 0640);
		dup2(pid.outfile, STDOUT_FILENO);
	}
	else if (pid.lst->pipeout)
		dup2(data->exec->pipefd[1], STDOUT_FILENO);
	else
		close(data->exec->pipefd[1]);
}

/*void	outfiles_pipeline(t_data *data)// a finir
{
	//t_pid	pid;
	int		outfile;

	//pid = data->exec->child[data->exec->status];
	outfile = 0;
	while (outfile != child.lst->outfile_count)
	{
		if (outfile != child.lst->outfile_count - 1)
			child.pid[outfile] = fork();
		if (!ft_strncmp(child.lst->append[outfile], "false", ft_strlen("false")))
			child.outfile = open(child.lst->outfile[outfile], O_RDWR | O_TRUNC | O_CREAT, 0640);
		else if (!ft_strncmp(child.lst->append[outfile], "true", ft_strlen("true")))
			child.outfile = open(child.lst->outfile[outfile], O_WRONLY | O_CREAT | O_APPEND, 0640);
		if (!child.pid[outfile])
			break;
		outfile++;
	}
}*/
