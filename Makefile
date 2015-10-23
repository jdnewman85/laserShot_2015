
CC = gcc
CFLAGS = -Wall -fgnu89-inline -g -pg
#CFLAGS+=-DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -Wall -g -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi -fgnu89-inline -Wall
LDFLAGS += -L$(SDKSTAGE)/opt/vc/lib/ -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -lm -L../libs/ilclient -L../libs/vgfont

INCLUDES += -I$(SDKSTAGE)/opt/vc/include/ -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux -I./ -I../libs/ilclient -I../libs/vgfont

SRC = $(wildcard '*.c') #BUG WTF DOESN'T THIS WORK?
SRC = piGL.c openglMisc.c lib/lodepng.c

BIN = a.out

all: $(SRC)
	$(CC) -o $(BIN) $^ $(CFLAGS) $(INCLUDES) $(LDFLAGS)

clean:
	rm *.o $(BIN)

