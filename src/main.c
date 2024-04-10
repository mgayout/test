/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/10 16:37:18 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*status_lst(t_mini *lst)
{
	if (lst->token > 0)
		return (ft_strdup("token"));
	if (is_a_cmd(lst->data))
		return (ft_strdup("cmd"));
	else if (!ft_strncmp(lst->data, "-", 1))
		return (ft_strdup("flag"));
	else
		return (ft_strdup("file")); //arg
}

int	is_a_cmd(char *str)
{
	char	**path;
	char	*tmp;
	char	*path_cmd;
	int		i;

	path = ft_split(getenv("PATH"), ':');	
	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(path_cmd, 0) == 0)
		{
			printf("%s\n", path_cmd);
			return (1);
		}
		free(path_cmd);
		i++;
	}
	/*if (access(str, 0) == 0)
	{
		printf("%s\n", str);
		return (1);
	}*/
	return (0);
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

int	main(int argc, char **argv, char *envp[])
{
	t_mini	*lst;
	char	**arg;
	char	*prompt;

	if (argc != 1 || argv[1])
		return (0);
	lst = NULL;
	while (1)
	{
		prompt = readline("minishell :");
		add_history(prompt);
		arg = ft_split(prompt, ' ');
		create_lst(&lst, arg);
		print_lst(lst);
		exec_arg(lst, envp);
		free_lst(&lst);
	}
}
