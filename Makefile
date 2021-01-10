# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artmende <artmende@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 18:29:53 by artmende          #+#    #+#              #
#    Updated: 2021/01/05 11:46:30 by artmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

MAKELIB = ar rc

CFLAGS = -Wall -Wextra -Werror

LIBFTA = libft.a

SRCS =	fct.c \
		cases.c \

OBJS = $(SRCS:.c=.o)

OBJSLIBFT =	./libft/ft_atoi.o \
			./libft/ft_calloc.o \
			./libft/ft_strchr.o \
			./libft/ft_strlen.o \

NAME = libftprintf.a

RM = rm -f

$(NAME): $(OBJS) $(OBJSLIBFT)
	$(MAKELIB) $(NAME) $(OBJS) $(OBJSLIBFT)

$(OBJSLIBFT):
	cd libft && make

all: $(NAME)

re: fclean all

clean:
	$(RM) $(OBJS)
	cd libft && make fclean

fclean: clean
	$(RM) $(NAME)

.PHONY: clean fclean re all
