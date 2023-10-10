
TARGET	=	lang
OBJS	=	parser.o \
			scanner.o \
			main.o \
			ast.o

include ../common.make

all: $(TARGET)

%.o:%.c
	gcc $(BOPTS) -c -o $@ $<

$(TARGET): $(OBJS)
	gcc $(LOPTS) -o $(TARGET) $(OBJS) $(LIBS)

parser.c parser.h: parser.y ast.h ast.c
	bison -tvdo parser.c parser.y

scanner.c: scanner.l
	flex -io scanner.c scanner.l

scanner.o: scanner.c parser.h
	gcc $(BOPTS) $(WARNS) -c -o $@ $<

ast.c: gen_ast.py
	python gen_ast.py

ast.o: ast.c ast.h
parser.o: parser.c
main.o: main.c parser.h

clean:
	rm -f $(TARGET) $(OBJS) parser.c parser.h parser.output scanner.c *.bak

format: clean
	clang-format -i *.c *.h