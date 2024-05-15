/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:13:00 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 16:01:30 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file_pipeline(t_data *data, t_pid child, int out)
{
	if (!data->exec->pid[out])
	{
		if (out == 0)
		{
			if (child.lst->infile_count > 1
				|| (child.lst->infile_count == 1 && child.lst->pipein == true))
				infiles_pipeline(data, child);
			else
				infile_pipeline(data, child);
		}
		else
			infile_pipeline_bool(data, child);
		outfile_pipeline(data, child);
	}
	else
		if (child.lst->pipeout)
		{
			dup2(data->exec->pipefd[0], STDIN_FILENO);
			close(data->exec->pipefd[1]);
		}
}

void	infile_pipeline(t_data *data, t_pid child)
{
	if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "false", ft_strlen("false")))
	{
		child.infile = open(child.lst->infile[0], O_RDONLY);
		dup2(child.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "true", ft_strlen("true")))
	{
		child.infile = init_heredoc(data, child.lst->infile[0]);
		data->exec->temp = true;
		dup2(child.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else
		close(data->exec->pipefd[0]);
}

void	infiles_pipeline(t_data *data, t_pid child)
{
	int		infile;
	int		file;

	infile = 0;
	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (child.lst->pipein == true)
		write_pipe_temp(STDIN_FILENO, file);
	while (infile != child.lst->infile_count)
	{
		if (!ft_strncmp(child.lst->heredoc[infile], "false", ft_strlen("false")))
			write_infile_temp(child, infile, file);
		else
			write_heredoc_temp(data, child, infile, file);
		infile++;
	}
	close(file);
	child.infile = open(".temp", O_RDONLY);
	dup2(child.infile, STDIN_FILENO);
	data->exec->temp = true;
}

void	infile_pipeline_bool(t_data *data, t_pid child)
{
	ft_putstr_fd("hi\n", data->exec->std_out);
	if (child.lst->infile_count == 0 && child.lst->pipein)
	{
		ft_putstr_fd("1\n", data->exec->std_out);
		printf("pipe\n");
		close(data->exec->pipefd[0]);
	}
	else if (child.lst->infile_count == 1
		&& !ft_strncmp(child.lst->heredoc[0], "false", ft_strlen("false")))
	{
		ft_putstr_fd("2\n", data->exec->std_out);
		printf("%s\n", child.lst->infile[0]);
		child.infile = open(child.lst->infile[0], O_RDONLY);
		dup2(child.infile, STDIN_FILENO);
	}
	else
	{
		ft_putstr_fd("3\n", data->exec->std_out);
		child.infile = open(".temp", O_RDONLY);
		dup2(child.infile, STDIN_FILENO);
	}
}


void	outfile_pipeline(t_data *data, t_pid child)
{
	printf("okok\n");
	if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "false", ft_strlen("false")))
	{
		child.outfile = open(child.lst->outfile[0], O_RDWR | O_TRUNC | O_CREAT, 0640);
		dup2(child.outfile, STDOUT_FILENO);
	}
	else if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "true", ft_strlen("true")))
	{
		child.outfile = open(child.lst->outfile[0], O_WRONLY | O_CREAT | O_APPEND, 0640);
		dup2(child.outfile, STDOUT_FILENO);
	}
	else if (child.lst->pipeout)
		dup2(data->exec->pipefd[1], STDOUT_FILENO);
	else
		close(data->exec->pipefd[1]);
}
