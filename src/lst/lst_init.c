/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:27:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/12 11:26:35 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_lst(t_arg **lst, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		fill_list(lst, arg[i]);
		i++;
	}
	fill_status(*lst);
	fill_in_out(*lst);
}

void	fill_status(t_arg *lst)
{
	while (lst != NULL)
	{
		lst->status = status_lst(lst);
		lst = lst->next;
	}
}

void	fill_in_out(t_arg *lst)
{
	while (lst != NULL)
	{
		if (!ft_strncmp(lst->status, "cmd", 4))
		{
			before_cmd(lst);
			after_cmd(lst);
		}
		lst = lst->next;
	}
}
