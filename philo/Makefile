# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 12:22:18 by ktieu             #+#    #+#              #
#    Updated: 2024/08/09 15:07:40 by ktieu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CFLAGS			=	-g  -O3 -pthread  -Wall -Wextra -Werror -I ./includes
CC				=	cc

SRC_DIR			=	./srcs/
SRC_FILES		=	$(SRC_DIR)/libft.c \
					$(SRC_DIR)/utils.c \
					$(SRC_DIR)/msg.c \
					$(SRC_DIR)/args.c \
					$(SRC_DIR)/ft_init.c \
					$(SRC_DIR)/ft_free.c \
					$(SRC_DIR)/philosopher.c \
					$(SRC_DIR)/simulation.c \
					$(SRC_DIR)/main.c



OBJ_DIR			=	obj
OBJ_FILES		=	$(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re