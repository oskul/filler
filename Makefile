# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sshiling <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 13:34:29 by sshiling          #+#    #+#              #
#    Updated: 2018/03/19 13:34:38 by sshiling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = oskulska.filler

SRCS = main.c read_map.c read_piece.c find_solution.c 

LIBFT = libft/

OBJECTS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Creating .o files. Please wait..."
	@make -C $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) -L $(LIBFT) -lftprintf
	@echo "All .o files successfully created."
	@echo "Executable successfully created."

clean:
	@echo "Deleting all .o files. Please wait..."
	@rm -f $(OBJECTS)
	@make clean -C $(LIBFT)
	@echo "All .o files deleted."	

fclean: clean
	@echo "Deleting all .o files and executable. Please wait..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo "All .o files and executable deleted."	

re: fclean all

.PHONY: re all clean fclean
