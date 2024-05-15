/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:54:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 15:45:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../minishell.h"
# include "../builtins/builtins.h"

//EXEC

void	exec(t_data *data);
void	exec_cmd_file(t_data *data);
void	exec_cmd_files(t_data *data);
void	exec_pipeline(t_data *data);

//EXEC_INIT

t_exe	*init_exe(t_par *parser);
t_pid	init_child(t_data *data);
int		find_nb_out(t_exp *lst);

//EXEC_FILE_CMD

void	open_file_cmd(t_data *data, t_pid child, bool infile);
int		infile_cmd(t_data *data, t_pid child);
int		infiles_cmd(t_data *data, t_pid child);
int		infile_cmd_bool(t_data *data, t_pid child);
int		outfile_cmd(t_data *data, t_pid child);

//EXEC_FILE_PIPELINE

void	open_file_pipeline(t_data *data, t_pid child, int out);
void	infile_pipeline(t_data *data, t_pid child);
void	infiles_pipeline(t_data *data, t_pid child);
void	infile_pipeline_bool(t_data *data, t_pid child);
void	outfile_pipeline(t_data *data, t_pid child);

//EXEC_UTILS

int		init_heredoc(t_data *data, char *stop);
void	write_infile_temp(t_pid child, int count, int temp);
void	write_heredoc_temp(t_data *data, t_pid child, int count, int temp);
void	write_pipe_temp(int pipe, int temp);
void	create_all_files(t_data *data, t_pid child);

//EXEC_CMD

void	children(t_data *data, t_pid child);
char	*create_arg1(char *str);
char	**create_arg2(t_pid child);

#endif