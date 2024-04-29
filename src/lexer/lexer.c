/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/29 17:52:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer(t_data *data)
{
	int		i;

	i = 0;
	data->lexer = NULL;
	while (data->prompt[i])
	{
		//printf("lexer : %s\n", data->prompt);
		while ((data->prompt[i] >= 9 && data->prompt[i] <= 13) || data->prompt[i] == ' ')
			i++;
		i += add_new_t_lex(data, &data->lexer, &data->prompt[i]);
	}
}

int	add_new_t_lex(t_data *data, t_lex **lexer, char *prompt)
{
	t_lex	*new;
	int		i;

	i = 0;
	new = new_lex();
	data->prompt = ft_strdup(prompt);
	//printf("lexer : %s\n", data->prompt);
	if (prompt[0] == '>' || prompt[0] == '<' || prompt[0] == '|')
		i = token_type(new, prompt);
	else
		i = string_type(data, new);
	lexadd_back(lexer, new);
	return (i);
}
