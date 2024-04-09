/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/09 16:57:21 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_arg(t_mini *lst, char **envp)
{
	//t_exec	strct;

	//strct.lst = *lst;
	//init_exec(&strct, envp);
	/*while (pipex.status < pipex.nb_cmd)
	{
		if (pipe(pipex.pipefd) == -1)
			free_parent(&pipex);
		pipex.pid[pipex.status] = fork();
		if (pipex.pid[pipex.status] == -1)
			free_parent(&pipex);
		open_pipe(&pipex, argc, argv, envp);
		pipex.status += 1;
	}
	free_parent(&pipex);*/
}