
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

TARGET = piGL.out
SOURCES = $(shell echo src/*.c) $(shell echo lib/*.c)
COMMON = #Usefull if I make a common head or something
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(LIBS)

release: $(SOURCES) $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS) $(LIBS) $(INCDIRS)

profile: CFLAGS += -pg
profile: $(TARGET)

clean:
	-rm -f $(OBJECTS)
	-rm -f gmon.out

distclean: clean
	-rm -f $(TARGET)

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

