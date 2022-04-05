.PONY: build run

CC=g++
CPP_OUT=client
CPP_SRC=*.cpp
CPP_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
# -Wall -O2

build:
		@$(CC) -o $(CPP_OUT) $(CPP_SRC) $(CPP_FLAGS)

run:
		@./$(CPP_OUT)

clean:
		@rm $(CPP_OUT)
