/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:49:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/18 17:47:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exec(t_data *data)
{
	t_lst	*tmp;

	tmp = data->lst;
	data->exec->status = 0;
	data->exec->nb_arg = lstsize(tmp);
	data->exec->nb_cmd = 0;
	data->exec->std_in = dup(0);
	data->exec->std_out = dup(1);
	data->exec->heredoc = false;
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
	t_lst	*tmp;
	int		cmd;
	int		i;

	i = data->exec->status;
	cmd = 0;
	tmp = data->lst;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->status, "cmd", 4) && cmd == i)
		{
			data->exec->child[i].lst = tmp;
			if (tmp->heredoc)
				data->exec->heredoc = true;
			return ;
		}
		else if (!ft_strncmp(tmp->status, "cmd", 4) && cmd != i)
			cmd++;
		tmp = tmp->next;
	}
}

void	init_heredoc(t_data *data)
{
	t_pid	pid;
	char	*buf;
	int		file;
	int		i;

	pid = data->exec->child[data->exec->status];
	i = 0;
	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		while (++i < data->exec->nb_cmd)
			write(1, "pipe ", ft_strlen("pipe "));
		write(1, "heredoc> ", ft_strlen("heredoc> "));
		buf = get_next_line(0);
		if (ft_strncmp(buf, pid.lst->heredoc, ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(pid.lst->heredoc) + 1)
			break ;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
		i = 0;
	}
	free(buf);
	close(file);
}
