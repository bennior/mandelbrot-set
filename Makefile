CXX	:=	gcc
OPT	:=	-O3	-ffast-math

LIB	:=	-lSDL3
BIN	:=	mandelbrot

all: $(BIN)

run: clean all
	clear
	./$(BIN)

$(BIN): *.c
	$(CXX) $(OPT) *.c -o $@ $(LIB)

clean:
	-rm $(BIN)
