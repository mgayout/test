/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:15:45 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/16 11:59:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_string_par(t_par *parser, t_lex *lexer)
{
	if (lexer->prev->type == REDIR)
	{
		if (lexer->prev->redir == INFILE || lexer->prev->redir == HEREDOC)
		{
			if (parser->infile)
			{
				if (parser->heredoc)
					wrong_heredoc(parser->infile);
				else
					open(parser->infile, O_CREAT, 0777);
			}
			if (lexer->prev->redir == INFILE)
			{
				parser->infile = ft_strdup(lexer->data);
				parser->heredoc = false;
			}
			else
			{
				parser->infile = ft_strdup(lexer->data);
				parser->heredoc = true;
			}
		}
		else if (lexer->prev->redir == OUTFILE || lexer->prev->redir == APPEND)
		{
			if (parser->outfile)
				open(parser->outfile, O_CREAT, 0777);
			parser->outfile = ft_strdup(lexer->data);
			if (lexer->prev->redir == OUTFILE)
				parser->append = false;
			else if (lexer->prev->redir == APPEND)
				parser->append = true;
		}
	}
	else if (lexer->prev->type == STRING)
	{
		if (parser->status == 1)
		{
			if (!parser->arg)
				parser->arg = ft_strdup(lexer->data);
			else
				parser->arg = join_data_par(parser->arg, lexer->data);
		}
		else if (parser->status == 2)
			if (lexer->prev->prev->type == REDIR)
			{
				parser->cmd = ft_strdup(lexer->data);
				parser->status = 1;
			}
	}
	parser->data = join_data_par(parser->data, lexer->data);
}

void	add_redir_par(t_par *parser, t_lex *lexer)
{
	if (lexer->redir == INFILE)
		parser->data = join_data_par(parser->data, "<");
	else if (lexer->redir == OUTFILE)
		parser->data = join_data_par(parser->data, ">");
	else if (lexer->redir == HEREDOC)
		parser->data = join_data_par(parser->data, "<<");
	else if (lexer->redir == APPEND)
		parser->data = join_data_par(parser->data, ">>");
}

int	is_a_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (2);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (3);
	else if (!ft_strncmp(cmd, "export", 7))
		return (4);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (5);
	else if (!ft_strncmp(cmd, "env", 4))
		return (6);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (7);
	return (0);
}

char	*join_data_par(char *old, char *str)
{
	char	*new;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!old)
		size = ft_strlen(str);
	else if (!str)
		size = ft_strlen(old);
	else if (!str && !old)
		return (NULL);
	else
		size = ft_strlen(old) + ft_strlen(str);
	new = malloc(sizeof(char) * (size + 2));
	if (old)
		while (i < (int)ft_strlen(old))
		{
			new[i] = old[i];
			i++;
		}
	new[i] = ' ';
	i++;
	if (str)
		while (j < (int)ft_strlen(str))
		{
			new[i] = str[j];
			i++;
			j++;
		}
	new[i] = '\0';
	free(old);
	return (new);
}

void	wrong_heredoc(char *stop)
{
	char	*buf;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		buf = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(buf, stop, ft_strlen(buf) - 1)
			&& ft_strlen(buf) == ft_strlen(stop) + 1)
			break ;
		free(buf);
	}
	free(buf);
}

void	print_par(t_data *data)
{
	t_par	*tmp;

	tmp = data->parser;
	while (tmp != NULL)
	{
		printf("id = %d\n", tmp->id);
		printf("data = %s\n", tmp->data);
		printf("cmd = %s\n", tmp->cmd);
		printf("arg = %s\n", tmp->arg);
		printf("builtin = %d\n", tmp->builtin);
		if (tmp->infile)
		{
			if (!tmp->heredoc)
				printf("infile = %s\n", tmp->infile);
			else
				printf("heredoc limiter = %s\n", tmp->infile);	
		}
		if (tmp->pipein)
			printf("pipein true\n");
		if (tmp->outfile)
		{
			if (!tmp->append)
				printf("outfile = %s\n", tmp->outfile);
			else
				printf("outfile append = %s\n", tmp->outfile);
		}
		if (tmp->pipeout)
			printf("pipeout true\n");
		printf("\n");
		tmp = tmp->next;
	}
}
