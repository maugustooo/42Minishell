# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 08:48:35 by gude-jes          #+#    #+#              #
#    Updated: 2024/08/27 11:09:38 by gude-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g

NAME			= libft.a

LIB_SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c ft_str_isalpha.c ft_isspace.c\
					ft_strlcat.c ft_strncmp.c ft_strcmp.c ft_substr.c ft_atoi.c ft_isalpha.c ft_strclen.c\
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c ft_strncpy.c ft_find_c.c\
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_striteri.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c\
					ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c\
					get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c\
					ft_printf/ft_printf_utils.c ft_printf/ft_printf.c\
					ft_printf/ft_putchar.c ft_printf/ft_putnbrhex.c\
					ft_printf/ft_putptr.c ft_printf/ft_uitoa.c\
					ft_printf_fd/ft_printf_utils_fd.c ft_printf_fd/ft_printf_fd.c\
					ft_printf_fd/ft_putchar_fd.c ft_printf_fd/ft_putnbrhex_fd.c\
					ft_printf_fd/ft_putptr_fd.c ft_printf_fd/ft_uitoa_fd.c
OBJS			= $(LIB_SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus