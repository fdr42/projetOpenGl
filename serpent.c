#include "plateau.h"
void dessine_snake(boule* serpent){
  GLUquadric* boule =gluNewQuadric();
//Inutile de tout afficher en jeu (optimsation)
int visible=20;
if(rotation || taille<20)
	visible=taille;

if(rotation || taille>70)
	visible=70;

  for(int i=0;i<visible;i++){
    glPushMatrix();   	 	
    glTranslatef(serpent[i].x,serpent[i].y,serpent[i].z);
    glColor3ub(decor[i].r+(serpent[0].compteur_colli*3),decor[i].g-(serpent[0].compteur_colli*3),decor[i].b-(serpent[0].compteur_colli*3));
    if(i==0){
      gluSphere(boule,.5,30,30);
      glPopMatrix();
    }else
      gluSphere(boule,.4,30,30);
    glPopMatrix();
  }
  for(int i=0;i<TAILLE_MAX;i++){
    glPushMatrix();
    if(snake[i].tir==1){
      glTranslatef(serpent[i].x,serpent[i].y,serpent[i].z);
      glColor3ub(rand()%255,rand()%255,rand()%255);
      gluSphere(boule,.4,30,30);
    }
    glPopMatrix();
  }
  glPopMatrix();
}

boule* init_serpent(boule* serpent){
  float y=5;
  int i,j;
  for(i=0;i<TAILLE_MAX;i++){
    serpent[i].atourner=0;
    serpent[i].tir=0;
    serpent[i].x=10.25;
    serpent[i].y=y;
    serpent[i].z=1.5;
    for(j=0;j<TAILLE_MAX;j++){
      serpent[i].tab_tour[j].pos_y=0;
      serpent[i].tab_tour[j].pos_x=0;
      serpent[i].tab_tour[j].compteur=-1;
      serpent[i].nb_tour=0;
    }
    y-=.5;
    if(i==0)
      y-=.2;
    serpent[i].direction.x=0;
    serpent[i].direction.y=vitesse;
    serpent[i].direction.z=0;
    serpent[i].block_y=0;
    serpent[i].block_x=0;
    serpent[i].compteur_colli=0;
  }
  return serpent;
}


