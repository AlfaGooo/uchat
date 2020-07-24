NAME = sqlite3.a

CFLAG = -std=c11 -Wall -Wextra -Werror -Wpedantic

INC = inc/sqlite3.h

INCS = sqlite3.h

SRC =  src/sqlite3.c

SRCS = sqlite3.c

OBJ_DIR = obj

OBJ =  obj/sqlite3.o

OBJS = sqlite3.o

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