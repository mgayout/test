/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:39:13 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 15:12:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	data_noquote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("no quote\n");
	//printf("prompt = %s\n", prompt);
	t_lstr	*data;
	char	*tmp;
	int		i;

	i = 0;
	while (prompt[i] && (!ft_strchr(limiter, prompt[i])))
		i++;
	//printf("i = %d\n", i);
	tmp = ft_calloc(sizeof(char), (i + 1));
	ft_strncpy(tmp, prompt, i);
	data = new_lstr(tmp, NO_QUOTE);
	lstradd_back(&lexer->data, data);
	//printf("tmp = %s\n", tmp);
	free(tmp);
	return (i);
}

int	data_quote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("quote\n");
	//printf("prompt = %s\n", prompt);
	t_lstr	*data;
	char	*tmp;
	int		i;

	i = 1;
	while (prompt[i] && !ft_strchr(limiter, prompt[i]))
		i++;
	//printf("i = %d\n", i);
	tmp = ft_substr(prompt, 1, i - 1);
	data = new_lstr(tmp, QUOTE);
	lstradd_back(&lexer->data, data);
	//printf("tmp = %s\n", tmp);
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
