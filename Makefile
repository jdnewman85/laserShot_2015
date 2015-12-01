
#SDKSTAGE needs to be added around more to make cross compile work
SHELL = /bin/sh
CC = gcc

FLAGS = -fgnu89-inline #-std=gnu99 
CFLAGS = -Wall -Wextra
DEBUGFLAGS = -O0 -D _DEBUG -ggdb3
RELEASEFLAGS = -O2 -D NDEBUG #-combine -fwhole-program
LDFLAGS += -L$(SDKSTAGE)/opt/vc/lib/
LIBS += -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -lm -lkazmath

INCDIRS += -I$(SDKSTAGE)/opt/vc/include/ -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux -I./include

TARGET = piGL
SOURCES = $(shell echo src/*.c) $(shell echo lib/*.c)
COMMON = #Usefull if I make a common head or something
HEADERS = $(shell echo include/*.h)
BUILD_DIR = build
OBJECTS = $(addprefix ${BUILD_DIR}/,$(patsubst %.c,%.o,$(SOURCES)))
TESTBENCH = $(shell echo testbench/*.c)
LIBTARGET = lib$(TARGET).a

GO_C = go
CGO_FLAGS = $(FLAGS) $(INCDIRS)
CGO_LDFLAGS = $(LDFLAGS) $(LIBS)
GO_LDFLAGS = -linkmode external -extldflags -static
GO_TARGET = piGL
GO_SOURCES = $(shell echo src/*.go)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET).out $(OBJECTS) $(TESTBENCH) $(LDFLAGS) $(LIBS) $(INCDIRS)

release: $(SOURCES) $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) -o $(TARGET).out $(SOURCES) $(TESTBENCH) $(LDFLAGS) $(LIBS) $(INCDIRS)

static: $(OBJECTS)
	ar -rcs $(LIBTARGET) $(OBJECTS)

go-static: $(GO_SOURCES) static
	CGO_CFLAGS="$(CGO_FLAGS)" CGO_LDFLAGS="$(CGO_LDFLAGS)" $(GO_C) build -o $(GO_TARGET) -ldflags "$(GO_LDFLAGS) $(CGO_LDFLAGS)" $(GO_SOURCES)

profile: CFLAGS += -pg
profile: $(TARGET)

clean:
	-rm -rf $(BUILD_DIR)
	-rm -f gmon.out

distclean: clean
	-rm -f $(TARGET).out
	-rm -f $(LIBTARGET)

#If not using GNU make or to be safe
$(BUILD_DIR)/%.o: %.c $(HEADERS) $(COMMON)
	@mkdir -p `dirname $@`
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $< $(INCDIRS)

.PHONY : all profile release clean distclean \
	install install-strip uninstall

