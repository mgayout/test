/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:16:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/09 16:57:10 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft-/libft.h"
# include "libft-/ft_printf+/ft_printf.h"
# include "libft-/get_next_line+/get_next_line.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

typedef struct s_mini
{
	int				id;
	char			*status;
	int				token;
	int				builtins;
	char			*data;
	struct s_mini	*next;
	struct s_mini	*prev;
}					t_mini;

typedef struct s_exec
{
	int				pipefd[2];
	int				*pid;
	int				heredoc;
	int				status;
	int				nb_cmd;
	int				infile;
	int				outfile;
	char			*path;
	char			**path_cmd;
	char			**cmd;
	char			*cmd_path;
	struct s_mini	lst;
}					t_exec;

//MAIN



//LST_ARG

void	fill_list(t_mini **lst, char *str);
void	print_lst(t_mini *lst);
void	free_lst(t_mini **s);
int		token_lst(char *str);

//LST_FUNCTION

void	lstadd_back(t_mini **lst, t_mini *new);
t_mini	*lstlast(t_mini *lst);
int		lstsize(t_mini *lst);

//EXEC

void	exec_arg(t_mini *lst, char **envp);

//INIT_EXEC

#endif