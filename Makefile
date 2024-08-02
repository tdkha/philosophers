# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 12:22:18 by ktieu             #+#    #+#              #
#    Updated: 2024/08/02 13:18:18 by ktieu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
NAME_BONUS		=	philo_bonus

CFLAGS			=	-g -O3 -pthread -Wall -Wextra -Werror -I ./includes
CC				=	cc

SRC_DIR			=	./srcs/mandatory
SRC_FILES		=	$(SRC_DIR)/libft.c \
					$(SRC_DIR)/utils.c \
					$(SRC_DIR)/msg.c \
					$(SRC_DIR)/args.c \
					$(SRC_DIR)/ft_init.c \
					$(SRC_DIR)/ft_free.c \
					$(SRC_DIR)/main.c

BONUS_DIR		=	./srcs/bonus
BONUS_FILES		=	$(BONUS_DIR)/libft.c \
					$(BONUS_DIR)/utils.c \
					$(BONUS_DIR)/msg.c \
					$(BONUS_DIR)/args.c \
					$(BONUS_DIR)/ft_init.c \
					$(BONUS_DIR)/ft_free.c \
					$(BONUS_DIR)/main.c

OBJ_DIR			=	obj
OBJ_FILES		=	$(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ_FILES	=	$(BONUS_FILES:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJ_FILES)
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus