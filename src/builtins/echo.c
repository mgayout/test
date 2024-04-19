/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/19 12:01:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo_builtin(t_data *data)
{
	//char	c;
	int		i;

	//c = '%';
	i = data->exec->status;
	if (!data->exec->child[i].lst->flag)
		printf("%s\n", data->exec->child[i].lst->arg);
	//else
		//if (!ft_strncmp(data->exec->child[i].lst->flag, "-n", 3))
			//printf("%s%c\n", data->exec->child[i].lst->arg, c);
}
