# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 08:49:04 by gude-jes          #+#    #+#              #
#    Updated: 2024/09/17 11:29:40 by maugusto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g

READLINE_PATH	= vendor/readline/
RLFLAG 			= -L$(READLINE_PATH)/lib -lreadline

NAME		= minishell

INC			= -I./includes
RM			= rm -rf

GENERAL		= main
PARSE		= parse tokens count_tokens handle_splited
EXECUTOR	= executor handle_cd handle_echo handle_exit handle_pwd handle_env handle_export handle_export2 handle_unset signals pipes check_pipe
CMD			= handle_cmd handle_cmd2 redirects
EXPANDER	= expander expander_utils expander_utils2
UTILS		= cmd_utils token_utils env_utils env_utils2 utils freedom echo_redirects

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH		= src src/parse\
				src/expander\
				src/executor\
				src/executor/cd\
				src/executor/pwd\
				src/executor/env\
				src/executor/exit\
				src/executor/echo\
				src/executor/export\
				src/executor/unset\
				src/executor/pipes\
				src/cmds\
				src/utils\
				

LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a

SRC			= $(addsuffix .c, $(GENERAL))\
				$(addsuffix .c, $(PARSE))\
				$(addsuffix .c, $(EXECUTOR))\
				$(addsuffix .c, $(EXPANDER))\
				$(addsuffix .c, $(CMD))\
				$(addsuffix .c, $(UTILS))\



OBJ_DIR		= obj

OBJS		= $(SRC:%.c=$(OBJ_DIR)/%.o)

BONUS_OBJS	= $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: deps $(NAME)

deps:
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR):
	@mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS) $(LIBFT)
	@$(CC) $(CFLAGS) $(RLFLAG) $(OBJS) $(LIBFT) -o $(NAME)

valgrind: 
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(RM) $(OBJS) readline.supp

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_PATH) 
	@$(RM) $(NAME) $(OBJ_DIR)

re: fclean all