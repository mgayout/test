/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:54:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/26 11:17:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../minishell.h"
# include "../builtins/builtins.h"

//EXEC

void	exec(t_data *data);
void	exec_a_cmd(t_data *data);
void	exec_pipeline(t_data *data);

//EXEC_INIT

t_exe	*init_exe(t_par *parser);
void	init_child(t_data *data);
void	init_heredoc(t_data *data);

//EXEC_OPEN

void	open_pipe(t_data *data);
void	open_infile(t_data *data);
void	open_outfile(t_data *data);
void	open_files(t_data *data);

//EXEC_CMD

void	children(t_data *data);
char	*create_arg1(char *str);
char	**create_arg2(t_data *data);

#endif