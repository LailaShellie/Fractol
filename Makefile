# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lshellie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 14:20:33 by lshellie          #+#    #+#              #
#    Updated: 2019/11/04 14:20:34 by lshellie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c draw.c keyboard.c init_cl.c close.c mouse.c

OBJ = $(SRC:.c=.o)

NAME = fractol

LIB = libft/libft.a

MLX = ./mlx/libmlx.a

all: $(LIB) $(NAME)

$(LIB):
	make -C ./libft
$(MLX):
	make -C ./mlx
$(NAME): $(MLX) $(OBJ) fractol.h
	gcc -Wall -Wextra -Werror -o $(NAME) -I fract-ol.h $(LIB) $(MLX) -lmlx -framework OpenGL -framework AppKit -framework OpenCL $(OBJ)
%.o: src/%.c fractol.h
	gcc -c $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
re: fclean all