/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:49:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/03 16:17:07 by mgayout          ###   ########.fr       */
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
	exec->nb_cmd = parsize(parser);
	exec->std_in = dup(0);
	exec->std_out = dup(1);
	exec->pid = malloc(sizeof(int) * exec->nb_cmd);
	exec->child = malloc(sizeof(t_pid) * exec->nb_cmd);
	return (exec);
}

/*void	init_child(t_data *data)
{
	t_par	*tmp;
	int		i;

	tmp = data->parser;
	i = data->exec->status;
	while (tmp != NULL)
	{
		if (i == (tmp->id - 1))
		{
			data->exec->child[i].lst = tmp;
			if (tmp->heredoc)
				data->exec->heredoc = true;
			return ;
		}
		tmp = tmp->next;
	}
}*/

int	init_heredoc(t_data *data)
{
	t_pid	pid;
	char	*buf;
	int		file;

	pid = data->exec->child[data->exec->status];
	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (ft_strncmp(buf, pid.lst->heredoc[0], ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(pid.lst->heredoc[0]) + 1)
			break ;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	return (open(".temp", O_RDONLY));
}
