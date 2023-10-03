make_dirs := $(shell mkdir -p bin)

TARGET	=	bin/lang
UTIL	=	util/libutil.a

DEBUG	=	-g
EXT		=	-Wno-unused-variable -Wno-sign-compare
CONFIG	=	-DENA_TRACE -DUSE_GC -lgc
LIBDIRS	=	-L.
LIBS	=	-lutil -lgc
CARGS	=	$(CONFIG) -Wall -Wextra -Wpedantic

all: $(TARGET)
$(TARGET): $(UTIL) $(GC)
	make -C src && cp src/lang bin
$(UTIL):
	make -C util

clean:
	rm -rf bin
	make -C util clean
	make -C src clean
