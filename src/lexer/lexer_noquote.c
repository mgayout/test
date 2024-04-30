/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_noquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:59:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/30 15:59:52 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	data_noquote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("noquote\n");
	int	i;

	i = 0;
	if (!lexer->data)
		i = init_noquote(lexer, prompt, limiter);
	else
		i = join_noquote(lexer, prompt, limiter);	
	return (i);
}

int	init_noquote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("init\n");
	char	*tmp;
	int		i;

	i = 0;
	while (prompt[i] && (!ft_strchr(limiter, prompt[i])))
		i++;	
	tmp = ft_calloc(sizeof(char), (i + 1));
	ft_strncpy(tmp, prompt, i);
	lexer->data = ft_strdup(tmp);
	free(tmp);
	return (i);
}

int	join_noquote(t_lex *lexer, char *prompt, char *limiter)
{
	//printf("join\n");
	char	*tmp;
	int		i;

	i = 0;
	while (prompt[i] && (!ft_strchr(limiter, prompt[i])))
		i++;	
	tmp = ft_calloc(sizeof(char), (i + 1));
	ft_strncpy(tmp, prompt, i);
	lexer->data = ft_strjoin(lexer->data, tmp);
	free(tmp);
	return (i);
}
