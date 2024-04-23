/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/23 17:38:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_lex(t_data *data)
{
	t_lex	*tmp;
	int		i;
	int		j;

	tmp = data->lexer;
	i = 1;
	while (tmp != NULL)
	{
		printf("lst n* %d\n", i);
		printf("type = %d\n", tmp->type);
		if (tmp->type == 1)
			printf("redir = %d\n", tmp->redir);
		else if (tmp->type == 2)
		{
			j = 0;
			printf("data = %s\n", tmp->data);
			while (j < tmp->quote_id)
			{
				printf("quote n* %d = %d\n", j + 1, tmp->quote[j]);	
				j++;
			}
		}
		tmp = tmp->next;
		i++;
	}
}