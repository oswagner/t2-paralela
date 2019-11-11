CC      =   	mpicc
BIN     =   	hello
SRCS	=	hello.c utils.c
BIN2	=	int
SRCS2	=	int.c utils.c
BIN3	=	distsort
SRCS3	=	distsort.c utils.c
OBJDIR 	=	obj

CFLAGS  = -Wall
CFLAGS  += -Wmissing-declarations -Wuninitialized -Wtype-limits
CFLAGS  += -Wshadow -Wpointer-arith -Wcomment
CFLAGS  += -Wsign-compare -Wstrict-overflow=5
CFLAGS  += -Wwrite-strings -Wdeprecated -Wmissing-field-initializers
CFLAGS  += -g
CFLAGS  += -Wcast-qual -Wsign-conversion

CGCCFLAGS = -Wunsafe-loop-optimizations -Wlogical-op -Wclobbered
CGCCADDFLAGS = -Wstack-usage=512 -Wcast-align=strict
 
DFLAGS = -D_FORTIFY_SOURCE=2

PGFLAGS = -pg

LINKERFLAGS =

.PHONY: clean all

all: $(SRCS) $(BIN) $(SRCS2) $(BIN2) $(SRCS3) $(BIN3)

$(BIN):
	$(CC) $(CFLAGS) $(CGCCFLAGS) $(CGCCADDFLAGS) $(IFLAGS) $(DFLAGS) \
	$(LDFLAGS) -O1 $(SRCS) -o $@ $(LINKERFLAGS)

$(BIN2):
	$(CC) $(CFLAGS) $(CGCCFLAGS) $(CGCCADDFLAGS) $(IFLAGS) $(DFLAGS) \
	$(LDFLAGS) -O1 $(SRCS2) -o $@ $(LINKERFLAGS)

$(BIN3):
	$(CC) $(CFLAGS) $(CGCCFLAGS) $(CGCCADDFLAGS) $(IFLAGS) $(DFLAGS) \
	$(LDFLAGS) -O1 $(SRCS3) -o $@ $(LINKERFLAGS)
clean:
	rm -f $(BIN) $(BIN2) $(BIN3)
