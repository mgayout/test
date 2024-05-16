/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/16 12:38:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander(t_data *data)
{
	t_par	*parser;

	parser = data->parser;
	while (parser != NULL)
	{
		if (ft_strchr(parser->data, '$'))
			dollar_parser(data, parser);
		parser = parser->next;
	}
}

void	dollar_parser(t_data *data, t_par *parser)
{
	if (ft_strchr(parser->cmd, '$'))
		parser->cmd = env_var(data, parser->cmd);
	if (parser->arg && ft_strchr(parser->arg, '$'))
		parser->arg = env_var(data, parser->arg);
	if (parser->infile && ft_strchr(parser->infile, '$'))
		parser->infile = env_var(data, parser->infile);
	if (parser->outfile && ft_strchr(parser->outfile, '$'))
		parser->outfile = env_var(data, parser->outfile);
}
