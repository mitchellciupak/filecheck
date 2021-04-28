OPENCV=0
OPENMP=0
DEBUG=0

OBJ=main.o test.o args.o utils.o shared.o modules/perm.o modules/info.o modules/link.o modules/cycle.o

VPATH=./src/:./
EXEC=filecheck
SLIB=lib${EXEC}.so
ALIB=lib${EXEC}.a
OBJDIR=./obj/

CC=gcc
AR=ar
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread
COMMON= -Iinclude/ -Isrc/
CFLAGS=-Wall -g -Wno-unknown-pragmas -Wfatal-errors -fPIC

ifeq ($(OPENMP), 1)
CFLAGS+= -fopenmp
endif

ifeq ($(DEBUG), 1)
OPTS=-O0 -g
COMMON= -Iinclude/ -Isrc/
endif

CFLAGS+=$(OPTS)

OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile
MOD_DEPS = $(wildcard src/modules/*.h) Makefile

all: obj $(SLIB) $(ALIB) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(ALIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SLIB): $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.c $(DEPS) $(MOD_DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(OBJS) $(SLIB) $(ALIB) $(EXEC) $(OBJDIR)/*
	mkdir obj/modules
