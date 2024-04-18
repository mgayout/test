# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 09:16:25 by mgayout           #+#    #+#              #
#    Updated: 2024/04/18 17:44:22 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
MINIFLAG = -lreadline -g3
SRC_DIR = src/
SRC_PAR_DIR = src/parser/
SRC_LST_DIR = src/lst/
SRC_EXEC_DIR = src/exec/
SRC_BUIL_DIR = src/builtins/
OBJ_DIR = obj/
LIBFT = libft+/libft.a

SRC =	main \
		split_env \
		env_var \

SRC_PAR =	parser \
			parser_utils \

SRC_LST =	lst_init \
			lst_utils \
			lst_function \
			lst_args \
			lst_is_a \

SRC_EXEC =	exec \
			exec_init \
			exec_pipe \
			exec_cmd \

SRC_BUIL =	builtins \
			echo \
			cd \
			pwd \
			export \
			unset \
			env \
			exit \

SRCS =	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

SRCS_PAR = $(addprefix $(SRC_PAR_DIR), $(addsuffix .c, $(SRC_PAR)))

SRCS_LST =	$(addprefix $(SRC_LST_DIR), $(addsuffix .c, $(SRC_LST)))
		
SRCS_EXEC =	$(addprefix $(SRC_EXEC_DIR), $(addsuffix .c, $(SRC_EXEC)))

SRCS_BUIL = $(addprefix $(SRC_BUIL_DIR), $(addsuffix .c, $(SRC_BUIL)))

#OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft+/

$(NAME):
	@$(CC) $(SRCS) $(SRCS_PAR) $(SRCS_LST) $(SRCS_EXEC) $(SRCS_BUIL) $(LIBFT) $(CFLAGS) $(MINIFLAG) -o $(NAME) 

#$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	mkdir -p $(@D)
#	$(CC) $(LIBFT) $(CFLAGS) -c $< -o $@

clean:
#	$(RM) $(OBJ_DIR)
	make clean -C libft+/

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft+/

re: fclean all

.PHONY: all clean fclean re