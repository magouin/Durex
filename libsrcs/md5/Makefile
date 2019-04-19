SRC_NAME = main.c \
		md5_main.c \
		md5_parsing.c \
		md5_parsing_2.c \
		md5_stages.c \
		md5_fghi.c \
		md5_init.c \
		general_operations.c \
		bitwise_operations.c

OBJ_PATH = ./obj/

INC_PATH = ./includes ../libft/includes

SRC_PATH = ./srcs/

NAME = ../../lib/libmd5.a

CC = gcc
CFLAGS =  -Wextra -Wall -g
# CFLAGS =  -Wextra -Wall -Werror -g
LFLAGS = -lft
LIB_DIR=./lib/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix -I,$(INC_PATH))

all : LIB_RULE $(NAME)

LIB_RULE:
	@mkdir -p $(LIB_DIR)

$(NAME): $(OBJ)
	ar r $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NAME)
	@rmdir lib 2> /dev/null || true

re: fclean all

.PHONY : all clean fclean re
