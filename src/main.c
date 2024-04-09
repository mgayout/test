/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/09 17:00:30 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*status_lst(t_mini *lst, int id)
{
	char	*str;
	
	
	return (str);
}

int	token_lst(char *str)
{
	if (!ft_strncmp(str, "<<", 3))
		return (1);
	else if (!ft_strncmp(str, "<", 2))
		return (2);
	else if (!ft_strncmp(str, ">", 2))
		return (3);
	else if (!ft_strncmp(str, ">>", 3))
		return (4);
	else if (!ft_strncmp(str, "|", 2))
		return (5);
	else
		return (0);
}

int	main(char **envp)
{
	t_mini	*lst;
	char	**arg;
	char	*prompt;

	lst = NULL;
	while (1)
	{
		prompt = readline("minishell :");
		add_history(prompt);
		arg = ft_split(prompt, ' ');
		create_lst(&lst, arg);
		print_lst(lst);
		//exec_arg(lst, envp);
		free_lst(&lst);
	}
}
