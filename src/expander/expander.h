/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 18:29:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

//EXPANDER

void	expander(t_data *data);
t_exp	*init_expander(t_par *parser);
void	dollar_expander(t_data *data, t_exp *expander);

//EXPANDER_ENV

char	*modify_expander(t_data *data, char *str);
char	*modify_str(char *new, char *str, int i);
char	*search_var(t_data *data, char *str, int i);

//EXPANDER_UTILS

char	*search_begin(char *str, int i);
char	*search_end(char *str, int i);
int		count_dollar(char *str);
char	**copy_tab(char **old);
int		is_a_builtin(char *cmd);
void	print_exp(t_data *data);

//EXPANDER_FUNCTION

t_exp	*explast(t_exp *lst);
int		expsize(t_exp *lst);
void	expadd_back(t_exp **lst, t_exp *new);

#endif