/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/03 16:09:40 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_data *data)
{
	t_par	*par_tmp;
	t_lex	*lex_tmp;
	
	data->parser = new_par(data->lexer);
	par_tmp = data->parser;
	lex_tmp = data->lexer;
	while (lex_tmp != NULL)
	{
		if (addlex_topar(par_tmp, lex_tmp))
			par_tmp = par_tmp->next;
		else
			lex_tmp = lex_tmp->next;
	}
}

int	addlex_topar(t_par *parser, t_lex *lexer)
{
	if (parser->id == 0)
		first_elem(parser, lexer);
	else if (lexer->type != PIPE)
		x_elem(parser, lexer);
	else
	{
		last_elem(parser, lexer);
		return (1);
	}
	return (0);
}

void	first_elem(t_par *parser, t_lex *lexer)
{
	if (parser->prev == NULL)
		parser->id = 1;
	else
		parser->id = parser->prev->id + 1;
	if (lexer->type == STRING)
	{
		parser->cmd = ft_strdup(lexer->data);
		parser->builtin = is_a_builtin(lexer->data);
		parser->data = ft_strdup(lexer->data);
		parser->status = 1;
	}
	else if (lexer->type == REDIR)
	{
		if (lexer->redir == INFILE)
			parser->data = ft_strdup("<");
		else if (lexer->redir == OUTFILE)
			parser->data = ft_strdup(">");
		else if (lexer->redir == HEREDOC)
			parser->data = ft_strdup("<<");
		else if (lexer->redir == APPEND)
			parser->data = ft_strdup(">>");
		parser->status = 2;
	}
}

void	x_elem(t_par *parser, t_lex *lexer)
{
	if (lexer->type == STRING)
		add_string_par(parser, lexer);
	else if (lexer->type == REDIR)
		add_redir_par(parser, lexer);
}

void	last_elem(t_par *parser, t_lex *lexer)
{
	t_par	*new;

	new = new_par(lexer->next);
	parser->pipeout = true;
	parser->data = join_data_par(parser->data, "|");
	new->pipein = true;
	new->prev = parser;
	parser->next = new;
}
