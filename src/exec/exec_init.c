/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:49:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/12 11:16:05 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exec(t_data *data)
{
	t_arg	*tmp;

	tmp = data->lst;
	data->exec->status = 0;
	data->exec->nb_arg = lstsize(tmp);
	data->exec->nb_cmd = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->status, "cmd", 4))
			data->exec->nb_cmd += 1;
		tmp = tmp->next;
	}
	data->exec->pid = malloc(sizeof(int) * data->exec->nb_cmd);
	data->exec->child = malloc(sizeof(t_pid) * data->exec->nb_cmd);
}

void	init_child(t_data *data)
{
	t_arg	*tmp;
	int		cmd;
	int		i;

	i = data->exec->status;
	cmd = 0;
	tmp = data->lst;
	data->exec->child[i].pipein = false;
	data->exec->child[i].pipeout = false;
	data->exec->child[i].std_in = false;
	data->exec->child[i].std_out = false;
	while (tmp != NULL)
	{
		//printf("data = %s && status = %s\n", tmp->data, tmp->status);
		//printf("cdm = %d && i = %d\n", cmd, i);
		if (!ft_strncmp(tmp->status, "cmd", 4) && cmd == i)
		{
			//printf("if : data = %s\n", tmp->data);
			data->exec->child[i].cmd = ft_strdup(tmp->data);
			if (tmp->next != NULL)
			{
				if (!ft_strncmp(tmp->next->status, "arg", 4))
					data->exec->child[i].arg = ft_strdup(tmp->next->data);
				else if (!ft_strncmp(tmp->next->status, "flag", 5))
					data->exec->child[i].flag = ft_strdup(tmp->next->data);
			}
			if (tmp->infile)
				data->exec->child[i].infile = open(tmp->infile, O_RDONLY);
			if (tmp->outfile)
				data->exec->child[i].outfile = open(tmp->outfile, O_WRONLY
				| O_CREAT | O_APPEND, 0777);
			if (tmp->pipein)
				data->exec->child[i].pipein = true;
			if (tmp->pipeout)
				data->exec->child[i].pipeout = true;
			if (!tmp->infile && !tmp->pipein)
				data->exec->child[i].std_in = true;
			if (!tmp->outfile && !tmp->pipeout)
				data->exec->child[i].std_out = true;
			//printf("cmd %s\n", data->exec->child[i].cmd);
			return ;
		}
		else if (!ft_strncmp(tmp->status, "cmd", 4) && cmd != i)
			cmd++;
		tmp = tmp->next;
	}
}