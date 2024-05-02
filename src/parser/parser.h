/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:55:30 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/02 17:31:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishell.h"

//PARSER

void	parser(t_data *data);
int		addlex_topar(t_par *parser, t_lex *lexer);
void	first_elem(t_par *parser, t_lex *lexer);
void	x_elem(t_par *parser, t_lex *lexer);
void	last_elem(t_par *parser);

//PARSER_UTILS

void	add_string_par(t_par *parser, t_lex *lexer);
void	add_redir_par(t_par *parser, t_lex *lexer);
int		is_a_builtin(char *cmd);
char	*join_data_par(char *old, char *str);
void	print_par(t_data *data);

//PARSER_FUNCTION

t_par	*new_par(void);
void	init_tab_in(t_par *parser, t_lex *lexer);
void	init_tab_out(t_par *parser, t_lex *lexer);
int		nb_tab(char	**par_tab);
int		parsize(t_par *parser);

#endif