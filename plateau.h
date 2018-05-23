#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include "GL/gl.h"
#include "GL/glut.h"
#endif

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "serpent.h"

typedef struct block{
  int hauteur;
  int bonus;
  float obstacle;
  float compteur;
  float rebond;
}block;

int longueur;
int largeur;

typedef struct planete{
  vecteur direction;
  float x;
  float y;
  float z;
  float taille;
  int anneau;
  float r;
  float g;
  float b;
}planete;


block blocs[1000][100];
planete decor[100];

void init_decor();
void dessinBlock(block precedent, block suivant, int pos_largeur,int pos_longueur,int bordure);
void init_plateau();
void dessinPlannete();
