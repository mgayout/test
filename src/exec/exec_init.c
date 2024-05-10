/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:49:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/10 18:37:12 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../parser/parser.h"

t_exe	*init_exe(t_par *parser)
{
	t_exe	*exec;

	exec = (t_exe *)ft_calloc(1, sizeof(t_exe));
	if (!exec)
		return (NULL);
	exec->status = 0;
	exec->out = 0;
	exec->nb_cmd = parsize(parser);
	exec->std_in = dup(0);
	exec->std_out = dup(1);
	exec->pid = malloc(sizeof(int) * exec->nb_cmd);
	exec->child = malloc(sizeof(t_pid) * exec->nb_cmd);
	return (exec);
}

t_pid	init_child(t_data *data)
{
	t_pid	child;
	t_par	*tmp;
	int		i;

	child.infile = 0;
	child.outfile = 0;
	i = data->exec->status;
	tmp = data->parser;
	while (tmp != NULL)
	{
		if (i == (tmp->id - 1))
		{
			child.lst = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	if (child.lst->outfile_count >= 1)
	{
		if (child.lst->pipeout)
			child.pid = malloc(sizeof(int) * child.lst->outfile_count);
		else
			child.pid = malloc(sizeof(int) * child.lst->outfile_count - 1);
	}
	return (child);
}
