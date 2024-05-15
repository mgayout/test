/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:59 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/15 09:00:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd_builtin(t_data *data, t_pid child)
{
	if (!data->prompt)
		return(1);
	if (!child.lst)
		return (1);
	return (1);
}
