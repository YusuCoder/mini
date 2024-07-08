# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 11:33:19 by ryusupov          #+#    #+#              #
#    Updated: 2024/07/08 19:09:03 by ryusupov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -g
RM		:= rm -rf


LIBFT_PATH  := ./libft
OBJ_PATH	:= ./obj
P_SRC_PATH	:= ./p_srcs
E_SRC_PATH	:= ./e_srcs
MAIN		:= main.c
SRC_FILES	:=


OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES))
MAIN_OBJ	:= $(OBJ_PATH)/main.o

LIBFT		:= $(LIBFT_PATH)/libft.a

all: git_sub_update readline_install $(NAME)
#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE COMMAND
readline_install:
	@if ! brew list readline > /dev/null 2>&1; then \
		brew install readline; \
	fi
#IF SUBMODULE IS NOT EXISTS IN THE REPO, FETCH AND UPDATE
git_sub_update:
	@git submodule update --init --recursive

$(NAME): $(MAIN_OBJ) $(SRC_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re git_sub_update
