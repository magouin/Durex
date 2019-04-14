SRC_NAME = main.c \
			service.c

OBJ_PATH = ./obj/

INC_PATH = ./includes ./libsrcs/libft/includes/

SRC_PATH = ./srcs/

NAME = Durex

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

all : $(LIB_DIR) $(NAME) rm

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(NAME): $(OBJ)
	make -C libsrcs/libft -j8
	gcc $(CFLAGS) $(INC) -L $(LIB_DIR) $(LFLAGS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true
	@make -C libsrcs/libft clean

fclean:
	make clean
	@rm -fv $(NAME)
	@make -C libsrcs/libft fclean
	@rmdir lib 2> /dev/null || true

re:
	make fclean
	make all

rm:
	rm -f /bin/Durex
	killall Durex 2>&- >&- || true

.PHONY : all clean fclean re
