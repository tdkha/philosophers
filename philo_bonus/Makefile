# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 12:22:18 by ktieu             #+#    #+#              #
#    Updated: 2024/08/28 19:10:17 by ktieu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS		=	philo_bonus

CFLAGS			=	-g -Wall -Wextra -Werror -pthread -O3 -I ./includes
CC				=	cc

BONUS_DIR		=	./srcs/
BONUS_FILES		=	$(BONUS_DIR)/libft_bonus.c \
					$(BONUS_DIR)/utils_bonus.c \
					$(BONUS_DIR)/ft_make_sem.c \
					$(BONUS_DIR)/msg_bonus.c \
					$(BONUS_DIR)/args_bonus.c \
					$(BONUS_DIR)/ft_init_bonus.c \
					$(BONUS_DIR)/ft_free_bonus.c \
					$(BONUS_DIR)/process_bonus.c \
					$(BONUS_DIR)/routine_utils_bonus.c \
					$(BONUS_DIR)/monitor_bonus.c \
					$(BONUS_DIR)/routine_bonus.c \
					$(BONUS_DIR)/main_bonus.c

OBJ_DIR			=	obj
BONUS_OBJ_FILES	=	$(BONUS_FILES:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)


$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
all: $(NAME_BONUS)

$(NAME): $(BONUS_OBJ_FILES)
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJ_FILES)
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
