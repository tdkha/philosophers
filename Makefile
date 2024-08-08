# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 12:22:18 by ktieu             #+#    #+#              #
#    Updated: 2024/08/08 15:56:38 by ktieu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
NAME_BONUS		=	philo_bonus

CFLAGS			=	-g  -O3 -pthread  -I ./includes
CC				=	cc

SRC_DIR			=	./srcs/philo
SRC_FILES		=	$(SRC_DIR)/libft.c \
					$(SRC_DIR)/utils.c \
					$(SRC_DIR)/msg.c \
					$(SRC_DIR)/args.c \
					$(SRC_DIR)/ft_init.c \
					$(SRC_DIR)/ft_free.c \
					$(SRC_DIR)/philosopher.c \
					$(SRC_DIR)/simulation.c \
					$(SRC_DIR)/main.c

BONUS_DIR		=	./srcs/philo_bonus
BONUS_FILES		=	$(BONUS_DIR)/libft_bonus.c \
					$(BONUS_DIR)/utils_bonus.c \
					$(BONUS_DIR)/msg_bonus.c \
					$(BONUS_DIR)/args_bonus.c \
					$(BONUS_DIR)/ft_init_bonus.c \
					$(BONUS_DIR)/ft_free_bonus.c \
					$(BONUS_DIR)/process_bonus.c \
					$(BONUS_DIR)/routine_utils_bonus.c \
					$(BONUS_DIR)/routine_bonus.c \
					$(BONUS_DIR)/main_bonus.c

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