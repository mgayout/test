/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/14 16:18:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander(t_data *data)
{
	t_par	*parser;

	data->expander = (t_exp *)ft_calloc(1, sizeof(t_exp));
	data->expander = NULL;
	parser = data->parser;
	while (parser != NULL)
	{
		if (ft_strchr(parser->data, '$'))
			dollar_parser(data, parser);
		if ((parser->outfile_count == 1 && parser->pipeout) || parser->outfile_count > 1)
			add_exps(&data->expander, parser);
		else
			add_exp(&data->expander, parser);
		parser = parser->next;
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
