# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alouisy- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/25 17:33:36 by alouisy-          #+#    #+#              #
#    Updated: 2017/02/25 17:33:39 by alouisy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCS = main.c hooks.c gfx.c

OBJS = $(SRCS:.c=.o)

LIBS = -L minilibx_macos/ -lmlx -L libft/ -lft -lm

INCLUDES = -I. -I libft/includes/. -I minilibx_macos/.

FRAMEWORKS = -framework OpenGL -framework AppKit

CFLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME):
	@make -C libft/
	@make -C minilibx_macos/
	@gcc $(CFLAGS) -c $(SRCS) $(INCLUDES)
	@gcc $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LIBS) $(FRAMEWORKS)
	@echo "\"fractol\" has been succefully created !"

clean:
	@make -C libft/ clean
	@make -C minilibx_macos/ clean
	@/bin/rm -f $(OBJS)
	@echo "FRACTOL Object files deleted."

fclean: clean
	@make -C libft/ fclean
	@make -C minilibx_macos/ clean
	@/bin/rm -f $(NAME)
	@echo "FRACTOL Executable deleted."

re: fclean all

.PHONY: clean