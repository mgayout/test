/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:49:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/25 16:59:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *data)
{
	//free_env(&data->env);
	free_lex(&data->lexer);
	free_par(&data->parser);
}

void	free_env(t_env **env)
{
	t_env	*tmp;
	
	while (*env != NULL)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->name);
		free_tab(tmp->value);
		free(tmp);
	}
}

void	free_lex(t_lex **lexer)
{
	t_lex	*tmp;
	
	while (*lexer != NULL)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp->data);
		free(tmp);
	}
}

void	free_par(t_par **parser)
{
	t_par	*tmp;

	while (*parser != NULL)
	{
		tmp = *parser;
		*parser = (*parser)->next;
		free(tmp->data);
		free(tmp->cmd);
		free(tmp->arg);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->infile)
			free(tmp->outfile);
		if (tmp->heredoc)
			free(tmp->heredoc);
		free(tmp);
	}
}

void	free_tab(char **tabs)
{
	int	i;
	
	i = 0;
	while (tabs[i] != NULL)
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}