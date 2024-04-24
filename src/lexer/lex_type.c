/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:26:41 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/24 17:01:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	token_type(t_lex *lexer, char *prompt)
{
	if (!ft_strncmp(prompt, ">>", 2))
	{
		lexer->type = REDIR;
		lexer->redir = APPEND;
		return (2);
	}
	else if (!ft_strncmp(prompt, ">", 1))
	{
		lexer->type = REDIR;
		lexer->redir = OUTFILE;
		return (1);
	}
	else if (!ft_strncmp(prompt, "<<", 2))
	{
		lexer->type = REDIR;
		lexer->redir = HEREDOC;
		return (2);
	}
	else if (!ft_strncmp(prompt, "<", 1))
	{
		lexer->type = REDIR;
		lexer->redir = INFILE;
		return (1);
	}
	else if (!ft_strncmp(prompt, "|", 1))
	{
		lexer->type = PIPE;
		return (1);
	}
	return (0);
}

int	string_type(t_data *data, t_lex *lexer, char *prompt)
{
	int	i;
	int	quotes;

	quotes = count_quotes(prompt);
	if (quotes % 2)
		return (0);
	i = 0;
	while (prompt[i] && !ft_strchr("><| \t\n\r\v\f", prompt[i]))
	{
		if (prompt[i] == '\'')
		{
			lexer->type = STRING;
			lexer->quote = QUOTE;
			i += data_quotes(data, lexer, prompt + (i + 1), "'");
			printf("end find prompt[i] = %c\n", prompt[i]);
		}
		else if (prompt[i] == '"')
		{
			lexer->type = STRING;
			lexer->quote = DQUOTE;
			i += data_quotes(data, lexer, prompt + (i + 1), "\"");
			printf("end find prompt[i] = %c\n", prompt[i]);
		}
		else
		{
			lexer->type = STRING;
			lexer->quote = NO_QUOTE;
			i += data_no_quote(data, lexer, prompt + i);
			printf("end find prompt[i] = %c\n", prompt[i]);
		}
	}
	return (i);
}


