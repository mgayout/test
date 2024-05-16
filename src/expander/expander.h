/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/16 12:06:18 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

//EXPANDER

void	expander(t_data *data);
void	dollar_parser(t_data *data, t_par *parser);

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

#endif