ifeq ($(MAKELEVEL),0)
.PHONY: all
all:
	$(MAKE) 3rdparty -C ..
else

SHELL = /bin/bash

other_targets = x264 faac ffmpeg

.PHONY: all

all: $(other_targets)


ffmpeg: x264 faac

.SECONDEXPANSION:

$(other_targets): $$(wildcard distfiles/$$@*) $$(wildcard patchsets/[0-9][0-9]-$$@*.patch) \
            $$(wildcard patchsets/$$@*.patch) $$(wildcard specs/$$@.spec)
	@set -e; source package_util.sh; __extract $@; __prepare $@; $(MAKE); $(MAKE) install
	touch $@

endif
