#include "affichage.h"
#include <string.h>
/**********Fonction de dessin de chaines de caracteres***********/
void drawBitmapText(char *string,float x,float y,float z) 
{  
//on pousse la matrice dans la pile pour ne pas perdre notre point de vue
glPushMatrix();
glOrtho(0, 800, 600, 0, -1, 1);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
	glRasterPos3f(x, y,z);
//on dessine chaque caractere
	for (int c=strlen(string); c >= 0; c--) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[c]);
	}
glPopMatrix();
//On remet la matrice precedente
}

void Affichage(){
   
   
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);
// ici on anticipe la prochaine pente pour que la camera commence son mouvement
if((pente_actuelle<prochaine_pente && pente_actuelle+incr>prochaine_pente) || (pente_actuelle>prochaine_pente && pente_actuelle+incr<prochaine_pente))
prochaine_pente=pente_actuelle;
else
pente_actuelle+=incr;

//Experimental
 gluLookAt(snake[0].x,snake[0].y-8+snake[0].compteur_colli/39,snake[0].z+5+pente_actuelle*2,snake[0].x,snake[0].y,1+snake[0].z+pente_actuelle*2,0,0,1);


//On dessine le score et le nombre de boules restantes
int x=taille;
char chiffres[10];
int a=0;
 while (x != 0)
    {

      chiffres[a] = '0'+x % 10;
a++;
      x /= 10;
    }
chiffres[a] = '\0';
        drawBitmapText(chiffres,0.8,0.8,0);

	a=0;
x=score; 
while (x != 0)
    {
      chiffres[a] = '0'+x % 10;
a++;
      x /= 10;
    }
chiffres[a] = '\0';
        drawBitmapText(chiffres,-0.8,0.8,0);
 
/************dessin des blocs**********/
  for(int j=0;j<longueur-1;j++)
    dessinBlock(blocs[0][j],blocs[0][j+1],0,j*6,1);
    
  for(int j=0;j<longueur-1;j++)
    for(int i=1;i<largeur-1;i++)
      dessinBlock(blocs[i][j],blocs[i][j+1],i*2,j*6,0);
    
  for(int j=0;j<longueur-1;j++)
    dessinBlock(blocs[largeur-1][j],blocs[largeur-1][j+1],2*(largeur-1),j*6,1);

  /************ fin dessin des blocs**********/
 /************dessin du serpent**********/
  dessine_snake(snake,taille);
 /************ fin dessin du serpent**********/


//dessin des axes(a supprimer)
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



  glFlush();


   

}
