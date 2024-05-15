/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:41 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 09:00:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exit_builtin(t_data *data, t_pid child)
{
	if (!data->prompt)
		return(1);
	if (!child.lst)
		return (1);
	return (1);
}
