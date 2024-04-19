/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:57:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/19 11:58:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "../../minishell.h"

//LST_INIT

void	create_lst(t_lst **lst, char **arg);
void	fill_status(t_lst *lst);
void	fill_cmd(t_lst *lst);
void	fill_list(t_lst **lst, char *str);
void	set_lstargs(t_lst **lst, t_lst *new, char *str);

//LST_ARGS

char	*status_lst(t_lst *lst);
int		token_lst(char *str);
void	flag_arg(t_lst *lst);
void	before_cmd(t_lst *lst);
void	after_cmd(t_lst *lst);

//LST_IS_A

int		is_a_cmd(char *str);
void	is_a_builtins(t_lst *lst);
int		is_an_arg(t_lst **lst);
int		is_a_limiter(t_lst **lst);
int		is_a_file(t_lst **lst);

//LST_UTILS

void	print_lst(t_lst *lst);
void	free_lst(t_lst **s);
void	free_tab(char **tabtab);

//LST_FUNCTION

void	lstadd_back(t_lst **lst, t_lst *new);
t_lst	*lstlast(t_lst *lst);
int		lstsize(t_lst *lst);

#endif