NAME = cJSON.a

CFLAG = -std=c11 -Wall -Wextra -Werror -Wpedantic

INC = inc/cJSON.h

INCS = cJSON.h

SRC =  src/CJSON.c

SRCS = cJSON.c

OBJ_DIR = obj

OBJ =  obj/cJSON.o

OBJS = cJSON.o

all: install uninstall
install:
	@mkdir -p $(OBJ_DIR)
	@cp $(SRC) .
	@cp $(INC) .
	@clang $(CFLAG) -c $(SRCS) -I $(INCS)
	@cp $(OBJS) $(OBJ_DIR)
	@rm -rf $(OBJS)
	@ar -cq $(NAME) $(OBJ)
uninstall:
	@rm -rf $(SRCS)
	@rm -rf $(INCS)
	@rm -rf $(OBJ_DIR)
clean: uninstall
	@rm -rf $(NAME)
reinstall: uninstall install
