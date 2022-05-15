all: compile execute

compile: 
	g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system	

execute:
	./a.out