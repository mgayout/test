# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 14:27:16 by mgayout           #+#    #+#              #
#    Updated: 2023/11/09 14:27:16 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
SRC 			=	ft_putchar_fd ft_putstr_fd ft_putnbr_fd ft_strlen

SRC_A			=	$(addsuffix .c, ${SRC})

OBJ				=	$(SRC_A:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJ) 
					ar -rc $(NAME) $(OBJ)

clean:
					$(RM) $(OBJ)

fclean: 		clean
					$(RM) $(NAME)

re:				fclean all

.PHONY: 		all clean fclean re