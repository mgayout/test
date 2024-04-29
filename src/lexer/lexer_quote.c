/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:39:13 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/29 17:55:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	count_quotes(char *prompt)
{
	int	i;
	int status;

	i = 0;
	status = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && status != 2)
		{
			if (status == 0)
				status = 1;
			else
				status = 0;
		}
		else if (prompt[i] == '\"' && status != 1)
		{
			if (status == 0)
				status = 2;
			else
				status = 0;
		}
		i++;
	}
	return (status);
}

int	data_no_quote(t_lex *lexer, char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i] && (!ft_strchr("\"'><| \t\n\r\v\f", prompt[i])))
		i++;
	if (!lexer->data)
		init_lex_data(lexer, prompt, i, NO_QUOTE);
	else
		join_lex_data(lexer, prompt, i, NO_QUOTE);	
	return (i);
}

int	data_quotes(t_lex *lexer, char *prompt, char *limiter)
{
	int		i;

	i = 0;
	while (prompt[i] && (!ft_strchr(limiter, prompt[i])))
		i++;
	if ((prompt[i] == '\'' || prompt[i] == '"'))
		i++;
	if (!lexer->data)
		init_lex_data(lexer, prompt, i, QUOTE);
	else
		join_lex_data(lexer, prompt, i, QUOTE);	
	return (i + 1);
}

void	init_lex_data(t_lex *lexer, char *prompt, int i, t_lex_quote n)
{
	char	*tmp;

	if (n == NO_QUOTE)
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
	free(tmp);
}

void	join_lex_data(t_lex *lexer, char *prompt, int i, t_lex_quote n)
{
	char	*tmp;
	char	*stock;

	if (n == NO_QUOTE)
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
	free(stock);
	free(tmp);
}

char	*add_final_quote(char *prompt)
{
	char	*new_prompt;
	char	*buf;
	char	last_quote;
	int		i;

	i = 0;
	write(1, "> ", 2);
	buf = get_next_line(0);
	last_quote = '\'';
	if (count_quotes(prompt) == 2)
		last_quote = '"';
	while (prompt[i] && prompt[i] != last_quote)
		i++;
	//printf("i = %d\n", i);
	if (prompt[i] == last_quote)
		new_prompt = join_final_quote(prompt, buf, i);
	else
		new_prompt = ft_strjoin(prompt, buf);
	free(buf);
	//printf("%s\n", new_prompt);
	return (new_prompt);
}
char	*join_final_quote(char *prompt, char *buf, int i)
{
	char	*new_prompt;
	int		size;
	int		j;
	int		k;

	j = 0;
	k = 0;
	size = ft_strlen(prompt) + ft_strlen(buf);
	new_prompt = malloc(sizeof(char) * size + 2);
	while (prompt[j])
	{
		new_prompt[j] = prompt[j];
		j++;
	}
	while(buf[k])
	{
		if (k == i)
		{
			new_prompt[j + k] = '\n';
			j++;
		}
		new_prompt[j + k] = buf[k];
		k++;
	}
	new_prompt[j + k] = '\0';
	printf("prompt = %s", new_prompt);
	return (new_prompt);
}
