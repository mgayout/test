/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 18:32:53 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../lexer/lexer.h"

void	expander(t_data *data)
{
	t_exp	*tmp;
	t_par	*parser;

	data->expander = NULL;
	parser = data->parser;
	while (parser != NULL)
	{
		tmp = init_expander(parser);
		dollar_expander(data, tmp);
		expadd_back(&data->expander, tmp);
		parser = parser->next;
		free(tmp);
	}
}

t_exp	*init_expander(t_par *parser)
{
	t_exp	*expander;

	expander = malloc(sizeof(t_exp));
	expander->id = parser->id;
	expander->cmd = lstrjoin(parser->cmd);
	printf("cmd = %s\n", expander->cmd);
	expander->builtin = is_a_builtin(expander->cmd);
	expander->arg = lstrjoin(parser->arg);
	//expander->infile = infile_exp(parser->infile, parser->infile_count, parser->pipein);
	//expander->outfile = outfile_exp(parser->outfile, parser->outfile_count, parser->pipeout);
	expander->pipein = parser->pipein;
	expander->pipeout = parser->pipeout;
	//expander->heredoc = is_a_heredoc(parser->infile, parser->infile_count);
	expander->append = parser->append;
	expander->prev = NULL;
	expander->next = NULL;
	return (expander);
}

void	dollar_expander(t_data *data, t_exp *expander)
{
	if (ft_strchr(expander->cmd, '$'))
		expander->cmd = modify_expander(data, expander->cmd);
	if (expander->arg && ft_strchr(expander->arg, '$'))
		expander->arg = modify_expander(data, expander->arg);
	//if (expander->infile && ft_strchr(expander->infile, '$'))
		//expander->infile = modify_expander(data, expander->infile);
	//if (expander->outfile && ft_strchr(expander->outfile, '$'))
		//expander->outfile = modify_expander(data, expander->outfile);
}
