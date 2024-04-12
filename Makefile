# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 09:16:25 by mgayout           #+#    #+#              #
#    Updated: 2024/04/12 12:24:29 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
MINIFLAG = -lreadline -g3
SRC_DIR = src/
SRC_LST_DIR = src/lst/
SRC_EXEC_DIR = src/exec/
OBJ_DIR = obj/
LIBFT = libft-/libft.a

SRC =	main \

SRC_LST =	lst_init \
			lst_fill \
			lst_utils \
			lst_function \

SRC_EXEC =	exec \
			exec_init \

SRCS =	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

SRCS_LST =	$(addprefix $(SRC_LST_DIR), $(addsuffix .c, $(SRC_LST)))
		
SRCS_EXEC =	$(addprefix $(SRC_EXEC_DIR), $(addsuffix .c, $(SRC_EXEC)))

#OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft-/

$(NAME):
	@$(CC) $(SRCS) $(SRCS_LST) $(SRCS_EXEC) $(LIBFT) $(CFLAGS) $(MINIFLAG) -o $(NAME) 

#$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	mkdir -p $(@D)
#	$(CC) $(LIBFT) $(CFLAGS) -c $< -o $@

clean:
#	$(RM) $(OBJ_DIR)
	make clean -C libft-/

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft-/

re: fclean all

.PHONY: all clean fclean re