/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:49:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/16 13:28:11 by mgayout          ###   ########.fr       */
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
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->status, "cmd", 4) && cmd == i)
		{
			data->exec->child[i].lst = tmp;
			if (tmp->infile)
				data->exec->child[i].infile = open(tmp->infile, O_RDONLY);
			if (tmp->outfile && tmp->append)
				data->exec->child[i].outfile = open(tmp->outfile, O_WRONLY | O_CREAT | O_APPEND, 0640);
			else if (tmp->outfile && !tmp->append)
				data->exec->child[i].outfile = open(tmp->outfile, O_RDWR | O_TRUNC | O_CREAT, 0640);
			return ;
		}
		else if (!ft_strncmp(tmp->status, "cmd", 4) && cmd != i)
			cmd++;
		tmp = tmp->next;
	}
}

void	init_heredoc(t_data *data)
{
	char	*buf;
	int		file;
	int		i;

	i = 0;
	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		while (++i < data->exec->nb_cmd)
			write(1, "pipe ", ft_strlen("pipe "));
		write(1, "heredoc> ", ft_strlen("heredoc> "));
		buf = get_next_line(0);
		if (ft_strncmp(buf, data->exec->child[data->exec->status].lst->heredoc, ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(data->exec->child[data->exec->status].lst->heredoc) + 1)
			break ;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
		i = 0;
	}
	free(buf);
	close(file);
}