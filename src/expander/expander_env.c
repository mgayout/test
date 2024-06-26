/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:34:44 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 18:30:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*modify_expander(t_data *data, char *str)
{
	int	dollar;
	int	i;
	int	j;

	dollar = count_dollar(str);
	j = 0;
	while (j < dollar)
	{
		i = 0;
		while (str[i] != '$')
			i++;
		if (str[i + 1] == '?')
			str = modify_str(ft_itoa(data->error), str, i);	
		else if (str[i + 1] != ' ' && str[i + 1] != '\n' && str[i + 1] != '\0')
			str = modify_str(search_var(data, str, i + 1), str, i);
		j++;
	}
	return(str);
}

char	*modify_str(char *new, char *str, int i)
{
	char	*begin;
	char	*end;
	int		j;
	
	begin = ft_substr(str, 0, i);
	j = i + 1;
	printf("str[i] = %c\n", str[i]);
	printf("str[j] = %c | j = %d\n", str[j], j);
	while (str[j] != ' ' && str[j] != '\0' && str[j] != '\n' && str[j] != '$')
		j++;
	printf("str[j] = %c | j = %d\n", str[j], j);
	end = ft_substr(str, j, (ft_strlen(str) - j) + 1);
	if (begin)
		printf("begin = %s\n", begin);
	if (new)
		printf("new = %s\n", new);
	if (end)
		printf("end = %s\n", end);
	if (!begin && !new)
		return (end);
	else if (!begin && !end)
		return (new);
	else if (!new && !end)
		return (begin);
	else if (!begin)
		return (ft_strjoin(new, end));
	else if (!new)
		return (ft_strjoin(begin, end));
	else if (!end)
		return (ft_strjoin(begin, new));
	else if (!begin && !end)
		return (new);
	return (ft_strjoin(ft_strjoin(begin, new), end));
}

char	*search_var(t_data *data, char *str, int i)
{
	t_env	*env;
	char	*new;
	char	*var;
	int		j;
	int		k;
	
	j = i;
	while (!ft_strchr("$<>|\0\n \"'", str[j]))
		j++;
	var = ft_substr(str, i, j - i);
	env = data->env;
	while (env && ft_strncmp(var, env->name, ft_strlen(env->name)) != 0)
		env = env->next;
	k = 0;
	new = NULL;
	while (env && env->value[k])
	{
		if (!new)
			new = ft_strdup(env->value[k]);
		else
			new = ft_strjoin(ft_strjoin(new, ":"), env->value[k]);
		k++;
	}
	return (new);
}
