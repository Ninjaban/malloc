#  **************************************************************************  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/01 00:00:00 by jcarra            #+#    #+#              #
#    Updated: 2017/04/25 14:57:22 by mrajaona         ###   ########.fr        #
#                                                                              #
#  **************************************************************************  #

NAME		=   libft_malloc_$(HOSTTYPE).so
NAMELN		=   libft_malloc.so

ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRC		=   ft_tools_string.c \
            ft_tools_number.c \
	        ft_tools_realloc.c \
	        ft_tools_malloc.c \
            mem.c \
            malloc.c \
    	    calloc.c \
            show_alloc_mem.c \
			realloc.c \
			reallocf.c \
            free.c \
            mutex.c

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
			@$(ECHO) '> \033[36m$@\033[0m\n'

.hide		:	$(OBJS)
			@touch .hide
			@chmod 755 .hide
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[33mSources\033[0m] ->\033[32m	Ready\n\033[0m'

clean		:
			@$(RM) test0 test1 test2 test3 test3b test4 test5 test6
			@$(RM) $(OBJS) .hide
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mDirectory cleaned\n\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(RM) $(NAMELN)
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mRemove executable\n\033[0m'

re		:	fclean all

test		:
			@$(CC) tests/test0.c -o test0 -I ./$(DIRINC)
			@$(CC) tests/test1.c -o test1 -I ./$(DIRINC)
			@$(CC) tests/test2.c -o test2 -I ./$(DIRINC)
			@$(CC) tests/test3.c -o test3 -I ./$(DIRINC)
			@$(CC) tests/test3b.c -o test3b -I ./$(DIRINC)
			@$(CC) tests/test4.c -o test4 -I ./$(DIRINC)
			@$(CC) tests/test5.c -o test5 -I ./$(DIRINC) -L. -lft_malloc
			@$(CC) tests/test6.c -o test6 -I ./$(DIRINC)

.PHONY		:	all clean fclean re

