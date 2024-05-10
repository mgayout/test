/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:54:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/10 18:24:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../minishell.h"
# include "../builtins/builtins.h"

//EXEC

void	exec(t_data *data);
void	exec_cmd_file(t_data *data);
void	exec_pipeline(t_data *data);

//EXEC_INIT

t_exe	*init_exe(t_par *parser);
t_pid	init_child(t_data *data);

//EXEC_FILE_CMD

void	open_file_cmd(t_data *data);
int		infile_cmd(t_data *data);
int		infiles_cmd(t_data *data);
int		outfile_cmd(t_data *data);
int		outfiles_cmd(t_data *data);

//EXEC_FILE_PIPELINE

void	open_file_pipeline(t_data *data);
void	infile_pipeline(t_data *data);
void	infiles_pipeline(t_data *data);
void	outfile_pipeline(t_data *data);
void	outfiles_pipeline(t_data *data);

//EXEC_UTILS

int		init_heredoc(t_data *data, char *stop);
void	write_infile_temp(t_data *data, int count, int temp);
void	write_heredoc_temp(t_data *data, int count, int temp);
void	write_pipe_temp(int pipe, int temp);

//EXEC_CMD

void	children(t_data *data);
char	*create_arg1(char *str);
char	**create_arg2(t_data *data);

#endif