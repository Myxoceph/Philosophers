# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 19:18:33 by abakirca          #+#    #+#              #
#    Updated: 2024/06/26 16:34:27 by abakirca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo
INC					=	inc/
SRC_DIR				=	srcs/
OBJ_DIR				=	obj/
CC					=	gcc
CFLAGS				=	-Wall -Werror -Wextra
RM					=	rm -f

PHILO_DIR			=	$(SRC_DIR)main.c $(SRC_DIR)init.c $(SRC_DIR)simulation.c \
						$(SRC_DIR)utils.c $(SRC_DIR)getter_setter.c $(SRC_DIR)err_handle.c

SRCS 				=	$(PHILO_DIR)

OBJ 				=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))


all: 				$(NAME)

$(NAME): 			$(OBJ)
					@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)

fclean: 			clean
					@$(RM) $(NAME)

re: 				fclean all

.PHONY: 			all clean fclean re
