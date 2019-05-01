DROPPED_SRC_NAME = main.c \
			service.c \
			network.c

SRC_NAME = dropper.c

OBJ_PATH = ./obj/

INC_PATH = ./includes ./libsrcs/libft/includes/

SRC_PATH = ./srcs/

DROPPED_NAME = Durex_dropped
NAME = dropper

CC = gcc
CFLAGS =  -Wextra -Wall -g
# CFLAGS =  -Wextra -Wall -Werror -g
LFLAGS = -lcurl
DROPPED_LFLAGS = -lmd5 -lft -lm

LIB_DIR=./lib/

DROPPED_OBJ_NAME = $(DROPPED_SRC_NAME:.c=.o)
DROPPED_SRC = $(addprefix $(SRC_PATH),$(DROPPED_SRC_NAME))
DROPPED_OBJ = $(addprefix $(OBJ_PATH),$(DROPPED_OBJ_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))


INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

dropped: $(DROPPED_NAME)

$(DROPPED_NAME) : $(DROPPED_OBJ) $(LIB_DIR) rm
	make -C libsrcs/libft -j8
	make -C libsrcs/md5
	gcc $(CFLAGS) $(INC) $(DROPPED_OBJ) -L $(LIB_DIR) $(DROPPED_LFLAGS) -o $(DROPPED_NAME)

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(NAME): $(OBJ)
	gcc $(CFLAGS) $(INC) $(OBJ) -L $(LIB_DIR) $(LFLAGS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@make -C libsrcs/libft clean
	@make -C libsrcs/md5 clean

fclean:
	make clean
	@rm -fv $(NAME)
	@make -C libsrcs/libft fclean
	@make -C libsrcs/md5 fclean
	@rmdir lib 2> /dev/null || true
	@rm -fv $(DROPPED_NAME)

re:
	make fclean
	make all

rm:
	rm -f /bin/Durex
	rm -f /etc/init.d/Durex
	killall Durex 2>&- >&- || true
	killall Durex_dropped 2>&- >&- || true
	killall dropper 2>&- >&- || true

.PHONY : all clean fclean re
