CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g

READLINE_PATH	= vendor/readline/
RLFLAG 			= -L$(READLINE_PATH)/lib -lreadline

NAME		= minishell

INC			= -I./includes
RM			= rm -rf

GENERAL		= main
PARSE		= parse tokens utils freedom
EXECUTOR	= executor handle_cd handle_echo handle_exit handle_pwd handle_env handle_export

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH		= src src/parse\
				src/parse/utils\
				src/executor\
				src/executor/cd\
				src/executor/pwd\
				src/executor/env\
				src/executor/exit\
				src/executor/echo\
				src/executor/export\
				

LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a

SRC			= $(addsuffix .c, $(GENERAL))\
				$(addsuffix .c, $(PARSE))\
				$(addsuffix .c, $(EXECUTOR))\


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