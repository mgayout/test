/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:26:41 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/29 17:49:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	token_type(t_lex *lexer, char *prompt)
{
	lexer->type = REDIR;
	if (!ft_strncmp(prompt, ">>", 2))
		lexer->redir = APPEND;
	else if (!ft_strncmp(prompt, ">", 1))
		lexer->redir = OUTFILE;
	else if (!ft_strncmp(prompt, "<<", 2))
		lexer->redir = HEREDOC;
	else if (!ft_strncmp(prompt, "<", 1))
		lexer->redir = INFILE;
	else if (!ft_strncmp(prompt, "|", 1))
		lexer->type = PIPE;
	if (!ft_strncmp(prompt, "<<", 2) || !ft_strncmp(prompt, ">>", 2))
		return (2);
	return (1);
}

int	string_type(t_data *data, t_lex *lexer)
{
	int	i;

	i = 0;
	lexer->type = STRING;
	while (data->prompt[i] && !ft_strchr("><| \t\n\r\v\f", data->prompt[i]))
	{
		//printf("entree : %s\n", &prompt[i]);
		if (data->prompt[i] == '\'' || data->prompt[i] == '"')
		{
			while (count_quotes(data->prompt))
				data->prompt = add_final_quote(data->prompt);
			//printf("mid : %s\n", data->prompt);
			if (data->prompt[i] == '\'')
				i += data_quotes(lexer, data->prompt + (i + 1), "'");
			else if (data->prompt[i] == '"')
				i += data_quotes(lexer, data->prompt + (i + 1), "\"");
		}
		else
			i += data_no_quote(lexer, data->prompt + i);
		//printf("sortie : %s\n", &prompt[i]);
	}
	return (i);
}


