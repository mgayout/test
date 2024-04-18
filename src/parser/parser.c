/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/18 18:03:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void	parser(t_data *data, char *str)
{
	
}*/

char	*add_space(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		tok;

	i = 0;
	j = 0;
	tok = tokenwoutsp_nb(str);
	new = malloc(sizeof(char) * ft_strlen(str) + tok);
	printf("%d\n", tok);
	while (str[i] != '\0')
	{
		if (str[i + 1] == '>' || str[i + 1] == '<')
		{
			if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
				new[i + j] = str[i];
			else
			{
				new[i + j] = ' ';
				j++;
			}
		}
		else if (str[i - 1] == '>' || str[i - 1] == '<')
		{
			if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
				new[i + j] = str[i];
			else
			{
				new[i + j] = ' ';
				j++;
			}
		}
		else
			new[i + j] = str[i];
		i++;
		printf("%d\n", i);
	}
	new[i + j] = '\0';
	return (new);
}
