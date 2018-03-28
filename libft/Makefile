#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okovalov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 16:01:57 by okovalov          #+#    #+#              #
#    Updated: 2018/01/15 12:47:13 by okovalov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
SRC = ft_memccpy.c ft_memcmp.c ft_memmove.c ft_strcat.c ft_strdup.c \
      ft_strlen.c ft_strncpy.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memset.c \
      ft_strcpy.c ft_strlcat.c ft_strncat.c ft_strchr.c ft_strrchr.c \
      ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
      ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
      ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
      ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
      ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
      ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
      ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
      get_next_line.c printf.c ft_libfunc.c ft_atoi_pr.c cast.c wchar.c spec.c \
      castux.c castind.c flag.c ft_del_list.c ft_lstpushback.c\

OBJ = $(SRC:.c=.o)

HEADER = libft.h get_next_line.h ft_printf.h

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -o $@ $<

clean:
		/bin/rm -f $(OBJ)

fclean: clean
		/bin/rm -f $(NAME)

re: fclean all