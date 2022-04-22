.PONY: build run

CC=g++
CPP_OUT=main
CPP_SRC=*.cpp
CPP_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lpthread

build:
		@$(CC) -o $(CPP_OUT) $(CPP_SRC) $(CPP_FLAGS)

run:
		@./$(CPP_OUT)

clean:
		@rm $(CPP_OUT)