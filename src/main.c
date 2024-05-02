/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/02 16:43:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "exec/exec.h"
#include "expander/expander.h"

void	minishell_loop(t_data *data)
{
	data->prompt = readline("minishell :");
	if (ft_strlen(data->prompt))
	{
		add_history(data->prompt);
		lexer(data);
		//print_lex(data);
		if (check_lexer(data->lexer))
		{
			parser(data);
			//print_par(data);
			if (check_parser(data->parser))
			{
				expander(data);
				exec(data);
			}
		}
		free_all(data);	
	}
	minishell_loop(data);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	if (argc != 1 || argv[1])
		return (0);
	data.envp = envp;
	env(&data);
	//print_env(data.env);
	if (!data.envp[0])
		return (0);
	minishell_loop(&data);
}
