/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:16:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/17 09:26:03 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft+/libft.h"
# include "libft+/ft_printf+/ft_printf.h"
# include "libft+/get_next_line+/get_next_line.h"

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

typedef struct s_arg
{
	int				id;
	char			*data;
	char			*status;
//	int				builtins;
	char			*flag;
	char			*arg;
	char			*infile;
	char			*outfile;
	bool			pipein;
	bool			pipeout;
	char			*heredoc;
	bool			append;
	int				token;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

typedef struct s_exec
{
	int				pipefd[2];
	int				std_in;
	int				std_out;
	bool			heredoc;
	int				*pid;
	int				nb_cmd;
	int				nb_arg;
	int				status;
	struct s_pid	*child;
}					t_exec;

typedef struct s_pid
{
	struct s_arg	*lst;
	char			*arg1;
	char			**arg2;
	int				infile;
	int				outfile;
}					t_pid;

typedef struct s_data
{
	char			**envp;
	struct s_arg	*lst;
	struct s_exec	*exec;
}					t_data;

//MAIN

void	minishell_loop(t_data *data);

//LST_INIT

void	create_lst(t_arg **lst, char **arg);
void	fill_status(t_arg *lst);
void	fill_cmd(t_arg *lst);

//LST_FILL

void	fill_list(t_arg **lst, char *str);
char	*status_lst(t_arg *lst);
int		token_lst(char *str);
void	flag_arg(t_arg *lst);
void	before_cmd(t_arg *lst);
void	after_cmd(t_arg *lst);

//LST_UTILS

int		is_a_cmd(char *str);
int		is_an_arg(t_arg **lst);
int		is_a_limiter(t_arg **lst);
int		is_a_file(t_arg **lst);
void	print_lst(t_arg *lst);
void	free_lst(t_arg **s);
void	free_tab(char **tabtab);

//LST_FUNCTION

void	lstadd_back(t_arg **lst, t_arg *new);
t_arg	*lstlast(t_arg *lst);
int		lstsize(t_arg *lst);

//EXEC

void	exec_arg(t_data *data);
void	open_pipe(t_data *data);
void	children(t_data *data);
char	*ft_arg1(char *str);
char	**ft_arg2(t_data *data);
t_arg	*good_cmd(t_data *data);

//EXEC_INIT

void	init_exec(t_data *data);
void	init_child(t_data *data);
void	init_heredoc(t_data *data);

#endif