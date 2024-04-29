/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/29 13:21:03 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_data *data)
{
	data->exec = init_exe(data->parser);
	//init_exec(data);
	if (data->exec->nb_cmd == 1)
		exec_a_cmd(data);
	else
		exec_pipeline(data);
	dup2(data->exec->std_in, STDIN_FILENO);
	dup2(data->exec->std_out, STDOUT_FILENO);
}

void	exec_a_cmd(t_data *data)
{
	data->exec->child[0].lst = data->parser;
	data->exec->pid[0] = fork();
	if (data->exec->child[0].lst->heredoc)
		data->exec->heredoc = true;
	if (!data->exec->pid[0])
	{
		open_files(data);
		if (data->exec->child[0].lst->builtin > 0)
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
