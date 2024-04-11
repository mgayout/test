# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 09:16:25 by mgayout           #+#    #+#              #
#    Updated: 2024/04/11 14:49:34 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
MINIFLAG = -lreadline -g3
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT = libft-/libft.a

SRC =	main \
		lst_arg \
		exec \
		exec_init \
		lst_function \
		

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

#OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft-/

$(NAME):
	@$(CC) $(SRCS) $(LIBFT) $(CFLAGS) $(MINIFLAG) -o $(NAME) 

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