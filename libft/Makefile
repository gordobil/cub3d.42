# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 16:12:44 by ngordobi          #+#    #+#              #
#    Updated: 2024/01/28 18:14:41 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libft.a

CC					=	gcc
CCFLAGS				=	-Wall -Wextra -Werror

SRC_PATH			=	./

SOURCES             =   $(shell find $(SRC_PATH) -name "*.c")

OBJ_DIR             =   .objects/
OBJECTS             =   $(SOURCES:$(SRC_PATH)%.c=$(OBJ_DIR)%.o)

INCLUDE				=	../includes/libft.h

#COLORS
WHITE				=	\033[0m

.SILENT:

all:				$(NAME) $(DONE)

$(NAME):			$(OBJECTS)
					@ar rcs $(NAME) $(OBJECTS)
					echo "$(WHITE)\n · Libft compilation complete."

$(OBJ_DIR)%.o:		$(SRC_PATH)%.c | $(OBJ_DIR)
					@mkdir -p $(dir $@)
					@$(CC) $(CC_FLAGS) -c -o $@ $<

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:
					@rm -rf ./.objects/
					@rm -rf *.o
					echo "\n$(WHITE) · Libft objects removed."
					
fclean:				clean
					@rm -rf $(NAME)
					@rm -rf ../$(NAME)
					echo "$(WHITE) · Libft executable removed."

re:					fclean all

.PHONY:				all clean fclean re
