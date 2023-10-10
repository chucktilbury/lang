
WARNS	=	-Wno-unused-variable -Wno-sign-compare
LIBS	=	-lutil -lgc
LDIR	=	-L../util
IDIR	=	-I../util
DEBUG	=	-g
CONFIG	=	-DENA_TRACE -DUSE_GC
CARGS	=	-Wall -Wextra -Wpedantic $(DEBUG) $(CONFIG)

BOPTS	=	$(CARGS) $(IDIR)
LOPTS	=	$(CARGS) $(LDIR)
