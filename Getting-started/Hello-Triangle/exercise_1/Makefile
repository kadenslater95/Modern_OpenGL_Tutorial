
template: template.cpp libshader.a
	g++ -Wall -o template template.cpp -L. -l:libshader.a -lGLEW -lGLU -lGL -lglfw

libshader.a: shader.cpp shader.h
	g++ -Wall -c -o shader.o shader.cpp
	ar rcs libshader.a shader.o
	rm shader.o
