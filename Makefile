# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 12:12:49 by ngordobi          #+#    #+#              #
#    Updated: 2024/04/10 14:19:24 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	cub3d

CC					=	gcc
CC_FLAGS			=	-Wall -Wextra -Werror
MLX_FLAGS			=	-L mlx/ -lmlx -lXext -lX11 -lm

SRC_PATH			=	./src/
GAME_PATH			=	./src/game/
PARS_PATH			=	./src/parsing/
LIBFT_PATH			=	./libft/
MLX_PATH			=	./mlx/

LIBFT				=	$(LIBFT_PATH)libft.a
MLX					=	./mlx/libmlx_Linux.a

SOURCES				=	$(GAME_PATH)draw.c \
						$(GAME_PATH)init_textures.c \
						$(GAME_PATH)minimap.c \
						$(GAME_PATH)mlx.c \
						$(GAME_PATH)render_frame.c \
						$(GAME_PATH)render_textures.c \
						$(GAME_PATH)walk.c \
						$(PARS_PATH)colors.c \
						$(PARS_PATH)file.c \
						$(PARS_PATH)map_check.c \
						$(PARS_PATH)map.c \
						$(PARS_PATH)parsing_utils.c \
						$(SRC_PATH)cub3d.c \
						$(SRC_PATH)exit.c \

OBJ_DIR				=	.objects/
OBJECTS				=	$(SOURCES:$(SRC_PATH)%.c=$(OBJ_DIR)%.o)

INCLUDES			=	./includes/cub3d.h \
						./includes/libft.h \

ZoneIdentifiers		=   $(shell find -name "*:Zone.Identifier")

#COLORS
BLUE				=	\033[1;34m
BOLD_BLUE			=	\033[0;34m
WHITE				=	\033[0m

define CUB3D
$(BOLD_BLUE)

                     ▓▓▓▓▓      ▓▓▓▓▓▓▓▓      ▓▓▓▓▓
                    ░░▓▓▓      ▓▓▓░░░░▓▓▓    ░░▓▓▓ 
  ▓▓▓▓▓▓  ▓▓▓▓▓ ▓▓▓▓ ░▓▓▓▓▓▓▓ ░░░    ░▓▓▓  ▓▓▓▓▓▓▓ 
 ▓▓▓░░▓▓▓░░▓▓▓ ░▓▓▓  ░▓▓▓░░▓▓▓   ▓▓▓▓▓▓░  ▓▓▓░░▓▓▓ 
░▓▓▓ ░░░  ░▓▓▓ ░▓▓▓  ░▓▓▓ ░▓▓▓  ░░░░░░▓▓▓░▓▓▓ ░▓▓▓ 
░▓▓▓  ▓▓▓ ░▓▓▓ ░▓▓▓  ░▓▓▓ ░▓▓▓ ▓▓▓   ░▓▓▓░▓▓▓ ░▓▓▓ 
░░▓▓▓▓▓▓  ░░▓▓▓▓▓▓▓▓ ▓▓▓▓▓▓▓▓ ░░▓▓▓▓▓▓▓▓ ░░▓▓▓▓▓▓▓▓
 ░░░░░░    ░░░░░░░░ ░░░░░░░░   ░░░░░░░░   ░░░░░░░░ 

$(WHITE)
$(END)
endef
export CUB3D

.SILENT:

all:				$(LIBFT) $(MLX) $(NAME)

$(NAME):			$(OBJECTS)
					@$(CC) $(CC_FLAGS) $(OBJECTS) $(LIBFT) $(MLX) -o $(NAME) $(MLX_FLAGS)

$(OBJ_DIR)%.o:		$(SRC_PATH)%.c | $(OBJ_DIR)
					@mkdir -p $(dir $@)
					@$(CC) $(CC_FLAGS) -c -o $@ $<

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

$(LIBFT):
					@make --no-print-directory -C $(LIBFT_PATH)

$(MLX):				
					@make --no-print-directory -s -C $(MLX_PATH) > /dev/null 2>&1
					@echo "$(WHITE) · Mlx compilation complete.\n"
					@echo "\n··············· Compilation complete ···············"
					@echo "$$CUB3D"

clean:
					@rm -f $(OBJ)
					@rm -rf .objects/
					@rm -rf $(SRC_PATH)*.o
					@rm -rf $(ZoneIdentifiers)
					@make clean --no-print-directory -s -C $(MLX_PATH) > /dev/null
					@make clean --no-print-directory -C $(LIBFT_PATH)
					@echo "$(WHITE) · Mlx cleaned.$(WHITE)"
					@echo "$(WHITE) · $(BLUE)Cub3d objects removed.$(WHITE)\n"
					
fclean:				clean
					@rm -rf $(NAME)
					@rm -rf $(LIBFT)
					@make fclean --no-print-directory -C $(LIBFT_PATH)
					@echo "$(WHITE) · $(BLUE)Cub3d executable removed.$(WHITE)\n"

re:					fclean all

.PHONY:				all clean fclean re
