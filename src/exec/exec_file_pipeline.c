/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:13:00 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/07 14:13:59 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file_pipeline(t_data *data)
{
	t_pid	pid;

	pid = data->exec->child[data->exec->status];
	if (pid.lst->infile_count > 1)
		infile_pipeline(data);
	//else
		//open_infiles_pipeline(data);
	if (pid.lst->outfile_count > 1)
		outfile_pipeline(data);
	//else
		//open_outfiles_pipeline(data);
}

void	infile_pipeline(t_data *data)
{
	t_pid	pid;

	pid = data->exec->child[data->exec->status];
	if (pid.lst->infile_count == 1 && !ft_strncmp(pid.lst->heredoc[0], "false", ft_strlen("false")))
	{
		pid.infile = open(pid.lst->infile[0], O_RDONLY);
		dup2(pid.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else if (pid.lst->infile_count == 1 && !ft_strncmp(pid.lst->heredoc[0], "true", ft_strlen("true")))
	{
		pid.infile = init_heredoc(data);
		dup2(pid.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else
		close(data->exec->pipefd[0]);
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
	else if (!ft_strncmp(pid.lst->append[0], "true", ft_strlen("true")) && pid.lst->outfile_count == 1)
	{
		pid.outfile = open(pid.lst->outfile[0], O_WRONLY | O_CREAT | O_APPEND, 0640);
		dup2(pid.outfile, STDOUT_FILENO);
	}
	else if (pid.lst->pipeout)
		dup2(data->exec->pipefd[1], STDOUT_FILENO);
	else
		close(data->exec->pipefd[1]);
}
