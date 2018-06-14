#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okovalov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 13:37:35 by okovalov          #+#    #+#              #
#    Updated: 2018/01/22 13:37:37 by okovalov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

SRC =	main.c \
        rooms.c \

OBJ = $(SRC:.c=.o)

CC = gcc

FLGS = -Wall -Wextra -Werror

INC = ./

LIB = -L ./libft/ -lft

all: $(NAME)

$(NAME): $(OBJ)
		make -C ./libft/
		$(CC) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c
		$(CC) $(FLGS) -c $<

clean:
		make -C ./libft/ clean
		rm -rf $(OBJ)

fclean: clean
		make -C ./libft/ fclean
		rm -f $(NAME)

re: fclean all