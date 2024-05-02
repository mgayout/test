/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:26:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/02 17:58:21 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_par	*new_par(void)
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
	//new->infile = NULL;
	//new->outfile = NULL;
	new->pipein = false;
	new->pipeout = false;
	//new->heredoc = NULL;
	//new->append = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	init_tab_in(t_par *parser, t_lex *lexer)
{
	t_par	*tmp_par;
	t_lex	*tmp_lex;
	int		infile;
	int		heredoc;
	
	infile = 0;
	heredoc = 0;
	tmp_par = parser;
	tmp_lex = lexer;
	while(tmp_lex != NULL)
	{
		if (tmp_lex->redir == INFILE)
			infile++;
		else if (tmp_lex->redir == HEREDOC)
			heredoc++;
		else if (tmp_lex->type == PIPE)
			break;
		tmp_lex = tmp_lex->next;
	}
	if (infile == 0)
		tmp_par->infile = ft_calloc(1, sizeof(char*));
	else
	{
		tmp_par->infile = malloc(sizeof(char*) * infile + 1);
		tmp_par->infile[infile + 1] = NULL;
	}
	if (heredoc == 0)
		tmp_par->heredoc = ft_calloc(1, sizeof(char*));
	else
	{
		tmp_par->heredoc = malloc(sizeof(char*) * heredoc + 1);
		tmp_par->heredoc[heredoc + 1] = NULL;
	}
	printf("infile = %d\n", infile);
	printf("heredoc = %d\n", heredoc);
}

void	init_tab_out(t_par *parser, t_lex *lexer)
{
	t_par	*tmp_par;
	t_lex	*tmp_lex;
	int		outfile;
	int		append;
	
	outfile = 0;
	append = 0;
	tmp_par = parser;
	tmp_lex = lexer;
	while(tmp_lex != NULL)
	{
		if (tmp_lex->redir == OUTFILE)
			outfile++;
		else if (tmp_lex->redir == APPEND)
			append++;
		else if (tmp_lex->type == PIPE)
			break;
		tmp_lex = tmp_lex->next;
	}
	if (outfile == 0)
		tmp_par->outfile = ft_calloc(1, sizeof(char*));
	else
	{
		tmp_par->outfile = malloc(sizeof(char*) * outfile + 1);
		tmp_par->outfile[outfile + 1] = NULL;	
	}
	if (append == 0)
		tmp_par->append = ft_calloc(1, sizeof(char*));
	else
	{
		tmp_par->append = malloc(sizeof(char*) * append + 1);
		tmp_par->append[append + 1] = NULL;	
	}
	printf("outfile = %d\n", outfile);
	printf("append = %d\n", append);
}

int	nb_tab(char	**par_tab)
{
	int	i;

	i = 0;
	while (par_tab[i] != NULL)
		i++;
	printf("i = %d\n", i);
	return (i);
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