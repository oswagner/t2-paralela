CC      =   	mpicc
BIN     =   	soma-interios
SRCS	=	soma-interios.c utils.c
OBJDIR 	=	obj

CFLAGS  = -Wall
CFLAGS  += -Wmissing-declarations -Wuninitialized -Wtype-limits
CFLAGS  += -Wshadow -Wpointer-arith -Wcomment
CFLAGS  += -Wsign-compare -Wstrict-overflow=5
CFLAGS  += -Wwrite-strings -Wdeprecated -Wmissing-field-initializers
CFLAGS  += -g
CFLAGS  += -Wcast-qual -Wsign-conversion

CGCCFLAGS = -Wunsafe-loop-optimizations -Wlogical-op -Wclobbered
 
DFLAGS = -D_FORTIFY_SOURCE=2

PGFLAGS = -pg

LINKERFLAGS =

.PHONY: clean all

all: $(SRCS) $(BIN)

$(BIN):
	$(CC) $(CFLAGS) $(CGCCFLAGS) $(CGCCADDFLAGS) $(IFLAGS) $(DFLAGS) \
	$(LDFLAGS) -O1 $(SRCS) -o $@ $(LINKERFLAGS)
	
clean:
	rm -f $(BIN) $(BIN2) $(BIN3)
