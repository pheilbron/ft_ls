NAME		=	ft_ls

CC			=	gcc
LIB			= -L../libft -lft
INC_FLAGS	= -I inc -I ../libft/inc
FLAGS		=	-Wall -Werror -Wextra
DEBUG_FLAGS	=	-fsanitize=address

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= parse_input usage main
OBJ			= $(patsubst %, $(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) ../libft/libft.a
	@$(CC) $(CFLAGS) $(LIB) -o $@ $^

../libft/libft.a:
	@make -sC libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@echo Compiling $<.
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

debug: 
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(INC_FLAGS) src/*.c \
		src/*/*.c src/*/*/*.c \
		../libft/src/*/*.c ../libft/src/stdio/ft_printf/*.c \
		../libft/src/stdio/ft_printf/*/*.c

clean: clean_debug
	#make clean -C lib/
	rm -rf $(OBJ_DIR)

clean_debug:
	rm -f debug 
	rm -rf debug.dSYM 

fclean: clean clean_debug
	#make fclean -C lib/
	rm -f $(NAME)

re: fclean all
