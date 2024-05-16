/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:26:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/16 11:40:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_par	*new_par()
{
	t_par	*new;

	new = (t_par *)ft_calloc(1, sizeof(t_par));
	if (!new)
		return (NULL);
	new->id = 0;
	new->status = 0;
	new->data = NULL;
	new->cmd = NULL;
	new->builtin = 0;
	new->arg = NULL;
	new->infile = NULL;
	new->heredoc = false;
	new->outfile = NULL;
	new->append = false;
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	parsize(t_par *parser)
{
	int	size;

	size = 0;
	while (parser != NULL)
	{
		++size;
		parser = parser->next;
	}
	return (size);
}