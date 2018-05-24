#include "affichage.h"
//#include "SDL/SDL.h"

#define nbpix_x 20
#define nbpix_y 20
#define nbpix_y 20

float angle = 0;


/****** FONCTION QUI PERMET DE REPRODUIRE LE MOUVEMENT FLUIDES DU SNAKE *****/
void tourner(int boule){
  //La fonction vas ajouter une valeur au vecteur direction en fonction du deplacement de la precedente
  //Pour la boule qui suit la premiere "<"
  if(boule==1){
    if(snake[boule-1].atourner<snake[boule-1].nb_tour){
      if(snake[boule-1].tab_tour[snake[boule-1].atourner].pos_x>0)
	snake[boule].direction.x+=0.25;
      else
	snake[boule].direction.x-=0.25;
      snake[boule-1].tab_tour[snake[boule-1].atourner].compteur=0;
      snake[boule-1].atourner++;
    }
    //Pour les autres "<="
  }else if(snake[boule-1].atourner<=snake[boule-1].nb_tour ){
    if(snake[boule-1].atourner!=0){
      if(snake[boule-1].tab_tour[snake[boule-1].atourner].pos_x>0)
	snake[boule].direction.x+=0.25;
      else
	snake[boule].direction.x-=0.25;
      snake[boule-1].tab_tour[snake[boule-1].atourner].compteur=0;
    }
    snake[boule-1].atourner++;
  } 
}

