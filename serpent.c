#include "serpent.h"
void dessine_snake(boule* serpent,int taille){
  GLUquadric* boule =gluNewQuadric();
  glPushMatrix();
  for(int i=0;i<taille;i++){
   glLoadIdentity();
    gluPerspective(70,(double)740/480,1,1000);
   	 	gluLookAt(snake[0].x,snake[0].y-4,snake[0].z+3,snake[0].direction.x+snake[0].x,snake[0].direction.y+snake[0].y,snake[0].direction.z+snake[0].z,0,0,1);
    glTranslatef(serpent[i].x,serpent[i].y,serpent[i].z);
    glColor3ub(255,255-(6*snake[0].compteur_colli),255-(6*snake[0].compteur_colli));
    if(i==0){
      gluSphere(boule,.5,30,30);
      
    }else
      gluSphere(boule,.4,30,30);
  }
 for(int i=0;i<TAILLE_MAX;i++){
if(snake[i].tir==1){
 glLoadIdentity();
    gluPerspective(70,(double)740/480,1,1000);
   	 	gluLookAt(snake[0].x,snake[0].y-4,snake[0].z+3,snake[0].direction.x+snake[0].x,snake[0].direction.y+snake[0].y,snake[0].direction.z+snake[0].z,0,0,1);
    glTranslatef(serpent[i].x,serpent[i].y,serpent[i].z);
    glColor3ub(0,255,255);
      gluSphere(boule,.4,30,30);
}
  }
glPopMatrix();
  glFlush();

}

boule* init_serpent(boule* serpent){
  float y=5;
  for(int i=0;i<TAILLE_MAX;i++){
      serpent[i].atourner=0;
serpent[i].tir=0;
    serpent[i].x=10.25;
    serpent[i].y=y;
    serpent[i].z=1.5;
    for(int j=0;j<TAILLE_MAX;j++){
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


