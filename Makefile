NAME		=	ft_ls

SRC			=	parse_input.c
TEST		=	test_parse.c

SRC_OBJ		=	$(SRC:.c, .o)
TEST_OBJ	=	$(TEST:.c, .o)

CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra
DEBUG_FLAGS	=	-fsanitize=address
INC			=	-I . -I libft/includes/
LIB			=	-Llibft/ -lft


all: obj
	$(CC) $(FLAGS) $(INC) -o $(NAME) $(SRC_OBJ) $(TEST_OBJ)

obj:
	$(CC) $(FLAGS) $(INC) -c $(SRC) $(TEST)

test_format:
	make -C libft/
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -g $(INC) $(LIB) format_output.c test_format.c
	
clean:
	rm -f $(SRC_OBJ)
	rm -f $(TEST_OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