void Animer(){
  usleep(1000);
  if(rotation == 1){
    angle+=0.1;
    if(angle >= 360){
      angle = 0;
    }
  }
  else{
    /***** Gestion des obstacles *****/
    //Si la case actuelle contient un obstacle le serpent s'arrete
    if(blocs[snake[0].block_x][snake[0].block_y-1].obstacle>0){
      for(int k=0;k<TAILLE_MAX-taille_tir;k++)
	snake[k].direction.y=0;
      if(taille==1)
	fini=2;
      else if(taille!=1){ //on compte jusqua 40 avant de decrementer une boule 
	snake[0].compteur_colli+=20*vitesse;
	if(snake[0].compteur_colli>=40){

	  blocs[snake[0].block_x][snake[0].block_y-1].obstacle--;
	  taille--;
	  score+=10;
	  //si on decremente une boule alors l'obstacle diminue, le joueur gagne 10 pts
	  if(blocs[snake[0].block_x][snake[0].block_y-1].obstacle==0)
	    score+=100;
	  //Si l'obstacle est totalement détruit le joueur gagne 100 pts
	  snake[0].compteur_colli=0;
	}
      }
      
    }else{
      //Remise a 0 du compteur de collision
      snake[0].compteur_colli=0;
      /***** On fait avancer le serpent *****/
      for(int k=0;k<TAILLE_MAX-taille_tir;k++)
	snake[k].direction.y=vitesse;
    }

    /***** Gestion des bonus *****/
    //Cette condition cherche a savoir si le serpent percute une boule bonus
    if(blocs[snake[0].block_x][snake[0].block_y-1].bonus && snake[0].y-((snake[0].block_y-1)*8)>2.3 && snake[0].y-((snake[0].block_y-1)*8)<3.2){
      taille++;
      score+=20;
      blocs[snake[0].block_x][snake[0].block_y-1].bonus=0;
      //On ajoute 20 points et une boule au serpent
    }
 
    /***** Animation des boules *****/
    for(int x=0;x<largeur;x++)
      for(int y=0;y<longueur;y++){
	if(blocs[x][y].compteur>.5)	
	  blocs[x][y].rebond=-.01;
	else if(blocs[x][y].compteur<0)
	  blocs[x][y].rebond=.01;
	blocs[x][y].compteur+=blocs[x][y].rebond;
      }
    //Un compteur de rebond est necessaire. Les bonus sont affichés dans plateau.c

    float pente;
    float delta_y;
    float delta_x;
    for(int i=0;i<TAILLE_MAX;i++){
      //Les boules qui vont trop loin sont supprimés
      if(snake[i].y>8*(longueur-1)-1){
	snake[i].direction.y=0;
	snake[i].tir=0;
	if(i==0){
	  score+=40*taille;//On ajoute 40 pts par boule
	  taille=0;
	  fini=1;
	}
      }
      if(snake[i].tir)
	if(blocs[snake[i].block_x][snake[i].block_y-1].obstacle>0){
	  blocs[snake[i].block_x][snake[i].block_y-1].obstacle--;
	  score+=30;//Si on touche un obstacle par le tir on gagne 30 pts
	  if(blocs[snake[0].block_x][snake[0].block_y-1].obstacle==0)
	    score+=100;
	  //100 si l'obstacle est totalement detruit
	  snake[i].tir=0;
	}
	

      
      /***** Mise a jour des positions *****/
      snake[i].y+=snake[i].direction.y;
      snake[i].x+=snake[i].direction.x;
      int test=0;
      if(i>0){
	for(int t=0;t<snake[i-1].atourner;t++){
	  //Ici on compte le nombre de raffraichissement avant de remettre le vecteur direction en x a 0, si la boule tournais
	  if(snake[i-1].tab_tour[t].compteur>-1 && snake[i-1].tab_tour[t].compteur<1){
	    tourne=0;
	    snake[i-1].tab_tour[t].compteur++;
	    test=1;
	  }	
	}
	if(test==0){ //Si on a fini de tourner on rement le vecteur a 0
	  snake[i].direction.x=0;
	  tourne=1;
	}
      }
      /***** Mise a jour des positions *****/
      //Si on arrive au point y ou la boule precedente a tourné, on peut tourner 
      if(i>0 && i<TAILLE_MAX-taille_tir)
	if(tourne && snake[i-1].tab_tour[snake[i-1].atourner].pos_y-.5<=snake[i].y)
	  tourner(i);
      if(i!=0 && snake[i].y+0.4>=(snake[i].block_y)*8)
	snake[i].block_y++;

      /***** Gestion de la pente *****/

      snake[i].block_x=snake[i].x/2;
      delta_y=blocs[2][snake[i].block_y].hauteur-blocs[2][snake[i].block_y-1].hauteur;
      delta_x= 8;
      pente=delta_y/delta_x;
      snake[i].z+=pente*snake[i].direction.y;
      
    }
  if(pente_actuelle==prochaine_pente){
    float prochain_delta_y=blocs[2][snake[2].block_y+1].hauteur-blocs[2][snake[2].block_y].hauteur;
    float prochain_delta_x= 8;

    prochaine_pente=prochain_delta_y/prochain_delta_x;
    float del_y=blocs[2][snake[2].block_y].hauteur-blocs[2][snake[2].block_y-1].hauteur;
    float del_x= 8;
    pente_actuelle = del_y/del_x;
    incr=0;

  }
  //Si ça descend on augmente la hauteur de la camera sinon inverse
  if(snake[2].y+0.5>=(snake[2].block_y)*8 ){
    if(pente_actuelle>prochaine_pente)
      incr=-vitesse/2;
    else
      incr=vitesse/2;
}
    if(snake[0].y+0.6>=(snake[0].block_y)*8)
      snake[0].block_y++;
  }
  glutPostRedisplay();
}




