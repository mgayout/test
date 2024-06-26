/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 18:14:32 by mgayout          ###   ########.fr       */
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

int		data_noquote(t_lex *lexer, char *prompt, char *limiter);
int		data_quote(t_lex *lexer, char *prompt, char *limiter);
char	*add_final_quote(char *prompt);

//LEX_UTILS

int		count_quotes(char *prompt);
void	print_lex(t_data *data);

//LEX_FUNCTION

t_lex	*new_lex(void);
t_lex	*lexlast(t_lex *lst);
int		lexsize(t_lex *lst);
void	lexadd_back(t_lex **lst, t_lex *new);

//LSTR_FUNCTION

t_lstr	*new_lstr(char *str, t_lex_quote n);
t_lstr	*lstrlast(t_lstr *lst);
int		lstrsize(t_lstr *lst);
void	lstradd_back(t_lstr **lst, t_lstr *new);
char	*lstrjoin(t_lstr *lst);

#endif