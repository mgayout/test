/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:38:05 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/14 16:18:24 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	add_exp(t_exp **expander, t_par *parser)
{
	t_exp	*new;
	
	new = malloc(sizeof(t_exp) * 1);
	new->id = parser->id;
	new->data = ft_strdup(parser->data);
	new->cmd = ft_strdup(parser->cmd);
	new->arg = NULL;
	if (parser->arg)
		new->arg = ft_strdup(parser->arg);
	new->builtin = parser->builtin;
	new->infile = copy_tab(parser->infile);
	new->heredoc = copy_tab(parser->heredoc);
	new->infile_count = parser->infile_count;
	new->outfile = copy_tab(parser->outfile);
	new->append = copy_tab(parser->append);
	new->outfile_count = parser->outfile_count;
	new->pipein = parser->pipein;
	new->pipeout = parser->pipeout;
	new->next = NULL;
	new->prev = NULL;
	add_back_exp(expander, new);
}

void	add_exps(t_exp **expander, t_par *parser)
{
	int	i;

	i = 0;
	while (i != parser->outfile_count)
	{
		add_exp_outfile(expander, parser, i);
		i++;
	}
	if (parser->pipeout)
		add_exp_pipeout(expander, parser);
}

void	add_exp_outfile(t_exp **expander, t_par *parser, int i)
{
	t_exp	*new;
	
	new = malloc(sizeof(t_exp) * 1);
	new->id = parser->id;
	new->data = ft_strdup(parser->data);
	new->cmd = ft_strdup(parser->cmd);
	new->arg = NULL;
	if (parser->arg)
		new->arg = ft_strdup(parser->arg);
	new->builtin = parser->builtin;
	new->infile = copy_tab(parser->infile);
	new->heredoc = copy_tab(parser->heredoc);
	new->infile_count = parser->infile_count;
	new->outfile = malloc(sizeof(char *) * 2);
	new->outfile[0] = ft_strdup(parser->outfile[i]);
	new->outfile[1] = NULL;
	new->append = malloc(sizeof(char *) * 2);
	new->append[0] = ft_strdup(parser->append[i]);
	new->append[1] = NULL;
	new->outfile_count = 1;
	new->pipein = parser->pipein;
	new->pipeout = false;
	new->next = NULL;
	new->prev = NULL;
	add_back_exp(expander, new);
}

void	add_exp_pipeout(t_exp **expander, t_par *parser)
{
	t_exp	*new;
	
	new = malloc(sizeof(t_exp) * 1);
	new->id = parser->id;
	new->data = ft_strdup(parser->data);
	new->cmd = ft_strdup(parser->cmd);
	new->arg = NULL;
	if (parser->arg)
		new->arg = ft_strdup(parser->arg);
	new->builtin = parser->builtin;
	new->infile = copy_tab(parser->infile);
	new->heredoc = copy_tab(parser->heredoc);
	new->infile_count = parser->infile_count;
	new->outfile = NULL;
	new->append = NULL;
	new->outfile_count = 0;
	new->pipein = parser->pipein;
	new->pipeout = true;
	new->next = NULL;
	new->prev = NULL;
	add_back_exp(expander, new);
}
