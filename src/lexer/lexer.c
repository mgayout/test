/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/23 17:51:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer(t_data *data, char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i])
	{
		while ((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == ' ')
			i++;
		i += add_new_t_lex(&data->lexer, &prompt[i]);
	}
}

int	add_new_t_lex(t_lex **lexer, char *prompt)
{
	t_lex	*new;
	int		i;

	i = 0;
	new = init_lexer();
	if (prompt[0] == '>' || prompt[0] == '<' || prompt[0] == '|')
		i = token_type(new, prompt);
	else
		i = string_type(new, prompt);
	lexadd_back(lexer, new);
	return (i);
}

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

int	string_type(t_lex *lexer, char *prompt)
{
	int	i;
	int	quotes;

	quotes = count_quotes(prompt);
	if (quotes % 2)
		return (0);
	if (!quotes)
		lexer->quote = malloc(sizeof(int));
	else
		lexer->quote = malloc(sizeof(int) * ((quotes * 2) + 1));
	i = 0;
	while (prompt[i] && !ft_strchr("><| \t\n\r\v\f", prompt[i]))
	{
		printf("prompt[i] = %c\n", prompt[i]);
		if (prompt[i] == '\'')
		{
			lexer->type = STRING;
			//lexer->quote = add_new_enum(lexer, lexer->quote, QUOTE);
			lexer->quote[lexer->quote_id] = QUOTE;
			i += find_content(prompt + i, "'", lexer, 1);
			lexer->quote_id += 1;
		}
		else if (prompt[i] == '"')
		{
			lexer->type = STRING;
			//lexer->quote = add_new_enum(lexer, lexer->quote, DQUOTE);
			lexer->quote[lexer->quote_id] = DQUOTE;
			i += find_content(prompt + i, "\"", lexer, 1);
			lexer->quote_id += 1;
		}
		else
		{
			lexer->type = STRING;
			//lexer->quote = add_new_enum(lexer, lexer->quote, NO_QUOTE);
			lexer->quote[lexer->quote_id] = NO_QUOTE;
			i += find_content(prompt + i, "\"'><| \t\n\r\v\f", lexer, 0);
			lexer->quote_id += 1;
		}
	}
	return (i);
}

/*int	*add_new_enum(t_lex *lexer, int *quote, t_lex_quote n)
{
	int	*new;
	int	i;

	i = 0;
	if (!quote)
		quote = malloc(sizeof(int));
	else
	{
		new = malloc(sizeof(int) * (lexer->quote_id + 1));
		while (i < lexer->quote_id)
		{
			new[i] = quote[i];
			i++;
		}
		free(quote);
		new[i] = n;
	}
	return (new);
}*/

int	find_content(char *str, char *limiter, t_lex *lexer, int status)
{
	int		i;
	char	*tmp;
	char	*stock;

	i = 0;
	while (str[i] && (ft_strchr(limiter, str[i]) == NULL || i == 0))
		i++;
	if ((str[i] == '\'' || str[i] == '"') && status == 1)
		i++;
	if (i)
	{
		tmp = ft_calloc(sizeof(char), (i + 1));
		ft_strncpy(tmp, str, i);
		if (!lexer->data)
			lexer->data = ft_strdup(tmp);
		else
		{
			stock = ft_strjoin(lexer->data, tmp);
			if (ft_strlen(lexer->data) != 0 && lexer->type == STRING)
				free(lexer->data);
			lexer->data = ft_strdup(stock);
			free(stock);
		}
		free(tmp);
	}
	return (i);
}

int	count_quotes(char *prompt)
{
	int	i;
	int status;
	int	dquotes;
	int	quotes;
	int	total;

	i = 0;
	status = 0;
	quotes = 0;
	dquotes = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && status != 2)
		{
			quotes++;
			if (status == 0)
				status = 1;
			else
				status = 0;
		}
		else if (prompt[i] == '\"' && status != 1)
		{
			dquotes++;
			if (status == 0)
				status = 2;
			else
				status = 0;
		}
		i++;
	}
	total = quotes + dquotes;
	return (total);
}

t_lex	*init_lexer(void)
{
	t_lex	*lexer;

	lexer = malloc(sizeof(t_lex));
	lexer->type = 0;
	lexer->data = NULL;
	lexer->redir = 0;
	lexer->quote = 0;
	lexer->quote_id = 0;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}