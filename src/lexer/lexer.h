/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/23 17:50:34 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../minishell.h"

//LEXER

void	lexer(t_data *data, char *prompt);
int		add_new_t_lex(t_lex **lexer, char *prompt);
int		token_type(t_lex *lexer, char *prompt);
t_lex	*init_lexer(void);
int		string_type(t_lex *lexer, char *prompt);
int		*add_new_enum(t_lex *lexer, int *quote, t_lex_quote n);
int		find_content(char *str, char *limiter, t_lex *lexer, int status);
int		count_quotes(char *prompt);

//LEX_UTILS

void	print_lex(t_data *data);

//LEX_FUNCTION

t_lex	*lexlast(t_lex *lst);
int		lexsize(t_lex *lst);
void	lexadd_back(t_lex **lst, t_lex *new);

#endif