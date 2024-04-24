/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:39:13 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/24 17:22:36 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	data_no_quote(t_data *data, t_lex *lexer, char *prompt)
{
	int		i;

	i = 0;
	if (prompt[0] == '$')
		i = 1;
	while (prompt[i] && (!ft_strchr("$\"'><| \t\n\r\v\f", prompt[i])))
		i++;
	if (prompt[0] == '$')
	{
		find_var(data, lexer, &prompt[1]);
		return(i);
	}
	if (!lexer->data)
		init_lex_data(lexer, prompt, i);
	else
		join_lex_data(lexer, prompt, i);
	return (i);
}


int	data_quotes(t_data *data, t_lex *lexer, char *prompt, char *limiter)
{
	int		i;

	i = 0;
	printf("start find prompt[i] = %c\n", prompt[i]);
	while (prompt[i] && (!ft_strchr(limiter, prompt[i])))
		i++;
	if ((prompt[i] == '\'' || prompt[i] == '"'))
		i++;
	if (check_dollar(prompt, i))
		env_lex_data(lexer, prompt, i);
	else
	{
		if (!lexer->data)
			init_lex_data(lexer, prompt, i);
		else
			join_lex_data(lexer, prompt, i);	
	}
	return (i + 1);
}

void	env_lex_data(t_lex *lexer, char prompt, int j)
{
	char	*start;
	int		i;

	i = 0;
	while (prompt[i] != '$')
		i++;
	start = ft_calloc(sizeof(char), (i + 1));
	ft_strncpy(start, prompt, i);
	
}

void	init_lex_data(t_lex *lexer, char *prompt, int i)
{
	char	*tmp;

	if (lexer->quote == NO_QUOTE)
	{
		tmp = ft_calloc(sizeof(char), (i + 1));
		ft_strncpy(tmp, prompt, i);
	}
	else
	{
		tmp = ft_calloc(sizeof(char), (i + 1));
		ft_strncpy(tmp, prompt, i - 1);
	}
	lexer->data = ft_strdup(tmp);
	printf("data = %s\n", lexer->data);
	free(tmp);
}

void	join_lex_data(t_lex *lexer, char *prompt, int i)
{
	char	*tmp;
	char	*stock;

	if (lexer->quote == NO_QUOTE)
	{
		tmp = ft_calloc(sizeof(char), (i + 1));
		ft_strncpy(tmp, prompt, i);
	}
	else
	{
		tmp = ft_calloc(sizeof(char), (i + 1));
		ft_strncpy(tmp, prompt, i - 2);
	}
	stock = ft_strjoin(lexer->data, tmp);
	if (ft_strlen(lexer->data) != 0 && lexer->type == STRING)
		free(lexer->data);
	lexer->data = ft_strdup(stock);
	printf("data = %s\n", lexer->data);
	free(stock);
	free(tmp);
}
