/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/24 17:17:22 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_dollar(char *prompt, int i)
{
	int	j;

	j = 0;
	while (j != i)
	{
		if (prompt[j] == '$')
			return (1);
		j++;
	}
	return (0);
}

void	print_lex(t_data *data)
{
	t_lex	*tmp;
	int		i;

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
			printf("data = %s\n", tmp->data);
			printf("quote = %d\n", tmp->quote);	
		}
		tmp = tmp->next;
		i++;
	}
}