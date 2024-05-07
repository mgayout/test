/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:54:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/07 14:51:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../minishell.h"
# include "../builtins/builtins.h"

//EXEC

void	exec(t_data *data);
void	exec_cmd(t_data *data);
void	exec_pipeline(t_data *data);

//EXEC_INIT

t_exe	*init_exe(t_par *parser);
void	init_child(t_data *data);
int		init_heredoc(t_data *data);

//EXEC_FILE_CMD

void	open_file_cmd(t_data *data);
void	infile_cmd(t_data *data);
void	infiles_cmd(t_data *data);
void	outfile_cmd(t_data *data);
void	outfiles_cmd(t_data *data);

//EXEC_FILE_PIPELINE

void	open_file_pipeline(t_data *data);
void	infile_pipeline(t_data *data);
void	outfile_pipeline(t_data *data);

//EXEC_FILES

int		open_infiles_cmd(t_data *data);
void	write_infile_temp(t_data *data, int count, int temp);
void	write_heredoc_temp(t_data *data, int count, int temp);
int		open_outfiles_cmd(t_data *data);

//EXEC_CMD

void	children(t_data *data);
char	*create_arg1(char *str);
char	**create_arg2(t_data *data);

#endif