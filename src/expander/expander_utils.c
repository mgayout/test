/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:29:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/16 12:41:31 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*search_begin(char *str, int i)
{
	char	*begin;
	int		j;

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

char	**copy_tab(char **old)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!old)
		return (NULL);
	while (old[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		new[j] = ft_strdup(old[j]);
		j++;
	}
	new[j] = NULL;
	return (new);
}
