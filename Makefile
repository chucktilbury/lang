
TARGET	=	lang
OBJS	=	parser.o \
			scanner.o \
			main.o \
			mem.o \
			str.o \
			ast.o

CARGS	=	-g -Wall -Wextra -Wpedantic
EXT	=	-Wno-unused-variable -Wno-sign-compare

all: $(TARGET)

%.o:%.c
	gcc $(CARGS) -c -o $@ $<

$(TARGET): $(OBJS)
	gcc $(CARGS) -o $(TARGET) $(OBJS)

parser.c parser.h: parser.y
	bison -tvdo parser.c parser.y

scanner.c: scanner.l
	flex -io scanner.c scanner.l

scanner.o: scanner.c parser.h
	gcc $(CARGS) $(EXT) -c -o $@ $<

ast_types.h: parser.c
	python3 gen_ast.py

ast.o: ast.c ast_types.h
parser.o: parser.c
main.o: main.c parser.h
mem.o: mem.c mem.h
str.o: str.c str.h

clean:
	rm -f $(TARGET) $(OBJS) \
			parser.c parser.h parser.output \
			scanner.c ast_types.h ast_data.h \
			nterms.txt
