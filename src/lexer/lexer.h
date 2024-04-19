/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/19 18:07:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../minishell.h"

typedef enum e_tok_type
{
	REDIR = 1,
	STRING,
	PIPE,
	
}	t_tok_type;

typedef enum e_tok_type
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
	
}	t_tok_redir;

t_lex	*lexlast(t_lex *lst);
int		lexsize(t_lex *lst);

#endif