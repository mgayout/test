/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:15:45 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/18 17:58:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	tokenwoutsp_nb(char *str)
{
	int	i;
	int	nb_token;

	i = 0;
	nb_token = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (i > 0)
				if (!((str[i - 1] >= 9 && str[i - 1] <= 13) || str[i - 1] == ' '))
					nb_token += 1;
			if (!((str[i + 1] >= 9 && str[i + 1] <= 13) || str[i + 1] == ' '))
				nb_token += 1;
		}
		i++;
	}
	return (nb_token);
}