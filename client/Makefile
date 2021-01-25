CLIENT = uchat

EMPTY = 
SPACE = $(EMPTY) $(EMPTY)
VPATH = VPATH = $(subst $(SPACE), :, $(SRCD))

OBJD = obj
INCD_LIBS = -I../libraries/include
LIBD_LIBS = -L../libraries/lib
INCD_CLIENT = -Iinc/
GTK_LIBS = -rdynamic `pkg-config --cflags --libs gtk+-3.0`
GTK_INC = `pkg-config --cflags gtk+-3.0`

SRCD = src src/main src/gui src/gui/authorization src/json_objects src/gui/contact src/gui/message
INCD = inc
SRCS = $(foreach dir, $(SRCD), $(wildcard $(dir)/*.c))
OBJS = $(addprefix $(OBJD)/, $(notdir $(SRCS:%.c=%.o)))
INCS = $(foreach dir, $(INCD), $(wildcard $(dir)/*.h))

OBJTEST = $(OBJS)

CC = clang

CFLAGS = -std=c11 $(addprefix -W, error no-deprecated all extra pedantic)
CPPFLAGS = -DMX_CLIENT='"$(CLIENT_WD)"' $(INCD_CLIENT) -D_GNU_SOURCE \
$(UTILS_INC) $(GTK_INC) $(INCD_LIBS) -I/usr/local/opt/openssl/include
LIBS = $(GTK_LIBS) $(LIBD_LIBS) -L/usr/local/opt/openssl/lib \
-lcjson -lsqlite3 -lpthread -rdynamic

all: $(CLIENT)

$(CLIENT): $(OBJS)
	@$(CC) -fsanitize=address -g -o $@ $^  $(LIBS)
	@printf "\033[32;1m$@ created\033[0m\n"

$(OBJS): obj/%.o: %.c $(INCS) | $(OBJD)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJD):
	@mkdir -p $@
	@printf "\033[32;1m$@ created\033[0m\n"

	

uninstall: clean
	@rm -rf $(CLIENT)
	@printf "\033[34;1mdeleted $(CLIENT)\033[0m\n"

clean:
	@rm -rf $(OBJD)
	@rm -rf $(CLIENT_WD)/files
	@printf "\033[34;1mdeleted $(OBJD)\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall