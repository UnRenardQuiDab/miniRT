# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 18:00:16 by bwisniew          #+#    #+#              #
#    Updated: 2024/05/08 22:45:29 by lcottet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -g3 -Wall -Wextra -Werror -MMD -MP

SRCS_DIR = srcs

SRCS = main.c error.c

ENGINE_SRCS = mlx.c ray.c

OBJECTS_SRCS =	camera.c ambient.c cylinder.c light.c plane.c sphere.c

DISPLAY_SRCS =	render.c

VEC_SRCS =	dot.c add.c product.c multiply.c substract.c normalize.c reflect.c color.c

FILE_SRCS = parsing.c init.c conversion.c range.c

SRCS += $(ENGINE_SRCS:%.c=engine/%.c) $(DISPLAY_SRCS:%.c=display/%.c)  $(FILE_SRCS:%.c=file/%.c) $(OBJECTS_SRCS:%.c=objects/%.c) $(VEC_SRCS:%.c=vec/%.c)

OUTDIR = obj

OBJ = $(SRCS:%.c=$(OUTDIR)/%.o)

DEP = $(OBJ:%.o=%.d)

LIBS_DIR = libs

NAME = miniRT

LIBFT = $(LIBS_DIR)/libft/libft.a

VECTOR = $(LIBS_DIR)/vector_c/libvct.a

GRAPHIC_FLAGS = -lm -lXext -lX11

MINILIBX_FOLDER = $(LIBS_DIR)/minilibx/

INCLUDE = includes $(MINILIBX_FOLDER) $(LIBS_DIR)/libft/includes $(LIBS_DIR)/vector_c/includes

OS	= $(shell uname -s)

ifeq ($(OS), Linux)
	MINILIBX_FOLDER = $(LIBS_DIR)/minilibx/minilibx-linux
endif
ifeq ($(OS), Darwin)
	MINILIBX_FOLDER		=	$(LIBS_DIR)/minilibx/minilibx_opengl/
endif

MINILIBX = $(MINILIBX_FOLDER)/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(VECTOR) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(VECTOR) $(MINILIBX) $(GRAPHIC_FLAGS)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.c $(LIBFT) $(VECTOR) $(MINILIBX)
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) $(INCLUDE:%=-I %) -o $@ -c $<

$(LIBFT): FORCE
	make -C $(LIBS_DIR)/libft

$(MINILIBX): FORCE
	make -C $(MINILIBX_FOLDER)

$(VECTOR): FORCE
	make -C $(LIBS_DIR)/vector_c

run: $(NAME)
	./$(NAME) scenes/basic.rt
	
valgrind: $(NAME)
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./$(NAME)

clean:
	rm -rf $(OUTDIR)
	make -C $(LIBS_DIR)/libft clean
	make -C $(LIBS_DIR)/vector_c clean
	make -C $(MINILIBX_FOLDER) clean

fclean: clean
	rm -f $(NAME) $(LIBFT) $(VECTOR) $(MINILIBX)

re: fclean $(NAME)

norm:
	norminette $(LIBS_DIR)/libft $(LIBS_DIR)/vector_c includes $(SRCS_DIR)

FORCE:

-include $(DEP)

.PHONY: all clean fclean re norm FORCE valgrind run