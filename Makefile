# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 11:33:19 by ryusupov          #+#    #+#              #
#    Updated: 2024/07/08 11:44:02 by ryusupov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -g
RM		:= rm -rf


OBJ_PATH	:= ./obj
P_SRC_PATH	:= ./p_srcs
E_SRC_PATH	:= ./e_srcs
MAIN		:= main.c
SRC_FILES	:=


OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES))
MAIN_OBJ	:= $(OBJ_PATH)/main.o


all: git_sub_update $(NAME)


git_sub_update:
	@git submodule update --init --recursive

$(NAME): $(MAIN_OBJ) $(SRC_FILES)
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re git_sub_update
