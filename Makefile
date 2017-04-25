#  **************************************************************************  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/01 00:00:00 by jcarra            #+#    #+#              #
#    Updated: 2017/04/12 16:51:04 by jcarra           ###   ########.fr        #
#                                                                              #
#  **************************************************************************  #

NAME		=   libft_malloc_$(HOSTTYPE).so
NAMELN		=   libft_malloc.so

ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRC		=   ft_putstr.c \
            ft_putnbr.c \
            mem.c \
            malloc.c \
            show_alloc_mem.c \
            free.c

DIRSRC		=	sources/
DIRINC		=	include/

SRCS		=	$(SRC:%=$(DIRSRC)%)

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -fPIC
LFLAGS		=

CC		=	gcc
LN      =   ln -s
RM		=	rm -f
ECHO		=	printf


all		:	$(NAME)
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[34mAll\033[0m] ->\033[32m\tReady\n\033[0m'
$(NAME)		:	.hide
			@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS)
			@$(LN) $(NAME) $(NAMELN)

%.o		:	%.c
			@$(CC) -o $@ -c $< $(CFLAGS)
			@$(ECHO) '- \b> \033[36m$@\033[0m\n'

.hide		:	$(OBJS)
			@touch .hide
			@chmod 755 .hide
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[33mSources\033[0m] ->\033[32m	Ready\n\033[0m'

clean		:
			@$(RM) $(OBJS) .hide
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mDirectory cleaned\n\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(RM) $(NAMELN)
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mRemove executable\n\033[0m'

re		:	fclean all

.PHONY		:	all clean fclean re

