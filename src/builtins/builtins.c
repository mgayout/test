/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:53:04 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/29 14:33:49 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exec_builtins(t_data *data)
{
	int	i;

	i = data->exec->status;
	if (data->exec->child[i].lst->builtin == 1)
		echo_builtin(data->exec->child[i].lst);
	else if (data->exec->child[i].lst->builtin == 2)
		cd_builtin();
	else if (data->exec->child[i].lst->builtin == 3)
		pwd_builtin();
	else if (data->exec->child[i].lst->builtin == 4)
		export_builtin();
	else if (data->exec->child[i].lst->builtin == 5)
		unset_builtin();
	else if (data->exec->child[i].lst->builtin == 6)
		env_builtin();
	else if (data->exec->child[i].lst->builtin == 7)
		exit_builtin();
}
