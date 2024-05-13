/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:34:44 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/13 13:44:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*env_var(t_data *data, char *str)
{
	int	dollar;
	int	i;
	int	j;

	dollar = count_dollar(str);
	j = 0;
	while (j < dollar)
	{
		i = 0;
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
	while (env != NULL)
	{
		if (!ft_strncmp(env_name, env->name, ft_strlen(env_name)))
			return (replace_str(str, env->value, i, j));
		env = env->next;
	}
	return (NULL);
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
			new = ft_strjoin(ft_strjoin(new, ":"), value[k]);
		k++;
	}
	if (!begin && end)
		return (ft_strjoin(new, end));
	else if (begin && !end)
		return (ft_strjoin(begin, new));
	else
		return (ft_strjoin(ft_strjoin(begin, new), end));
	return (NULL);
}
