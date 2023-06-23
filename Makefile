# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 19:25:47 by alaaouam          #+#    #+#              #
#    Updated: 2023/06/23 12:07:26 by alaaouam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	COLOURS	#

GREEN = \033[0:32m
COLOR_OFF = \033[0m

#	VARIABLES	#

NAME = minishell

SRC = main.c command_line.c signals.c lexer.c lexer_utils.c tokens.c free_utils.c parser.c parser_utils.c check_syntax.c check_syntax_utils.c \
			get_args.c get_commands.c get_path.c get_path_utils.c copy_env.c env.c get_variable.c get_variable_utils.c get_commands_utils.c \
			get_value.c array_utils.c heredoc.c heredoc_utils.c quotes_utils.c quote_remove_utils.c heredoc_to_file.c cmd_expansion.c error_utils.c \
			execute.c process.c process_utils.c redirections.c file_utils.c exec_built_in.c cd.c echo.c exit.c export.c pwd.c unset.c export_utils.c \
			export_utils_2.c export_utils_3.c general_utils.c env_utils.c quotes.c cmd_expansion_utils.c exit_utils.c overflow_utils.c check_redir_error.c \
			expand_cmd.c expand_arg.c add_args.c redir_expansion.c token_utils.c echo_utils.c quotes_utils2.c
			

SRC_PATH = src/*/
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

INC = inc/
LIBFT_INC = libft/include
READLINE_INC = /opt/homebrew/opt/readline/include
#READLINE_INC = /usr/lib/x86_64-linux-gnu/

CC = gcc
CFLAGS =  -Wall -Wextra  -I $(INC) -I $(LIBFT_INC) -I $(READLINE_INC) #-fsanitize=address
LFLAGS = -lreadline -L /opt/homebrew/opt/readline/lib
#LFLAGS = -lreadline #-L /usr/lib/x86_64-linux-gnu/
RM = rm -rf

#	RULES	#

all: $(NAME)

$(LIBFT): $(LIBFT_PATH)
	@make -C $(LIBFT_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)<+> Minishell has been created! <+>$(COLOR_OFF)"

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_PATH)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)
	@echo "$(GREEN)<-> Minishell cleaned successfuly! <->$(COLOR_OFF)"

re: fclean all

.PHONY: all clean fclean re
