/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:53:27 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/13 13:21:50 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file_cmd(t_data *data)
{
	t_pid	child;

	child = data->exec->child[data->exec->status];
	if (child.lst->infile_count <= 1)
		child.infile = infile_cmd(data);
	else
		child.infile = infiles_cmd(data);
	if (child.lst->outfile_count <= 1)
		child.outfile = outfile_cmd(data);
	else
		child.outfile = outfiles_cmd(data);
	dup2(child.infile, STDIN_FILENO);
	dup2(child.outfile, STDOUT_FILENO);
}

int	infile_cmd(t_data *data)
{
	printf("infile\n");
	t_pid	child;

	child = data->exec->child[data->exec->status];
	if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "false", ft_strlen("false")))
		child.infile = open(child.lst->infile[0], O_RDONLY);
	else if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "true", ft_strlen("true")))
		child.infile = init_heredoc(data, child.lst->infile[0]);
	else
		child.infile = data->exec->std_in;
	return(child.infile);
}

int	infiles_cmd(t_data *data)
{
	printf("infiles\n");
	t_pid	child;
	int		infile;
	int		file;

	child = data->exec->child[data->exec->status];
	infile = 0;
	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	close(file);
	while (infile != child.lst->infile_count)
	{
		if (!ft_strncmp(child.lst->heredoc[infile], "false", ft_strlen("false")))
			write_infile_temp(data, infile, file);
		else
			write_heredoc_temp(data, infile, file);
		infile++;
	}
	return(open(".temp", O_RDONLY));
}

int	outfile_cmd(t_data *data)
{
	printf("outfile\n");
	t_pid	child;
	
	child = data->exec->child[data->exec->status];
	if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "false", ft_strlen("false")))
		child.outfile = open(child.lst->outfile[0], O_RDWR | O_TRUNC | O_CREAT, 0640);
	else if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "true", ft_strlen("true")))
		child.outfile = open(child.lst->outfile[0], O_WRONLY | O_CREAT | O_APPEND, 0640);
	else
		child.outfile = data->exec->std_out;
	return (child.outfile);
}

int	outfiles_cmd(t_data *data)
{
	printf("outfiles\n");
	t_pid	child;
	int		outfile;
	
	child = data->exec->child[data->exec->status];
	outfile = 0;
	while (outfile != child.lst->outfile_count)
	{
		if (outfile != child.lst->outfile_count - 1)
			child.pid[outfile] = fork();
		if (!ft_strncmp(child.lst->append[outfile], "false", ft_strlen("false")))
			child.outfile = open(child.lst->outfile[outfile], O_RDWR | O_TRUNC | O_CREAT, 0640);
		else if (!ft_strncmp(child.lst->append[outfile], "true", ft_strlen("true")))
			child.outfile = open(child.lst->outfile[outfile], O_WRONLY | O_CREAT | O_APPEND, 0640);
		if (!child.pid[outfile])
			break;
		outfile++;
	}
	return (child.outfile);
}
