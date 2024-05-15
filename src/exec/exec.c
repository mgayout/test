/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 16:00:39 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_data *data)
{
	data->exec = init_exe(data->parser);
	if (data->exec->nb_cmd == 1)
		exec_cmd_file(data);
	else
		exec_pipeline(data);
	dup2(data->exec->std_in, STDIN_FILENO);
	dup2(data->exec->std_out, STDOUT_FILENO);
	if (data->exec->temp)
		unlink(".temp");
}

void	exec_cmd_file(t_data *data)
{
	t_pid	child;

	data->exec->child[data->exec->status] = init_child(data);
	child = data->exec->child[data->exec->status];
	if (child.nb_out > 1)
		exec_cmd_files(data);
	else
	{
		data->exec->pid = malloc(sizeof(int) * data->exec->nb_cmd);
		data->exec->pid[0] = fork();
		if (!data->exec->pid[0])
		{
			open_file_cmd(data, child, true);
			children(data, child);
		}
		waitpid(data->exec->pid[0], NULL, 0);
	}
}

void	exec_cmd_files(t_data *data)
{
	t_pid	child;
	int out;

	child = data->exec->child[data->exec->status];
	out = 0;
	data->exec->pid = malloc(sizeof(int) * child.nb_out);
	create_all_files(data, child);
	while (out != child.nb_out)
	{
		data->exec->pid[out] = fork();
		if (!data->exec->pid[out])
		{
			if (out == 0)
				open_file_cmd(data, child, true);
			else
				open_file_cmd(data, child, false);
			children(data, child);
		}
		waitpid(data->exec->pid[out], NULL, 0);
		out++;
		child.lst = child.lst->next;
	}
}

void	exec_pipeline(t_data *data)
{
	t_pid	child;
	int		out;

	while (data->exec->status < data->exec->nb_cmd)
	{
		out = 0;
		data->exec->child[data->exec->status] = init_child(data);
		child = data->exec->child[data->exec->status];
		data->exec->pid = malloc(sizeof(int) * child.nb_out);
		if (child.lst->pipeout)
			pipe(data->exec->pipefd);
		while (out != child.nb_out)
		{
			if (out == 0)
				create_all_files(data, child);
			data->exec->pid[out] = fork();
			open_file_pipeline(data, child, out);
			if (!data->exec->pid[out])
				children(data, child);
			waitpid(data->exec->pid[out], NULL, 0);
			data->exec->status += 1;
			out++;
			child.lst = child.lst->next;
		}
	}
}
