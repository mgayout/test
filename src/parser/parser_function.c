/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:26:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/07 11:59:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_par	*new_par(t_lex *lexer)
{
	t_par	*new;

	new = (t_par *)ft_calloc(1, sizeof(t_par));
	if (!new)
		return (NULL);
	new->id = 0;
	new->status = 0;
	new->data = NULL;
	new->cmd = NULL;
	new->builtin = 0;
	new->arg = NULL;
	new->infile = init_tab(lexer, INFILE, HEREDOC);
	new->infile_count = 0;
	new->heredoc = init_tab(lexer, HEREDOC, INFILE);
	new->outfile = init_tab(lexer, OUTFILE, APPEND);
	new->outfile_count = 0;
	new->append = init_tab(lexer, APPEND, OUTFILE);
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

char	**init_tab(t_lex *lexer, t_lex_redir n, t_lex_redir o)
{
	t_lex	*tmp_lex;
	char	**new_tab;
	int		count;
	
	count = 0;
	tmp_lex = lexer;
	while(tmp_lex != NULL)
	{
		if (tmp_lex->redir == n || tmp_lex->redir == o)
			count++;
		else if (tmp_lex->type == PIPE)
			break;
		tmp_lex = tmp_lex->next;
	}
	if (count == 0)
		new_tab = NULL;
	else
	{
		new_tab = malloc(sizeof(char*) * (count + 1));
		new_tab[count] = NULL;
	}
	return (new_tab);
}

int	parsize(t_par *parser)
{
	int	size;

	size = 0;
	while (parser != NULL)
	{
		++size;
		parser = parser->next;
	}
	return (size);
}