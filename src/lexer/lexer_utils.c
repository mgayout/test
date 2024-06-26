/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 15:15:21 by mgayout          ###   ########.fr       */
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
			while (tmp->data)
			{
				if (tmp->data->quote == 2)
					printf("data quote = %s\n", tmp->data->str);
				else
					printf("data no quote = %s\n", tmp->data->str);
				tmp->data = tmp->data->next;	
			}
		tmp = tmp->next;
		i++;
	}
}
