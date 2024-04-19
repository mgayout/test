/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/19 18:05:58 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer(t_data *data)
{
	t_lex	*lexer;
	int		i;

	i = 0;
	lexer = init_lexer();
	data->lexer = lex;
	while (data->prompt[i] != '\0')
	{
		if ((data->prompt[i] >= 9 && data->prompt[i] <= 13) || data->prompt[i] == ' ')
			i++;
		else
			add_new_t_lex(data, data->prompt[i]);
	}
}

void	add_new_t_lex(t_data *data, char *prompt)
{
	t_lex	*new;
	t_lex	*tmp;

	new = init_lexer();
	if (prompt[0] == '>' || prompt[0] == '<' || prompt[0] == '|')
		token_type(new, prompt);
	else
		string_type(new, prompt);
	tmp = data->lexer;
	while(tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tpm->next = new;
}

void	token_type(t_lex *lexer, char *prompt)
{
	t_lex	*tmp;

	if (ft_strncmp(prompt, ">>", 2))
	{
		lexer->type = REDIR;
		lexer->append = true;
		lexer->
	}
}

t_lex	*init_lexer(void)
{
	t_lex	*lexer;

	lexer = malloc(sizeof(t_lex));
	lexer->type = 0;
	lexer->data = NULL;
	lexer->infile = NULL;
	lexer->outfile = NULL;
	lexer->pipein = false;
	lexer->pipeout = false;
	lexer->heredoc = NULL;
	lexer->append = false;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}