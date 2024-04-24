/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/24 15:45:10 by mgayout          ###   ########.fr       */
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
		i += add_new_t_lex(data, &data->lexer, &prompt[i]);
	}
}

int	add_new_t_lex(t_data *data, t_lex **lexer, char *prompt)
{
	t_lex	*new;
	int		i;

	i = 0;
	new = new_lex();
	if (prompt[0] == '>' || prompt[0] == '<' || prompt[0] == '|')
		i = token_type(new, prompt);
	else
		i = string_type(data, new, prompt);
	lexadd_back(lexer, new);
	return (i);
}
