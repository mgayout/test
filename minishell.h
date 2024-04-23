/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:16:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/23 16:57:01 by mgayout          ###   ########.fr       */
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

typedef enum e_lex_type
{
	REDIR = 1,
	STRING,
	PIPE,
}	t_lex_type;

typedef enum e_lex_redir
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
}	t_lex_redir;

typedef enum e_lex_quote
{
	NO_QUOTE = 1,
	QUOTE,
	DQUOTE,
}	t_lex_quote;

typedef struct s_env
{
	char			*name;
	char			**value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_lex
{
	t_lex_type		type;
	char			*data;
	t_lex_redir		redir;
	int				*quote;
	int				quote_id;
	struct s_lex	*prev;
	struct s_lex	*next;
}					t_lex;

/*typedef struct s_lst
{
	int				id;
	char			*chardata;
	struct s_arg	*data;
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
	char			*prompt;
	struct s_lex	*lexer;
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

//ENV_VAR

void	env_var(t_data *data, char **arg);
int		is_an_env_var(t_env *env, char *str);
char	*strenv_var(t_env *env, char *str);
char	*strjoin_tab(char **value);

#endif