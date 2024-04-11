/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/11 17:44:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_cmd(t_arg *lst)
{
	t_arg	*tmp;
	
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token > 0)
		{
			if (!ft_strncmp(tmp->data, "<", 2))
				lst->infile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">", 2))
				lst->outfile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, "|", 2))
				lst->pipein = true;
			/*printf("BACK\ninfile = %s && outfile = %s\n", lst->infile, lst->outfile);
			if (lst->pipein == true)
				printf("true\n");
			else
				printf("false\n");*/
			return ;
		}
		tmp = tmp->prev;
	}
}

void	end_cmd(t_arg *lst)
{
	t_arg	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token > 0)
		{
			if (!ft_strncmp(tmp->data, "<", 2))
				lst->infile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, ">", 2))
				lst->outfile = ft_strdup(tmp->next->data);
			else if (!ft_strncmp(tmp->data, "|", 2))
				lst->pipeout = true;
			/*printf("FRONT\ninfile = %s && outfile = %s\n", lst->infile, lst->outfile);
			if (lst->pipein == true)
				printf("true\n");
			else
				printf("false\n");*/
			return ;
		}
		tmp = tmp->next;
	}
}

char	*status_lst(t_arg *lst)
{
	//printf("data prev = %s && new = %s\n", lst->prev->data, lst->data);
	if (lst->token > 0)
		return (ft_strdup("token"));
	if (is_a_cmd(lst->data))
		return (ft_strdup("cmd"));
	else if (!ft_strncmp(lst->data, "-", 1))
		return (ft_strdup("flag"));
	else if (is_an_arg(&lst))
		return (ft_strdup("arg"));
	else if (is_a_file(&lst))
		return (ft_strdup("file"));
	else
		return (ft_strdup("IDK"));
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
			return (1);
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

int	is_an_arg(t_arg **lst)
{
	t_arg	*tmp;

	tmp = *lst;
	if (tmp->prev == NULL)
		return (0);
	else if (!ft_strncmp(tmp->prev->status, "cmd", 3))
		return (1);
	return (0);
}

int	is_a_file(t_arg **lst)
{
	t_arg	*tmp;
	
	tmp = *lst;
	if (tmp->prev == NULL)
		return (0);
	else if (tmp->prev->token > 0 && tmp->prev->token < 5)
		return (1);
	else
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
