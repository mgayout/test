/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/02 16:41:49 by mgayout          ###   ########.fr       */
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
	if (ft_strchr(parser->arg, '$'))
		parser->arg = env_var(data, parser->arg);
	if (ft_strchr(parser->infile, '$'))
		parser->infile = env_var(data, parser->infile);
	if (ft_strchr(parser->outfile, '$'))
		parser->outfile = env_var(data, parser->outfile);
	if (ft_strchr(parser->heredoc, '$'))
		parser->heredoc = env_var(data, parser->heredoc);
}

char	*env_var(t_data *data, char *str)
{
	int	dollar;
	int	i;
	int	j;

	dollar = count_dollar(str);
	j = 0;
	//printf("%d dollar\n", dollar);
	while (j < dollar)
	{
		i = 0;
		//printf("str = %s\n", str);
		while(str[i] != '$')
			i++;
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
	int		k;
	
	env = data->env;
	j = i;
	while(!ft_strchr("$<>| \"'", str[j]))
		j++;
	env_name = malloc(sizeof(char) * (j - i) + 1);
	k = i;
	while(k != j)
	{
		env_name[k - i] = str[k];
		k++;
	}
	env_name[k - i] = '\0';
	new_str = NULL;
	//printf("%s%d\n", env_name, (int)ft_strlen(env_name));
	while (env != NULL)
	{
		if (!ft_strncmp(env_name, env->name, ft_strlen(env_name)))
			new_str = replace_str(str, env->value, i, j);
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
	begin = search_begin(str, i - 1);
	new = NULL;
	end = search_end(str, j);
	while (value[k] != NULL)
	{
		if (!new)
			new = ft_strdup(value[k]);
		else
		{
			new = ft_strjoin(new, ":");
			new = ft_strjoin(new, value[k]);
		}
		k++;
	}
	if (!begin && end)
		new = ft_strjoin(new, end);
	else if (begin && !end)
		new = ft_strjoin(begin, end);
	else if (begin && end)
		new = ft_strjoin(ft_strjoin(begin, new), end);
	return (new);
}

char	*search_begin(char *str, int i)
{
	char	*begin;
	int		j;

	//printf("i = %d\n", i);
	if (i == 0)
		return (NULL);
	begin = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (i != j)
	{
		begin[j] = str[j];
		j++;
	}
	begin[j] = '\0';
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
