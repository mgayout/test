/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:33:21 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/17 18:00:59 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_var(t_data *data, char **arg)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	k = 0;
	while (arg[k] != NULL)
	{
		j = 0;
		while (arg[k][j] != '\0')
		{
			if (!ft_strncmp(&arg[k][j], "$", 1))
			{
				i = j + 1;
				while (arg[k][i] != ' ' && arg[k][i] != '\0' && arg[k][i] != '$')
					i++;
				if (arg[k][i] == '$')
					i--;
				str = malloc(sizeof(char) * (i - j) + 1);
				ft_strlcpy(str, &arg[k][j + 1], (i - j) + 1);
				if (is_an_env_var(data->env, str))
				{
					if (ft_strncmp(arg[k], strenv_var(data->env, str), ft_strlen(arg[k])))
					{
						free(arg[k]);
						arg[k] = strenv_var(data->env, str);
					}
					else
						ft_strjoin(arg[k], strenv_var(data->env, str));
				}
				printf("$ = %s\n", str);
				printf("Value = %s\n", arg[k]);
				free(str);
			}
			j++;
		}
		k++;
	}
}

int	is_an_env_var(t_env *env, char *str)
{
	while (env != NULL)
	{
		//printf("%s\n", env->name);
		if (!ft_strncmp(env->name, str, ft_strlen(str)))
			return (1);
		env = env->next;
	}
	return (0);
}

char	*strenv_var(t_env *env, char *str)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, str, ft_strlen(str)))
			return (strjoin_tab(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*strjoin_tab(char **value)
{
	char	*tmp;
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (value[i] != NULL)
		i++;
	if (i == 1)
		return (value[0]);
	tmp = ft_strjoin(value[0], ":");
	tmp = ft_strjoin(tmp, value[1]);
	while (j != i)
	{
		tmp = ft_strjoin(tmp, ":");
		tmp = ft_strjoin(tmp, value[j]);
		j++;
	}
	return (tmp);
}