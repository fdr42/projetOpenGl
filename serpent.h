#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include "GL/gl.h"
#include "GL/glut.h"
#endif

#include<stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define TAILLE_MAX 150

typedef struct vecteur{
    float x;
    float y;
    float z;
}vecteur;
typedef struct animation{
float pos_x;
float pos_y;
float compteur;
}animation;

typedef struct boule{
    vecteur direction;
int tir;
    float x;
    float y;
    float z;
    int block_y;
int compteur_colli;
int block_x;
    int nb_tour;
    animation tab_tour[3000];
    int atourner;
}boule;

boule snake[TAILLE_MAX+1];
float incr;
int score;
float prochaine_pente;
float pente_actuelle;
float vitesse;
int tourne;
int taille;

int rotation;
int taille_tir;
void dessine_snake(boule* serpent,int taille);
boule* init_serpent(boule* serpent);
void point_vue();
