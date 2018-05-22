CC= gcc -Wall

compil:
	gcc -Wall Main.c serpent.c plateau.c affichage.c -o snake -lGLU -lglut -lGL -lm
apple :
	gcc -Wall  Main.c serpent.c plateau.c affichage.c -o snake -framework GLUT -framework OpenGL -Wno-deprecated
clean:
	rm snake
