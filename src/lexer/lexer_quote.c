/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:39:13 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/30 16:16:39 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	data_quote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("quote\n");
	int	i;

	if (!lexer->data)
		i = init_quote(lexer, prompt + 1, limiter);
	else
		i = join_quote(lexer, prompt + 1, limiter);
	i++;
	return (i);
}

int	init_quote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("init\n");
	char	*tmp;
	int		i;

	i = 0;
	while (prompt[i] && !ft_strchr(limiter, prompt[i]))
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (prompt[i] && !ft_strchr(limiter, prompt[i]))
	{
		tmp[i] = prompt[i];
		i++;
	}
	tmp[i] = '\0';
	lexer->data = ft_strdup(tmp);
	free(tmp);
	return (i + 1);
}

int	join_quote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("join\n");
	char	*tmp;
	int		i;

	i = 0;
	while (prompt[i] && !ft_strchr(limiter, prompt[i]))
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (prompt[i] && !ft_strchr(limiter, prompt[i]))
	{
		tmp[i] = prompt[i];
		i++;
	}
	tmp[i] = '\0';
	lexer->data = ft_strjoin(lexer->data, tmp);
	free(tmp);
	return (i + 1);
}

char	*add_final_quote(char *prompt)
{
	char	*new_prompt;
	char	*buf;

	write(1, "> ", 2);
	buf = get_next_line(0);
	buf = ft_strtrim(buf, "\n");
	prompt = ft_strjoin(prompt, "\n");
	new_prompt = ft_strjoin(prompt, buf);
	free(buf);
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
	while (prompt[++j])
		new_prompt[j] = prompt[j];
	while(buf[++k])
	{
		if (k == i)
		{
			new_prompt[j + k] = '\n';
			j++;
		}
		new_prompt[j + k] = buf[k];
	}
	new_prompt[j + k] = '\0';
	return (new_prompt);
}