//FONCTION QUI GERE LES EVENEMENTS CLAVIER
void click(unsigned char touche, int x, int y){
  int nb_tour;
  int i;
  //"d" ou "D" permet de tourner a droite
if(!rotation){
  if(touche=='d' || touche=='D'){
    if(snake[0].x+0.5<=largeur*2-2.2 && (blocs[(int)((snake[0].x+0.5)/2)][snake[0].block_y-1].obstacle==0
					 || (snake[0].direction.y==0 && blocs[(int)((snake[0].x+0.5)/2)][snake[0].block_y-2].obstacle==0))){
      for(i=0;i<TAILLE_MAX;i++){
	if(i==0){
	  nb_tour=snake[0].nb_tour;
	}
	else{
	  nb_tour=snake[i-1].nb_tour;
	}
	snake[i].tab_tour[nb_tour].pos_y=snake[0].y;
	snake[i].tab_tour[nb_tour].pos_x=+0.5;
	snake[i].nb_tour++;
      }
      snake[0].x+=0.5;
    }
  }
  
  //"q" ou "Q" permet de tourner a gauche
  if(touche=='q' || touche=='Q'){
         
    if(snake[0].x-0.5>=2.5 && (blocs[(int)((snake[0].x-0.5)/2)][snake[0].block_y-1].obstacle==0
			       || (snake[0].direction.y==0 && blocs[(int)((snake[0].x-0.5)/2)][snake[0].block_y-2].obstacle==0))) {	  
      for(i=0;i<TAILLE_MAX;i++){
	if(i==0){
	  nb_tour=snake[0].nb_tour;
	}
	else{
	  nb_tour=snake[i-1].nb_tour;
	}
	snake[i].tab_tour[nb_tour].pos_y=snake[0].y;
	snake[i].tab_tour[nb_tour].pos_x=-0.5;
	snake[i].nb_tour++;
      }
      snake[0].x-=0.5;          
    }  
  }
  
  //"z" ou "Z" permet de tirer
  if(touche=='z' || touche=='A'){
    //la derniere boule du serpent est alors projetee
    if(taille-1>0){
      snake[TAILLE_MAX-taille_tir]=snake[0];
      snake[TAILLE_MAX-taille_tir].tir=1;
      snake[TAILLE_MAX-taille_tir].direction.y+=2*vitesse;
      taille_tir++;
      taille--;
    }   
  }



  //"r" ou "R" permet de recomencer la partie quand elle est finie
  if((touche == 'r' ||  touche=='R') && fini!=0){
  pente_actuelle=-2;
  incr=vitesse;
    init_decor();
    init_plateau();
    score=0;
    rotation=1;
    taille=15;
    taille_tir=1;
    fini=0;
    srand(getpid());
    tourne=1;
    init_serpent(snake);
  }

  //"c" ou "C" permet de passer au niveau suivant si la partie est finie
  if((touche == 'c' ||  touche=='C') && fini!=0 && niveau !=-1){
    niveau++;
  pente_actuelle=-2;
  incr=vitesse;
    if(niveau%2==1){
      longueur+=5;
    }
    largeur=7+rand()%4;
    if(niveau%2==0){
      vitesse+=0.015;
    }
    init_decor();
    taille=15+niveau;
    srand(getpid());
    init_plateau();
    score=0;
    rotation=1;
    taille_tir=1;
    fini=0;
    tourne=1;
    init_serpent(snake);
  }     
} 
  //"p" ou "P" permet de lancer la partie
  if(touche == 'p' ||  touche=='P'){
    rotation = 0;
  }
  Affichage();
}


int main(int argc, char *argv[]){
  if(argc!=5 && argc!=1){
    printf("veuillez entrer ./troisd <longueur> <largeur> <vitesse> <taille> pour une partie personnalisée\n N'entrez aucun argument pour lancer les niveaux\n");
    exit(-1);
  }else if(argc==5){

if(atoi(argv[1])>1000 || atoi(argv[2])>100 || atoi(argv[4])>300){
 printf("Les dimensions sont trop grandes\nlongueur max=1000\nlargeur max=100\n taille max=300\n");
    exit(-1);
}

    longueur=atoi(argv[1]);
    largeur=atoi(argv[2]);
    vitesse=0.025*atoi(argv[3]);
    niveau=-1;
taille=atoi(argv[4]);
  }else if(argc==1){
    longueur=10;
    largeur=10;
    vitesse=0.05;
  taille=12;
  }
  
  init_decor();
  init_plateau();
  score=0;
  rotation=1;
  taille_tir=1;
  fini=0;
  srand(getpid());
  tourne=1;
  pente_actuelle=-2;
  prochaine_pente=0;
  incr=vitesse;
  init_serpent(snake);
  glutInit(&argc,argv);
  
  glutInitWindowSize(800,600);
  glutInitWindowPosition(50,50);
  glutCreateWindow("une fenetre");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glutKeyboardFunc(click);
  glutIdleFunc(Animer);
 
  glutDisplayFunc(Affichage);
 
  glutMainLoop();



    
  return 0;
}


