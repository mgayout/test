/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/15 18:17:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_loop(t_data *data)
{
	t_arg	*lst;
	char	**arg;
	char	*prompt;

	lst = NULL;
	data->lst = lst;
	prompt = readline("minishell :");
	add_history(prompt);
	arg = ft_split(prompt, ' ');
	create_lst(&data->lst, arg);
	free(arg);
	//print_lst(data->lst);
	exec_arg(data);
	free_lst(&data->lst);
	minishell_loop(data);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	if (argc != 1 || argv[1])
		return (0);
	data.envp = envp;
	if (!data.envp[0])
		return(0);
	minishell_loop(&data);
}
