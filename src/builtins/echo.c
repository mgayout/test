/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 14:10:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo_builtin(t_data *data, t_pid child)
{
	if (!data->prompt)
		return ;
	printf("%s\n", child.lst->arg);
}
