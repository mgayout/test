/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:07:44 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/07 14:21:55 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	write_infile_temp(t_data *data, int count, int temp)
{
	char	*buf;
	int		file;
	
	file = open(data->parser->infile[count], O_RDONLY);
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
}

void	write_heredoc_temp(t_data *data, int count, int temp)
{
	char	*buf;

	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (ft_strncmp(buf, data->exec->child->lst->infile[count], ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(data->exec->child->lst->infile[count]) + 1)
			break ;
		else
			write(temp, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
}

int	open_outfiles_cmd(t_data *data)
{
	int	*pid;
	int	outfile;

	pid = malloc(sizeof(int) * (data->exec->child[0].lst->outfile_count - 1));
	outfile = 0;
	while (outfile != (data->exec->child[0].lst->outfile_count - 1))
	{
		pid[outfile] = fork();
		if (!pid[outfile])
		{
			printf("1\n");
			if (!ft_strncmp(data->exec->child->lst->append[outfile], "false", ft_strlen("false")))
				return (open(data->exec->child[0].lst->outfile[outfile], O_RDWR | O_TRUNC | O_CREAT, 0640));
			else
				return (open(data->exec->child[0].lst->outfile[outfile], O_WRONLY | O_CREAT | O_APPEND, 0640));
		}
		waitpid(data->exec->pid[0], NULL, 0);
		outfile++;
	}
	if (!data->exec->child[0].outfile)
	{
		printf("2\n");
		if (!ft_strncmp(data->exec->child->lst->append[outfile], "false", ft_strlen("false")))
			return (open(data->exec->child[0].lst->outfile[outfile], O_RDWR | O_TRUNC | O_CREAT, 0640));
		else
			return (open(data->exec->child[0].lst->outfile[outfile], O_WRONLY | O_CREAT | O_APPEND, 0640));
	}
	return (0);
}











/*void	open_infiles_pipe(t_data *data)
{

}

void	open_outfiles_pipe(t_data *data)
{
	
}*/