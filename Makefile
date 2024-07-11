# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 11:33:19 by ryusupov          #+#    #+#              #
#    Updated: 2024/07/11 12:57:18 by ryusupov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -g
RM		:= rm -rf

LIBFT_PATH  := ./libft
OBJ_PATH	:= ./obj
P_SRC_PATH	:= ./_p_srcs
E_SRC_PATH	:= ./_e_srcs
MAIN		:= main.c
SRC_FILES	:= ./_p_srcs/_init_cmd.c \
			   ./_p_srcs/_handle_signals.c \
			   ./_p_srcs/_errors.c

OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES:.c=.o))
MAIN_OBJ	:= $(OBJ_PATH)/main.o

LIBFT		:= $(LIBFT_PATH)/libft.a

all: update $(NAME)

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE COMMAND IN MAC
rl:
	@brew install readline

#IF SUBMODULE IS NOT EXISTS IN THE REPO, FETCH AND UPDATE
update:
	@git submodule update --init --recursive

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE LINUX (LINUX ONLY)
linux: update readline_linux_install $(NAME)

#COMMAND TO INSTALL READLINE ON LINUX
readline_linux_install:
	@sudo apt install libreadline-dev

$(NAME): $(MAIN_OBJ) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(P_SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re git_sub_update
