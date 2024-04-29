/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/29 17:50:16 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../minishell.h"

//LEXER

void	lexer(t_data *data);
int		add_new_t_lex(t_data *data, t_lex **lexer, char *prompt);

//LEX_TYPE

int		token_type(t_lex *lexer, char *prompt);
int		string_type(t_data *data, t_lex *lexer);

//LEX_QUOTE

int		count_quotes(char *prompt);
int		data_no_quote(t_lex *lexer, char *prompt);
int		data_quotes(t_lex *lexer, char *prompt, char *limiter);
void	init_lex_data(t_lex *lexer, char *prompt, int i, t_lex_quote n);
void	join_lex_data(t_lex *lexer, char *prompt, int i, t_lex_quote n);
char	*add_final_quote(char *prompt);
char	*join_final_quote(char *prompt, char *buf, int i);

//LEX_UTILS

int		check_dollar(char *prompt, int i);
void	print_lex(t_data *data);

//LEX_FUNCTION

t_lex	*new_lex(void);
t_lex	*lexlast(t_lex *lst);
int		lexsize(t_lex *lst);
void	lexadd_back(t_lex **lst, t_lex *new);

#endif