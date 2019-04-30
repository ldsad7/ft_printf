# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/30 16:46:52 by tsimonis          #+#    #+#              #
#    Updated: 2019/02/02 13:48:38 by sdurgan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME := libftprintf.a

SRCS := ft_printf.c change_base.c ft_putchar_unicode.c print.c print_char.c \
	print_double.c print_double_hex.c print_int.c print_int_hex.c \
	print_n.c print_octal.c print_pointer.c print_str.c print_unsigned.c \
	ft_bzero.c ft_itoa_long.c ft_itoa_unsigned_long.c ft_strchr.c ft_strdel.c \
	ft_strlen.c ft_strcmp.c ft_strdup.c ft_memset.c print_percent.c \
	addition_print.c ft_strsub.c addition_double_hex_first.c addition_int.c \
	addition_double_hex_second.c add_0x.c double_math.c process_f.c ft_min.c \
	ft_strlen_wstr.c ft_abs.c

OBJS := $(SRCS:%.c=%.o)

CFLAGS := -Wall -Werror -Wextra
INCS := .
CC := gcc

all: $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCS)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
