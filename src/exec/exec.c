/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/07 16:53:33 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_data *data)
{
	data->exec = init_exe(data->parser);
	if (data->exec->nb_cmd == 1)
		exec_cmd(data);
	else
		exec_pipeline(data);
	dup2(data->exec->std_in, STDIN_FILENO);
	dup2(data->exec->std_out, STDOUT_FILENO);
}

void	exec_cmd_file(t_data *data)
{
	data->exec->child[0].lst = data->parser;
	data->exec->child[0].infile = 0;
	data->exec->child[0].outfile = 0;
	data->exec->pid[0] = fork();
	if (!data->exec->pid[0])
	{
		open_file_cmd(data);
		if (data->exec->child[0].lst->builtin > 0)
			exec_builtins(data);
		else
			children(data);
	}
	else
		waitpid(data->exec->pid[0], NULL, 0); //a modifie !
	if (data->exec->child[0].lst->infile_count > 1)
		unlink(".temp");	
}

void	exec_pipeline_file(t_data *data) //a modifie !
{
	while (data->exec->status < data->exec->nb_cmd)
	{
		init_child(data);
		if (data->exec->child[data->exec->status].lst->pipeout)
			pipe(data->exec->pipefd);
		data->exec->pid[data->exec->status] = fork();
		if (!data->exec->pid[data->exec->status])
		{
			open_file_pipeline(data);
			if (data->exec->child[data->exec->status].lst->builtin > 0)
				exec_builtins(data);
			else
				children(data);
		}
		else
		{
			waitpid(data->exec->pid[data->exec->status], NULL, 0);
			if (data->exec->child[data->exec->status].lst->pipeout)
			{
				dup2(data->exec->pipefd[0], STDIN_FILENO);
				close(data->exec->pipefd[1]);
			}
		}
		data->exec->status += 1;
	}
}
