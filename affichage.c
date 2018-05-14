#include "affichage.h"


void Affichage(){
   
   


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);

  gluLookAt(snake[0].x,snake[0].y-4,snake[0].z+3,snake[0].direction.x*5+snake[0].x,snake[0].direction.y*5+snake[0].y,snake[0].direction.z*5+snake[0].z,0,0,1);
/************dessin des blocs**********/
  for(int j=0;j<longueur-1;j++)
    dessinBlock(blocs[0][j],blocs[0][j+1],0,j*6,1);
    
  for(int j=0;j<longueur-1;j++)
    for(int i=1;i<largeur-1;i++)
      dessinBlock(blocs[i][j],blocs[i][j+1],i*2,j*6,0);
    
  for(int j=0;j<longueur-1;j++)
    dessinBlock(blocs[largeur-1][j],blocs[largeur-1][j+1],2*(largeur-1),j*6,1);

   /************ fin dessin des blocs**********/

  dessine_snake(snake,taille);

  glLineWidth(2.5);
    
    
  glBegin(GL_LINES);
  glColor3ub(255,150,0); 
  glVertex3d(0, 0, 0);
  glVertex3d(0, 100,0);
    
  glColor3ub(0,255,150); 
  glVertex3d(0, 0, 0);
  glVertex3d(100, 0,0);
    
  glColor3ub(0,0,255);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0,100);
  glEnd();
 glPushMatrix();
glOrtho(0, 800, 600, 0, -1, 1);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

int x=taille;
int chiffres[3];
int a=0;
 while (x != 0)
    {
      chiffres[++a] = x % 10;
      x /= 10;
    }
glRasterPos2f(0.7, 0.7);
	glColor3f (1,1,1);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0'+chiffres[a]);
        
glPopMatrix();
  glFlush();


   

}
