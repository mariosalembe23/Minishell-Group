# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 08:43:12 by codespace         #+#    #+#              #
#    Updated: 2024/11/01 09:57:07 by msalembe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = minishell.c actions.c utils.c \
	list.c actions_1.c actions_2.c \
	signal.c actions_3.c token.c \
	token_utils.c tokenization.c parse_token.c list_1.c

CC = cc
FLAGS = -Wall -Werror -Wextra
LIBFTDIR = libft

OBJ = $(SRC:.c=.o)

BOLD_PURPLE = \033[1;35m
BOLD_CYAN   = \033[1;36m
BOLD_YELLOW = \033[1;33m
NO_COLOR    = \033[0m

# ------------------------------ Mensagens ------------------------------

COMP_START  = printf "🚧 $(BOLD_YELLOW)Make: $(NO_COLOR) Iniciando a Compilação...\n$(NO_COLOR)"
SERV_READY  = printf "🗿 $(BOLD_CYAN)Shell Pronto!\n$(NO_COLOR)"

# ----------------------------- BONUS ------------------------------------

CLEANED     = printf "💧 $(BOLD_YELLOW)Clean: $(NO_COLOR)Removendo todos \".o\" files \n$(NO_COLOR)"
FCLEANED    = printf "🧼 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Removendo os Executáveis \n$(NO_COLOR)"

# ------------------------------ Regras ------------------------------

all: $(NAME)

$(NAME): $(OBJ)
	@$(COMP_START)
	@$(MAKE) -C $(LIBFTDIR)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L$(LIBFTDIR) -lft -lreadline
	@$(SERV_READY)

$(OBJ): %.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(CLEANED)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(FCLEANED)

re: fclean all

.PHONY: all clean fclean re