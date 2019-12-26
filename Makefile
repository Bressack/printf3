# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 16:56:08 by tharchen          #+#    #+#              #
#    Updated: 2019/11/17 21:16:50 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libftprintf.a

GCC				=	gcc

FLAGS			=	-Wall -Wextra -Werror #-g3 -fsanitize=address

# **************************************************************************** #

HEADER_DIR		=	includes/

HEADER_LIST		=	\
					ft_printf.h	\

HEADER			=	$(addprefix $(HEADER_DIR), $(HEADER_LIST))

# **************************************************************************** #

SRCS_DIR		=	srcs/

SRCS_LIST		=	\
					conv_cs.c		\
					conv_doxibu.c	\
					conv_n.c		\
					ft_printf.c		\
					write_buf.c		\
					precminsign.c	\

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# **************************************************************************** #

OBJS_DIR		=	objs/

OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))

OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@ printf "\033[37;01mlinking...\033[0m"
	@ ar rcs $@ $?
	@ printf "\033[37;01m done !\033[0m\n"
	@ printf "\033[37;01mindexing...\033[0m"
	@ ranlib $@
	@ printf "\033[37;01m done !\033[0m\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(OBJS_DIR)
	@ $(GCC) $(FLAGS) -I $(HEADER_DIR) -c -o $@ $<
	@ echo "\033[31mLibrairy \033[32mprintf: \033[34mCompilation of \033[36m$(notdir $<)\033[0m"

clean:
	@ rm -rf $(OBJS_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean all
