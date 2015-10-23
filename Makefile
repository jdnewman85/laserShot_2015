
#SDKSTAGE needs to be added around more to make cross compile work
SHELL = /bin/sh
CC = gcc

FLAGS = -fgnu89-inline #-std=gnu99 
CFLAGS = -Wall -Wextra
DEBUGFLAGS = -O0 -D _DEBUG -ggdb3
RELEASEFLAGS = -O2 -D NDEBUG #-combine -fwhole-program
LDFLAGS += -L$(SDKSTAGE)/opt/vc/lib/
LIBS += -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -lm 

INCDIRS += -I$(SDKSTAGE)/opt/vc/include/ -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux -I./include

TARGET = piGL
SOURCES = $(shell echo src/*.c) $(shell echo lib/*.c)
COMMON = #Usefull if I make a common head or something
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.c=.o)
TESTBENCH = $(shell echo testbench/*.c)

GO_C = go
GO_CFLAGS =
GO_LDFLAGS = -linkmode external -extldflags -static
GO_LIBTARGET = lib$(TARGET).a
GO_TARGET = piGL
GO_SOURCES = $(shell echo src/*.go)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS) $(TESTBENCH) $(LDFLAGS) $(LIBS) $(INCDIRS)

release: $(SOURCES) $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) -o $(TARGET) $(SOURCES) $(TESTBENCH) $(LDFLAGS) $(LIBS) $(INCDIRS)

static: $(OBJECTS) $(COMMON)
	ar -rcs $(GO_LIBTARGET) $(OBJECTS)
	$(GO_C) build -o $(GO_TARGET) -ldflags "$(GO_LDFLAGS)" $(GO_SOURCES)

profile: CFLAGS += -pg
profile: $(TARGET)

clean:
	-rm -f $(OBJECTS)
	-rm -f gmon.out

distclean: clean
	-rm -f $(TARGET)
	-rm -f $(GO_LIBTARGET)

#If not using GNU make or to be safe
%.o: %.c $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $< $(INCDIRS)

.PHONY : all profile release clean distclean \
	install install-strip uninstall








#Not using this yet

#PREFIX = $(DESTDIR)/usr/local
#BINDIR = $(PREFIX)/bin

#install: release
#	install -D $(TARGET) $(BINDIR)/$(TARGET)
#
#install-strip: release
#	install -D -s $(TARGET) $(BINDIR)/$(TARGET)
#
#uninstall:
#	-rm $(BINDIR)/$(TARGET)

#Doesn't work!!!
#Special GNU Make, check header files that matter
#.SECONDEXPANSION:
#
#$(foreach OBJ,$(OBJECTS),$(eval $(OBJ)_DEPS = $(shell gcc -MM $(OBJ:.o=.c) | sed s/.*://)))
#%.o: %.c $$($$@_DEPS)
#	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $< $(INCDIRS)

