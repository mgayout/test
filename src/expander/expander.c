/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/30 17:58:53 by mgayout          ###   ########.fr       */
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
			modify_parser(data, tmp);
		tmp = tmp->next;
	}
}

void	modify_parser(t_data *data, t_par *parser)
{
	if (ft_strchr(parser->cmd, '$'))
		parser->cmd = env_var(data, parser->cmd);
	else if (ft_strchr(parser->arg, '$'))
		parser->arg = env_var(data, parser->arg);
	else if (ft_strchr(parser->infile, '$'))
		parser->infile = env_var(data, parser->infile);
	else if (ft_strchr(parser->outfile, '$'))
		parser->outfile = env_var(data, parser->outfile);
	else if (ft_strchr(parser->heredoc, '$'))
		parser->heredoc = env_var(data, parser->heredoc);
}

char	*env_var(t_data *data, char *str)
{
	int	dollar;
	int	i;
	int	j;

	dollar = count_dollar(str);
	j = 0;
	printf("%d dollar\n", dollar);
	while (j < dollar)
	{
		i = 0;
		while(str[i] != '$')
			i++;
		str = search_env_var(data, str, i);
		j++;
	}
	return(str);
}

char	*search_env_var(t_data *data, char *str, int i)
{
	t_env	*env;
	char	*env_name;
	char	*new_str;
	int		j;
	
	env = data->env;
	j = i + 1;
	while(!ft_strchr("$<>| \"'", str[j]))
		j++;
	env_name = malloc(sizeof(char) * j);
	env_name = ft_strncpy(env_name, str + (i + 1), j);
	new_str = NULL;
	printf("%s\n", env_name);
	while (env != NULL)
	{
		if (!ft_strncmp(env_name, env->name, ft_strlen(env_name)))
			new_str = replace_str(str, env->value, i - 1, j);
		env = env->next;
	}
	return (new_str);
}

char	*replace_str(char	*str, char	**value, int i, int j)
{
	char	*begin;
	char	*new;
	char	*end;
	int		k;

	k = 0;
	while (value[k] != NULL)
	{
		if (!new)
			new = ft_strdup(value[k]);
		else
		{
			new = ft_strjoin(new, ":");
			new = ft_strjoin(new, value[k]);
		}
		i++;
	}
	begin = ft_strjoin(search_begin(str, i), " ");
	new = ft_strjoin(new, " ");
	end = search_end(str, j);
	new = ft_strjoin(ft_strjoin(begin, new), end);
	return (new);
}

char	*search_begin(char *str, int i)
{
	char	*begin;

	begin = malloc(sizeof(char) * (i + 1));
	begin = ft_strncpy(begin, str, i + 1);
	return (begin);
}

char	*search_end(char *str, int i)
{
	char	*end;
	int		j;

	j = i;
	while (str[j])
		j++;
	end = malloc(sizeof(char) * ((j - i) + 1));
	end = ft_strncpy(end, str + i, (j - i) + 1);
	return (end);
}

int	count_dollar(char *str)
{
	int	dollar;
	int	status;
	int	i;

	dollar = 0;
	status = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (status == 0)
			{
				dollar++;
				if (str[i + 1] == '$')
					status++;
			}
			else if (status == 1)
				status = 0;
		}
		i++;
	}
	return (dollar);
}
