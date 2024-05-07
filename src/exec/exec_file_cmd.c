/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:53:27 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/07 16:53:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file_cmd(t_data *data)
{
	t_pid	child;

	child = data->exec->child[data->exec->status];
	if (child.lst->infile_count <= 1)
		infile_cmd(data);
	else
		infiles_cmd(data);
	if (child.lst->outfile_count <= 1)
		outfile_cmd(data);
	else
		outfiles_cmd(data);
}

void	infile_cmd(t_data *data)
{
	t_pid	child;

	child = data->exec->child[data->exec->status];
	if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "false", ft_strlen("false")))
		child.infile = open(child.lst->infile[0], O_RDONLY);
	else if (child.lst->infile_count == 1 && !ft_strncmp(child.lst->heredoc[0], "true", ft_strlen("true")))
		child.infile = init_heredoc(data);
	else
		child.infile = data->exec->std_in;
	dup2(child.infile, STDIN_FILENO);
}

void	infiles_cmd(t_data *data)
{
	t_pid	child;
	int		infile;
	int		file;

	child = data->exec->child[data->exec->status];
	infile = 0;
	file = open(".temp", O_WRONLY | O_APPEND | O_CREAT, 0777);
	while (infile != child.lst->infile_count)
	{
		if (!ft_strncmp(child.lst->heredoc[infile], "false", ft_strlen("false")))
			write_infile_temp(data, infile, file);
		else
			write_heredoc_temp(data, infile, file);
		infile++;
	}
	close(file);
	child.infile = open(".temp", O_RDONLY);
	dup2(child.infile, STDIN_FILENO);
}

void	outfile_cmd(t_data *data)
{
	t_pid	child;
	
	child = data->exec->child[data->exec->status];
	if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "false", ft_strlen("false")))
		child.outfile = open(child.lst->outfile[0], O_RDWR | O_TRUNC | O_CREAT, 0640);
	else if (child.lst->outfile_count == 1 && !ft_strncmp(child.lst->append[0], "true", ft_strlen("true")))
		child.outfile = open(child.lst->outfile[0], O_WRONLY | O_CREAT | O_APPEND, 0640);
	else
		child.outfile = data->exec->std_out;
	dup2(child.outfile, STDOUT_FILENO);
}

void	outfiles_cmd(t_data *data) //a modifie !
{
	/*t_pid	child;
	int		*pid;
	int		outfile;
	
	child = data->exec->child[data->exec->status];
	pid = malloc(sizeof(int) * (child.lst->outfile_count - 1));
	outfile = 0;
	while (outfile != (child.lst->outfile_count - 1))
	{
		pid[outfile] = fork();
		if (!pid[outfile])
		{
			if (!ft_strncmp(child.lst->append[outfile], "false", ft_strlen("false")))
				dup2(open(child.lst->outfile[outfile], O_RDWR | O_TRUNC | O_CREAT, 0640), STDOUT_FILENO);
			else
				dup2(open(child.lst->outfile[outfile], O_WRONLY | O_CREAT | O_APPEND, 0640), STDOUT_FILENO);
			break ;
		}
		outfile++;
	}
	if (!data->exec->pid[data->exec->status])
	{
		if (!ft_strncmp(child.lst->append[outfile], "false", ft_strlen("false")))
			dup2(open(child.lst->outfile[outfile], O_RDWR | O_TRUNC | O_CREAT, 0640), STDOUT_FILENO);
		else
			dup2(open(child.lst->outfile[outfile], O_WRONLY | O_CREAT | O_APPEND, 0640), STDOUT_FILENO);
		waitpid(pid[outfile - 1], NULL, 0);
	}*/
}
