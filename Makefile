# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/05 13:16:08 by jfleisch          #+#    #+#              #
#    Updated: 2018/05/05 13:16:09 by jfleisch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

LINKER = -Llibft/ -lft

FLAGS = -Wall -Werror -Wextra -g #-fsanitize=address#lldb		remove

NORM = norminette -R CheckForbiddenSourceHeader

SRC = check.c list.c map.c piece.c place.c point.c solve.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

libft.a:
	@make -C libft/

$(NAME): libft.a $(OBJ)
	gcc $(OBJ) $(FLAGS) $(LINKER) main.c -o $(NAME)

%.o: %.c
	@gcc $(FLAGS) -c $^ -o $@

clean:
	@rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

norm:
	$(NORM)
