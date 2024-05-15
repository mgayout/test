/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:53:27 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 11:10:30 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file_cmd(t_data *data, t_pid child, bool infile)
{
	if (infile == true)
	{
		if (child.lst->infile_count <= 1)
			child.infile = infile_cmd(data, child);
		else
			child.infile = infiles_cmd(data, child);	
	}
	else
		child.infile = infile_cmd_bool(data, child);
	child.outfile = outfile_cmd(data, child);
	dup2(child.infile, STDIN_FILENO);
	dup2(child.outfile, STDOUT_FILENO);
}

int	infile_cmd(t_data *data, t_pid child)
{
	int	infile;

	if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "false", ft_strlen("false")))
		infile = open(child.lst->infile[0], O_RDONLY);
	else if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "true", ft_strlen("true")))
	{
		infile = init_heredoc(data, child.lst->infile[0]);
		data->exec->temp = true;	
	}
	else
		infile = data->exec->std_in;
	return(infile);
}

int	infiles_cmd(t_data *data, t_pid child)
{
	int		infile;
	int		file;

	infile = 0;
	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	close(file);
	while (infile != child.lst->infile_count)
	{
		if (!ft_strncmp(child.lst->heredoc[infile], "false", ft_strlen("false")))
			write_infile_temp(child, infile, file);
		else
			write_heredoc_temp(data, child, infile, file);
		infile++;
	}
	data->exec->temp = true;
	return(open(".temp", O_RDONLY));
}

int	infile_cmd_bool(t_data *data, t_pid child)
{
	int	infile;

	if (child.lst->infile_count == 0)
		infile = data->exec->std_in;
	else if (child.lst->infile_count == 1
		&& !ft_strncmp(child.lst->heredoc[0], "false", ft_strlen("false")))
		infile = open(child.lst->infile[0], O_RDONLY);
	else
		infile = open(".temp", O_RDONLY);
	return (infile);
}

int	outfile_cmd(t_data *data, t_pid child)
{
	if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "false", ft_strlen("false")))
		child.outfile = open(child.lst->outfile[0], O_RDWR | O_TRUNC | O_CREAT, 0640);
	else if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "true", ft_strlen("true")))
		child.outfile = open(child.lst->outfile[0], O_WRONLY | O_CREAT | O_APPEND, 0640);
	else
		child.outfile = data->exec->std_out;
	return (child.outfile);
}
