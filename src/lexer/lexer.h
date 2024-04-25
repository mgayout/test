/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/25 14:09:56 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../minishell.h"

//LEXER

void	lexer(t_data *data, char *prompt);
int		add_new_t_lex(t_lex **lexer, char *prompt);

//LEX_TYPE

int		token_type(t_lex *lexer, char *prompt);
int		string_type(t_lex *lexer, char *prompt);

//LEX_QUOTE

int		count_quotes(char *prompt);
int		data_no_quote(t_lex *lexer, char *prompt);
int		data_quotes(t_lex *lexer, char *prompt, char *limiter);
//void	env_lex_data(t_data *data, t_lex *lexer, char *prompt, int nb_dollar, int j);
void	init_lex_data(t_lex *lexer, char *prompt, int i);
void	join_lex_data(t_lex *lexer, char *prompt, int i);

//LEX_ENV

/*int		find_var(t_data *data, t_lex *lexer, char *prompt);
char	*join_var_val(t_env *env);
void	init_lex_data_env(t_lex *lexer, char *prompt, int i);
void	join_lex_data_env(t_lex *lexer, char *prompt, int i);*/

//LEX_UTILS

int		check_dollar(char *prompt, int i);
void	print_lex(t_data *data);

//LEX_FUNCTION

t_lex	*new_lex(void);
t_lex	*lexlast(t_lex *lst);
int		lexsize(t_lex *lst);
void	lexadd_back(t_lex **lst, t_lex *new);

#endif