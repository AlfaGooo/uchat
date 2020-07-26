CLIENT_NAME = uchat_client
SERVER_NAME = uchat_server

LIBS = libmx.a cJSON.a sqlite3.a
LIBS_INCS = libmx.h cJSON.h sqlite3.h
LIBS_INC = libmx/inc/libmx.h cJSON/inc/cJSON.h sqlite3/inc/sqlite3.h

CFLAG = -std=c11 -Wall -Wextra -Werror -Wpedantic -lsocket -lnsl
OPENSSL = -I./openssl/include -L./openssl/lib -lssl -lcrypto

OBJ_DIR = obj

CLIENT_INC = inc/uchat.h

SERVER_INC = inc/uchat.h

CLIENT_INCS = uchat.h

SERVER_INCS = uchat.h

CLIENT_SRC = 

SERVER_SRC = src/database/*.c

CLIENT_SRCS = client.c

SERVER_SRCS = server.c

CLIENT_OBJ = obj/client.o

SERVER_OBJ = obj/server.o

CLIENT_OBJS = client.o

SERVER_OBJS = server.o

all: lib_install client_install server_install lib_uninstall client_uninstall server_uninstall

client: client_install client_uninstall

server: server_install server_uninstall

lib: lib_install
	@make -C libmx uninstall
	@make -C cJSON uninstall
	@make -C sqlite3 uninstall

lib_install:
	@cp $(LIBS_INC) .
	@make -C libmx install
	@make -C cJSON install
	@make -C sqlite3 install
	@cp libmx/libmx.a .
	@cp cJSON/cJSON.a .
	@cp sqlite3/sqlite3.a .

client_install:
	@cp $(CLIENT_INC) .
	@cp $(CLIENT_SRC) .
	@clang -o $(CLIENT_NAME) $(CLIENT_SRCS) -I $(CLIENT_INCS) $(LIBS)

server_install:
	@cp $(SERVER_INC) .
	@cp $(SERVER_SRC) .
	@clang -o $(SERVER_NAME) $(SERVER_SRCS) -lpthread -I $(SERVER_INCS) $(LIBS)

install: lib_install client_install server_install

client_uninstall:
	@rm -rf $(CLIENT_SRCS)
	@rm -rf $(CLIENT_INCS)

server_uninstall:
	@rm -rf $(SERVER_SRCS)
	@rm -rf $(SERVER_INCS)

lib_uninstall:
	@make -C libmx uninstall
	@make -C cJSON uninstall
	@make -C sqlite3 uninstall
	@rm -rf $(LIBS) $(LIBS_INCS)

uninstall: client_uninstall server_uninstall lib_uninstall

lib_clean: lib_uninstall
	@rm -rf $(LIBS)
	@rm -rf $(LIBS_INCS)
	@make -C libmx clean
	@make -C cJSON clean
	@make -C sqlite3 clean

client_clean: client_uninstall
	@rm -rf $(CLIENT_OBJ)
	@rm -rf $(CLIENT_NAME)

server_clean: server_uninstall
	@rm -rf $(SERVER_OBJ)
	@rm -rf $(SERVER_NAME)

clean: lib_clean client_clean server_clean
	@rm -rf $(OBJ_DIR)

lib_reinstall: lib_uninstall lib_install

client_reinstall: client_uninstall client_install

server_reinstall: server_uninstall server_install

reinstall: lib_reinstall client_reinstall server_reinstall

#	@clang $(CFLAG) -o $(CLIENT_NAME) -c $(CLIENT_SRCS) -I $(CLIENT_INCS) $(LIBS)
#	@clang $(CFLAG) -o $(SERVER_NAME) -c $(SERVER_SRCS) -I $(CLIENT_INCS) $(LIBS)