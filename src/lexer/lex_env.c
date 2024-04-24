/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:21 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/24 16:51:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	find_var(t_data *data, t_lex *lexer, char *prompt)
{
	t_env	*tmp;
	char	*var;
	char	*var_val;
	int		i;

	tmp = data->env;
	i = 0;
	while (!ft_strchr("\"'><| \t\n\r\v\f$", prompt[i]))
		i++;
	var = ft_calloc(sizeof(char), (i + 1));
	ft_strncpy(var, prompt, i);
	while (tmp != NULL)
	{
		if (!ft_strncmp(var, tmp->name, ft_strlen(var)))
		{
			var_val = join_var_val(tmp);
			if (!lexer->data)
				init_lex_data_env(lexer, var_val, ft_strlen(var_val));
			else
				join_lex_data_env(lexer, var_val, ft_strlen(var_val));
			break ;
		}
		tmp = tmp->next;
	}
	free(var);
}

char	*join_var_val(t_env *env)
{
	char	*tmp;
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (env->value[i] != NULL)
	{
		if (!value)
			value = ft_strdup(env->value[i]);
		else
		{
			tmp = ft_strjoin(":", env->value[i]);
			value = ft_strjoin(value, tmp);
			free(tmp);
		}
		i++;
	}
	return (value);
}

void	init_lex_data_env(t_lex *lexer, char *prompt, int i)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char), (i + 1));
	ft_strncpy(tmp, prompt, i);
	lexer->data = ft_strdup(tmp);
	printf("data = %s\n", lexer->data);
	free(tmp);
}

void	join_lex_data_env(t_lex *lexer, char *prompt, int i)
{
	char	*tmp;
	char	*stock;

	tmp = ft_calloc(sizeof(char), (i + 1));
	ft_strncpy(tmp, prompt, i);
	stock = ft_strjoin(lexer->data, tmp);
	if (ft_strlen(lexer->data) != 0 && lexer->type == STRING)
		free(lexer->data);
	lexer->data = ft_strdup(stock);
	printf("data = %s\n", lexer->data);
	free(stock);
	free(tmp);
}
