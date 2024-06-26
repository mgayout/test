/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:49:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 17:21:41 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *data)
{
	//free_env(&data->env);
	free(data->prompt);
	if (data->lexer)
		free_lex(&data->lexer);
	if (data->parser)
		free_par(&data->parser);
	if (data->exec)
		free_exe(&data->exec);
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
		free(tmp->cmd);
		free(tmp->arg);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		free(tmp);
	}
}

void	free_exe(t_exe **exec)
{
	t_exe	*tmp;

	tmp = *exec;
	//if (tmp->heredoc)
		//unlink(".temp");
	free(tmp->child);
	free(tmp->pid);
	free(tmp->pipefd);
	//free(tmp);
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