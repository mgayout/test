/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:49:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/03 14:37:38 by mgayout          ###   ########.fr       */
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
	//if (data->exec)
		//free_exe(&data->exec);
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
			free_tab(tmp->infile);
		if (tmp->outfile)
			free_tab(tmp->outfile);
		if (tmp->heredoc)
			free_tab(tmp->heredoc);
		if (tmp->append)
			free_tab(tmp->append);
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