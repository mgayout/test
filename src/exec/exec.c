/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/19 12:01:34 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	init_exec(data);
	if (data->exec->nb_cmd == 1)
		exec_a_cmd(data);
	else
		exec_pipeline(data);
	dup2(data->exec->std_in, STDIN_FILENO);
	dup2(data->exec->std_out, STDOUT_FILENO);
	if (data->exec->pipefd[0] > 0)
		close(data->exec->pipefd[0]);
	if (data->exec->pipefd[1] > 0)
		close(data->exec->pipefd[1]);
	if (data->exec->heredoc)
		unlink(".temp");
	free(data->exec->pid);
	free(data->exec->child);
	free(data->exec->pipefd);
}

void	exec_a_cmd(t_data *data)
{
	init_child(data);
	data->exec->pid[0] = fork();
	if (!data->exec->pid[0])
	{
		open_files(data);
		if (data->exec->child[0].lst->builtins > 0)
			exec_builtins(data);
		else
			children(data);
	}
	else
		waitpid(data->exec->pid[0], NULL, 0);
}

void	exec_pipeline(t_data *data)
{
	while (data->exec->status < data->exec->nb_cmd)
	{
		init_child(data);
		if (data->exec->child[data->exec->status].lst->pipeout)
			pipe(data->exec->pipefd);
		data->exec->pid[data->exec->status] = fork();
		open_pipe(data);
		data->exec->status += 1;
	}
}
