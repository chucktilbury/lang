
TARGET	=	lang
OBJS	=	parser.o \
			scanner.o \
			main.o \
			ast.o

EXT		=	-Wno-unused-variable -Wno-sign-compare
LIBS	=	-lutil -lgc
LDIR	=	-L../util
IDIR	=	-I../util
DEBUG	=	-g -DENA_TRACE -DDEBUG_PARSER=1
CARGS	=	-Wall -Wextra -Wpedantic $(IDIR) $(DEBUG)

all: $(TARGET)

%.o:%.c
	gcc $(CARGS) -c -o $@ $<

$(TARGET): $(OBJS)
	gcc $(CARGS) $(LDIR) -o $(TARGET) $(OBJS) $(LIBS)

parser.c parser.h: parser.y ast.h ast.c
	bison -tvdo parser.c parser.y

scanner.c: scanner.l
	flex -io scanner.c scanner.l

scanner.o: scanner.c parser.h
	gcc $(CARGS) $(EXT) -c -o $@ $<

ast.c: gen_ast.py
	python gen_ast.py

ast.o: ast.c ast.h
parser.o: parser.c
main.o: main.c parser.h

clean:
	rm -f $(TARGET) $(OBJS) parser.c parser.h parser.output scanner.c *.bak
