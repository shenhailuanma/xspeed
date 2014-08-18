
ifeq ($(MAKELEVEL),0)
.PHONY: all
all:
	$(MAKE) xspeed -C ..
clean:
	rm -rf *.o *.d xspeed
else

CPPFLAGS = -I. -I$(INSTALLDIR)/include 
####CFLAGS += -Wall -Werror -std=c99
CFLAGS += -Wall -std=c99
LDFLAGS += -lpthread -ldl -lrt

#Source := $(wildcard *.c)
Source := xspeed.c 
OBJECTS := $(patsubst %.c, %.o, $(Source))

BUILD_ARCH = $(shell uname -m)
ifneq ($(BUILD_ARCH),x86_64)
 CPPFLAGS += -DENABLE_TVIE_WIN32LOADER
endif

.PHONY: all

all: xspeed 
	mkdir -p $(INSTALLDIR)/bin
	install -m 755 xspeed $(INSTALLDIR)/bin/xspeed


xspeed: $(OBJECTS) $(INSTALLDIR)/lib/libavformat.a $(INSTALLDIR)/lib/libavcodec.a \
$(INSTALLDIR)/lib/libavutil.a $(INSTALLDIR)/lib/libswscale.a $(INSTALLDIR)/lib/libswresample.a 
	$(CC) $^ -o $@ -lasound -lm -lz -lbz2 -lssl -lcrypto $(CPPFLAGS) $(LDFLAGS) $(LINKFLAGS)

clean:
	rm -rf *.o xspeed
include ../autodepend.mak

endif
