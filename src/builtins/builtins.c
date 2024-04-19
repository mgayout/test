/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:53:04 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/19 12:01:42 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exec_builtins(t_data *data)
{
	int	i;

	i = data->exec->status;
	if (data->exec->child[i].lst->builtins == 1)
		echo_builtin(data);
	else if (data->exec->child[i].lst->builtins == 2)
		cd_builtin();
	else if (data->exec->child[i].lst->builtins == 3)
		pwd_builtin();
	else if (data->exec->child[i].lst->builtins == 4)
		export_builtin();
	else if (data->exec->child[i].lst->builtins == 5)
		unset_builtin();
	else if (data->exec->child[i].lst->builtins == 6)
		env_builtin();
	else if (data->exec->child[i].lst->builtins == 7)
		exit_builtin();
}
