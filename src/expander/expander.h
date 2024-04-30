/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/30 17:59:25 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

void	expander(t_data *data);
void	modify_parser(t_data *data, t_par *parser);
char	*env_var(t_data * data, char *str);
char	*search_env_var(t_data *data, char *str, int i);
char	*replace_str(char	*str, char	**value, int i, int j);
char	*search_begin(char *str, int i);
char	*search_end(char *str, int i);
int		count_dollar(char *str);

#endif