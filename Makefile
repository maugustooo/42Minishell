# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 12:43:46 by gude-jes          #+#    #+#              #
#    Updated: 2024/07/29 12:49:07 by gude-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
NAME		= minishell

INC			= -I./includes
RM			= rm -rf

GENERAL		= main

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH		= src

LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a

SRC			= $(addsuffix .c, $(GENERAL))\


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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(RM) $(OBJS)

fclean: clean clean_bonus
	@$(MAKE) fclean -C $(LIBFT_PATH) 
	@$(RM) $(NAME) $(OBJ_DIR)

re: fclean all