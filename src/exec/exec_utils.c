/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:35:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/13 13:02:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	init_heredoc(t_data *data, char *stop)
{
	char	*buf;
	int		file;

	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		write(data->exec->std_out, "> ", 2);
		buf = get_next_line(data->exec->std_in);
		if (ft_strncmp(buf, stop, ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(stop) + 1)
			break ;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	return (open(".temp", O_RDONLY));
}

void	write_infile_temp(t_data *data, int count, int temp)
{
	char	*buf;
	int		file;
	
	file = open(data->parser->infile[count], O_RDONLY);
	temp = open(".temp", O_WRONLY | O_APPEND | O_CREAT, 0777);
	while (1)
	{
		buf = get_next_line(file);
		if (!buf)
			break ;
		else
			write(temp, buf, ft_strlen(buf));
		free(buf);
	}
	close(file);
	close(temp);
}

void	write_heredoc_temp(t_data *data, int count, int temp)
{
	t_pid	child;
	char	*buf;

	child = data->exec->child[data->exec->status];
	temp = open(".temp", O_WRONLY | O_APPEND | O_CREAT, 0777);
	while (1)
	{
		write(data->exec->std_out, "> ", 2);
		buf = get_next_line(data->exec->std_in);
		if (ft_strncmp(buf, child.lst->infile[count], ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(child.lst->infile[count]) + 1)
			break ;
		else
			write(temp, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(temp);
}

void	write_pipe_temp(int pipe, int temp)
{
	char	*buf;

	while (1)
	{
		buf = get_next_line(pipe);
		if (!buf)
			break ;
		else
			write(temp, buf, ft_strlen(buf));
		free(buf);
	}
}
