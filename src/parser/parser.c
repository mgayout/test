/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 17:29:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_data *data)
{
	t_par	*par_tmp;
	t_lex	*lex_tmp;
	
	data->parser = new_par();
	par_tmp = data->parser;
	lex_tmp = data->lexer;
	while (lex_tmp != NULL)
	{
		if (init_parser(par_tmp, lex_tmp))
			par_tmp = par_tmp->next;
		lex_tmp = lex_tmp->next;
	}
}

int	init_parser(t_par *parser, t_lex *lexer)
{
	if (parser->id == 0)
	{
		if (parser->prev == NULL)
			parser->id = 1;
		else
			parser->id = parser->prev->id + 1;
		if (lexer->type == STRING)
			first_string(parser, lexer);
		else if (lexer->type == REDIR)
			parser->status = 2;
	}
	else if (lexer->type != PIPE)
	{
		if (lexer->type == STRING
		&& (lexer->prev->redir == INFILE || lexer->prev->redir == HEREDOC))
			infile_parser(parser, lexer);
		else if (lexer->type == STRING
		&& (lexer->prev->redir == OUTFILE || lexer->prev->redir == APPEND))
			outfile_parser(parser, lexer);
		else if (lexer->type == STRING)
			cmd_arg_parser(parser, lexer);
	}
	else
		return (last_parser(parser));
	return (0);
}

int	last_parser(t_par *parser)
{
	t_par	*new;

	new = new_par();
	parser->pipeout = true;
	new->pipein = true;
	new->prev = parser;
	parser->next = new;
	return (1);
}

void	print_par(t_data *data)
{
	t_par	*parser;

	parser = data->parser;
	while (parser)
	{
		printf("id = %d\n", parser->id);
		while (parser->cmd)
		{
			if (parser->cmd->id != 0)
				printf("cmd id = %d\n", parser->cmd->id);
			printf("cmd = %s\n", parser->cmd->str);
			parser->cmd = parser->cmd->next;
		}
		while (parser->arg)
		{
			printf("arg = %s\n", parser->arg->str);
			parser->arg = parser->arg->next;
		}
		printf("infile count = %d\n", parser->infile_count);
		while (parser->infile)
		{
			if (parser->infile->heredoc == true)
			{
				printf("limiter = %s\n", parser->infile->str);
			}
			else
				printf("infile = %s\n", parser->infile->str);
			parser->infile = parser->infile->next;
		}
		printf("outfile count = %d\n", parser->outfile_count);
		while (parser->outfile)
		{
			printf("outfile = %s\n", parser->outfile->str);
			parser->outfile = parser->outfile->next;
		}
		if (parser->pipein)
			printf("pipein true\n");
		if (parser->pipeout)
			printf("pipeout true\n");
		printf("\n");
		parser = parser->next;
	}
}
