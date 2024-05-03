# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 18:00:16 by bwisniew          #+#    #+#              #
#    Updated: 2024/05/03 18:20:19 by lcottet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -g3 -Wall -Wextra -Werror -MMD -MP

SRCS_DIR = srcs

SRCS = main.c

ENGINE_SRCS = 

DISPLAY_SRCS =	

FILE_SRCS =

SRCS += $(ENGINE_SRCS:%.c=engine/%.c) $(DISPLAY_SRCS:%.c=display/%.c)  $(FILE_SRCS:%.c=file/%.c)

OUTDIR = obj

OBJ = $(SRCS:%.c=$(OUTDIR)/%.o)

DEP = $(OBJ:%.o=%.d)

LIBS_DIR = libs

INCLUDE = includes $(LIBS_DIR)/libft/includes $(LIBS_DIR)/vector_c/includes

NAME = miniRT

LIBFT = $(LIBS_DIR)/libft/libft.a

VECTOR = $(LIBS_DIR)/vector_c/libvct.a

GRAPHIC_FLAGS = -lm -lXext -lX11

MINILIBX_FOLDER = $(LIBS_DIR)/minilibx/

OS	= $(shell uname -s)

ifeq ($(OS), Linux)
	MINILIBX_FOLDER = $(LIBS_DIR)/minilibx/minilibx-linux
endif
ifeq ($(OS), Darwin)
	MINILIBX_PATH		=	lib/minilibx_opengl/
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
	./$(NAME)
	
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