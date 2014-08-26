
INSTALLDIR = /home/tvie/work/xspeed/_release

CPPFLAGS = -I. -I$(INSTALLDIR)/include 
####CFLAGS += -Wall -Werror -std=c99
CFLAGS += -Wall -std=c99
LDFLAGS += -lpthread -ldl -lrt

#Source := $(wildcard *.c)
Source := xspeed.c 
OBJECTS := $(patsubst %.c, %.o, $(Source))

BUILD_ARCH = $(shell uname -m)

.PHONY: all

all: xspeed 
	mkdir -p $(INSTALLDIR)/bin
	install -m 755 xspeed $(INSTALLDIR)/bin/xspeed


xspeed: $(OBJECTS) $(INSTALLDIR)/lib/libavformat.a $(INSTALLDIR)/lib/libavcodec.a \
$(INSTALLDIR)/lib/libavutil.a $(INSTALLDIR)/lib/libswscale.a $(INSTALLDIR)/lib/libswresample.a
	$(CC) $^ -o $@  -lm -lz -lbz2  $(CPPFLAGS) $(LDFLAGS) $(LINKFLAGS)

clean:
	rm -rf *.o xspeed
