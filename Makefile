# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 08:49:04 by gude-jes          #+#    #+#              #
#    Updated: 2024/11/04 09:06:10 by gude-jes         ###   ########.fr        #
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
PARSE		= parse tokens count_tokens handle_splited heredoc_pipe
EXECUTOR	= executor handle_cd handle_echo handle_exit handle_pwd handle_env handle_export handle_export2 handle_export3 handle_unset signals echo_utils echo_utils2 parse_echo
CMD			= handle_cmd handle_cmd2 handle_cmd3
EXPANDER	= expander expander_utils expander_utils2 expander_utils3
UTILS		= cmd_utils token_utils env_utils env_utils2 token_utils2 token_utils3 freedom echo_redirects cd_utils export_utils cmd_utils2 parse_utils parse_utils2 export_utils2
PIPES		= pipes pipes2 check_pipe
REDIRECTS  = redirects redirects_utils handle_redirects redirects_utils2

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
				src/pipes\
				src/redirects
				

LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a

SRC			= $(addsuffix .c, $(GENERAL))\
				$(addsuffix .c, $(PARSE))\
				$(addsuffix .c, $(EXECUTOR))\
				$(addsuffix .c, $(EXPANDER))\
				$(addsuffix .c, $(CMD))\
				$(addsuffix .c, $(UTILS))\
				$(addsuffix .c, $(PIPES))\
				$(addsuffix .c, $(REDIRECTS))\


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
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAG) $(LIBFT) -o $(NAME)

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