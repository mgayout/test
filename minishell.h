/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:16:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/18 17:48:06 by mgayout          ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			**value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

/*typedef struct s_lst
{
	int				id;
	char			*chardata;
	struct s_arg	*data;
	char			*infile;
	char			*outfile;
	bool			pipein;
	bool			pipeout;
	char			*heredoc;
	bool			append;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;*/

typedef struct s_lst
{
	int				id;
	char			*data;
	char			*status;
	int				builtins;
	char			*flag;
	char			*arg;
	char			*infile;
	char			*outfile;
	bool			pipein;
	bool			pipeout;
	char			*heredoc;
	bool			append;
	int				token;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

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
	struct s_lst	*lst;
	char			*arg1;
	char			**arg2;
	int				infile;
	int				outfile;
}					t_pid;

typedef struct s_data
{
	char			**envp;
	struct s_env	*env;
	//struct s_lst	*lst;
	//int				nb_part;
	struct s_lst	*lst;
	struct s_exec	*exec;
}					t_data;

//MAIN

void	minishell_loop(t_data *data);

//SPLIT_ENV

void	split_env(t_data *data);
void	fill_env(t_env **env, char *envp);
void	print_env(t_env *env);
t_env	*envlast(t_env *lst);
int		envsize(t_env *lst);

//PARSER

char	*add_space(char *str);

//PARSES_UTILS

int		tokenwoutsp_nb(char *str);

//ENV_VAR

void	env_var(t_data *data, char **arg);
int		is_an_env_var(t_env *env, char *str);
char	*strenv_var(t_env *env, char *str);
char	*strjoin_tab(char **value);

//LST_INIT

void	create_lst(t_lst **lst, char **arg);
void	fill_status(t_lst *lst);
void	fill_cmd(t_lst *lst);
void	fill_list(t_lst **lst, char *str);
void	set_lstargs(t_lst **lst, t_lst *new, char *str);

//LSt_lstS

char	*status_lst(t_lst *lst);
int		token_lst(char *str);
void	flag_arg(t_lst *lst);
void	before_cmd(t_lst *lst);
void	after_cmd(t_lst *lst);

//LST_IS_A

int		is_a_cmd(char *str);
void	is_a_builtins(t_lst *lst);
int		is_an_arg(t_lst **lst);
int		is_a_limiter(t_lst **lst);
int		is_a_file(t_lst **lst);

//LST_UTILS

void	print_lst(t_lst *lst);
void	free_lst(t_lst **s);
void	free_tab(char **tabtab);

//LST_FUNCTION

void	lstadd_back(t_lst **lst, t_lst *new);
t_lst	*lstlast(t_lst *lst);
int		lstsize(t_lst *lst);

//EXEC

void	exec(t_data *data);
void	exec_a_cmd(t_data *data);
void	exec_pipeline(t_data *data);

//EXEC_INIT

void	init_exec(t_data *data);
void	init_child(t_data *data);
void	init_heredoc(t_data *data);

//EXEC_OPEN

void	open_pipe(t_data *data);
void	open_infile(t_data *data);
void	open_outfile(t_data *data);
void	open_files(t_data *data);

//EXEC_CMD

void	children(t_data *data);
char	*ft_lst1(char *str);
char	**ft_lst2(t_data *data);

//BUILTINS

void	exec_builtins(t_data *data);

//ECHO

void	echo_builtin(t_data *data);

//CD

int		cd_builtin(void);

//PWD

int		pwd_builtin(void);

//EXPORT

int		export_builtin(void);

//UNSET

int		unset_builtin(void);

//ENV
int		env_builtin(void);

//EXIT

int		exit_builtin(void);

#endif