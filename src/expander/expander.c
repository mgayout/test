/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/13 14:07:21 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander(t_data *data)
{
	t_par	*tmp;

	tmp = data->parser;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->data, '$'))
			dollar_parser(data, tmp);
		tmp = tmp->next;
	}
	tmp = data->parser;
	while(tmp != NULL)
	{
		if (tmp->pipeout && tmp->outfile_count >= 1)
			tmp = multi_cmd_pipe(data, tmp);
		else if (tmp->outfile_count > 1)
			tmp = multi_cmd_nopipe(data, tmp);
		tmp = tmp->next;
	}
}

void	dollar_parser(t_data *data, t_par *parser)
{
	int	i;

	if (ft_strchr(parser->cmd, '$'))
		parser->cmd = env_var(data, parser->cmd);
	if (ft_strchr(parser->arg, '$'))
		parser->arg = env_var(data, parser->arg);
	i = 0;
	if (parser->infile)
		while (parser->infile[i] != NULL)
		{
			if (ft_strchr(parser->infile[i], '$'))
				parser->infile[i] = env_var(data, parser->infile[i]);
			i++;
		}
	i = 0;
	if (parser->outfile)
		while (parser->outfile[i] != NULL)
		{
			if (ft_strchr(parser->outfile[i], '$'))
				parser->outfile[i] = env_var(data, parser->outfile[i]);
			i++;
		}
}

t_par	*multi_cmd_nopipe(t_data *data, t_par *parser)
{
	t_par	*new;
	t_par	*prev;
	int	outfile;

	outfile = 0;
	new = parser;
	parser->prev->next = new;
	while (outfile != parser->outfile_count)
	{
		outfile++;
	}
	new->next
	return(new);
}

t_par	*multi_cmd_pipe(t_data *data, t_par *parser)
{
	
}
