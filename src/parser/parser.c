/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/24 11:39:10 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_data *data)
{
	t_lex	*tmp;

	tmp = data->lexer;
	data->parser = malloc(sizeof(t_par));
	while (tmp->next != NULL)
	{
		addlex_topar(data, tmp);
		tmp = tmp->next;
	}
}

void	addlex_topar(t_data *data, t_lex *lexer)
{
	
}