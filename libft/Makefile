# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 17:16:27 by alaaouam          #+#    #+#              #
#    Updated: 2023/03/15 10:48:29 by alaaouam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	COLOURS	#

GREEN = \033[0:32m
COLOR_OFF = \033[0m

#	VARIABLES	#

NAME = libft.a

SRC = ft_atoi.c ft_itoa.c ft_split.c ft_lstiter.c ft_bzero.c ft_strlen.c ft_strchr.c \
					ft_calloc.c ft_isdigit.c ft_lstlast.c ft_lstsize.c ft_isascii.c ft_substr.c \
					ft_strjoin.c ft_isprint.c ft_strdup.c ft_lstnew.c ft_strlcat.c ft_strnstr.c \
					ft_strrchr.c ft_striteri.c ft_lstmap.c ft_strlcpy.c ft_strtrim.c ft_isalpha.c \
					ft_tolower.c ft_lstclear.c ft_strmapi.c ft_toupper.c ft_isalnum.c ft_memset.c \
					ft_memchr.c ft_strncmp.c ft_memcpy.c ft_lstdelone.c ft_memcmp.c ft_putstr_fd.c \
					ft_putnbr_fd.c ft_memmove.c ft_putendl_fd.c ft_putchar_fd.c ft_lstadd_back.c ft_lstadd_front.c \
					ft_printf.c ft_printf_utils.c print_char_utils.c print_nbr_utils.c print_ptr_utils.c \
					get_next_line.c get_next_line_utils.c

INCLUDE = include/

SRC_PATH = src/*/
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE)
RM = rm -rf

#	RULES	#

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(INCLUDE)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)<+> Libft has been created! <+>$(COLOR_OFF)"

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)<-> Libft cleaned successfuly! <->$(COLOR_OFF)"

re: fclean all

.PHONY: all clean fclean re