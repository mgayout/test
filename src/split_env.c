/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:41 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/17 16:08:25 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_env(t_data *data)
{
	t_env	*env;
	int	i;

	i = 0;
	while(data->envp[i] != NULL)
	{
		fill_env(&env, data->envp[i]);
		i++;
	}
	data->env = env;
}

void	fill_env(t_env **env, char *envp)
{
	t_env	*new;
	t_env	*tmp;
	int		i;

	i = 0;
	while (ft_strncmp(&envp[i], "=", 1) != 0)
		i++;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = malloc(sizeof(char *) * i + 1);
	ft_strlcpy(new->name, envp, i + 1);
	new->value = ft_split(&envp[i + 1], ':');
	if (!(*env))
		*env = new;
	else
	{
		tmp = envlast(*env);
		new->prev = tmp;
		tmp->next = new;
	}
}

void	print_env(t_env *env)
{
	int	i;

	while (env != NULL)
	{
		i = 0;
		printf("Name = %s\n", env->name);
		while (env->value[i] != NULL)
		{
			printf("Value = %s\n", env->value[i]);
			i++;
		}
		env = env->next;
	}
}

t_env	*envlast(t_env *lst)
{
	t_env	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = envsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

int	envsize(t_env *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}