/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 14:05:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

//EXPANDER

void	expander(t_data *data);
void	dollar_parser(t_data *data, t_par *parser);

//EXPANDER_INIT

void	add_exp(t_exp **expander, t_par *parser);
void	add_exps(t_exp **expander, t_par *parser);
void	add_exp_outfile(t_exp **expander, t_par *parser, int i);
void	add_exp_pipeout(t_exp **expander, t_par *parser);

//EXPANDER_ENV

char	*env_var(t_data *data, char *str);
char	*search_env_var(t_data *data, char *str, int i);
char	*replace_str(char	*str, char	**value, int i, int j);
char	*replace_str2(t_data *data, char *str, int i, int j);


//EXPANDER_UTILS

char	*search_begin(char *str, int i);
char	*search_end(char *str, int i);
int		count_dollar(char *str);
char	**copy_tab(char **old);
void	print_exp(t_data *data);

//EXPANDER_FUNCTION

void	add_back_exp(t_exp **expander, t_exp *new);
t_exp	*explast(t_exp *lst);
int		expsize(t_exp *lst);

#endif