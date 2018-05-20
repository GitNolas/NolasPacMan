
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SOIL.h>
#include <unistd.h>
const int W_WIDTH = 900;
const int W_HEIGHT = 900;
#define DISTANCIA 4
#define PI 3.1416
#define INCREMENTO 0.2
float alpha=0;
float beta =0;
int fCadrado=0;
int fCirculo=0;
int fEsfera=0;
int fFanVerde=0;
int fFanAzul=0;
typedef struct objeto{
	float px;
	float py;
	float pz;
	float ex;
	float ey;
	float ez;
	int listarender;
	int tex;
} objeto;

extern int myEsfera();

struct objeto central={0,0,0,60,30,0};
struct objeto centralFondo={0,0,1,40,10,0};
struct objeto bCentroArriba={0,30,0,80,10,0};
struct objeto bCentroAbajo={0,-30,0,80,10,0};
struct objeto ppalArriba={0,50,0,200,10,0};
struct objeto ppalAbajo={0,-50,0,200,10,0};
struct objeto horiArribaIzq={-50,10,0,20,10,0};
struct objeto horiAbajoIzq={-50,-10,0,20,10,0};
struct objeto horiArribaDer={50,10,0,20,10,0};
struct objeto horiAbajoDer={50,-10,0,20,10,0};
struct objeto verArribaIzq={-75,20,0,10,30,0};
struct objeto verAbajoIzq={-75,-20,0,10,30,0};
struct objeto verArribaDer={75,20,0,10,30,0};
struct objeto verAbajoDer={75,-20,0,10,30,0};
struct objeto ppalDerArriba={95,30,0,10,50,0};
struct objeto ppalDerAbajo={95,-30,0,10,50,0};
struct objeto ppalIzqArriba={-95,30,0,10,50,0};
struct objeto ppalIzqAbajo={-95,-30,0,10,50,0};
struct objeto barreraArribaIzq={-55,35,0,10,20,0};
struct objeto barreraAbajoIzq={-55,-35,0,10,20,0};
struct objeto barreraAbajoDer={55,-35,0,10,20,0};
struct objeto barreraArribaDer={55,35,0,10,20,0};
struct objeto pacMan={20,20,0,9,9,0};
struct objeto verde={85,40,0,9,9,0};
struct objeto azul={-85,-40,0,9,9,0};

objeto mapa[21];
objeto coins[162];


int spaceTex=0;
int tder=0, tizq=0, tarri=0, taba=0, tmuro=0;
void texturas(){
	tder= SOIL_load_OGL_texture("pacman.jpg",SOIL_LOAD_RGBA,SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	tizq= SOIL_load_OGL_texture("pizq.png",SOIL_LOAD_RGBA,SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	tarri= SOIL_load_OGL_texture("parri.png",SOIL_LOAD_RGBA,SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	taba= SOIL_load_OGL_texture("paba.png",SOIL_LOAD_RGBA,SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
		pacMan.tex=tder;
	tmuro= SOIL_load_OGL_texture("muro.jpg",SOIL_LOAD_RGBA,SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
}


void myTeclasespeciales(int cursor,int x,int y)
{
 switch(cursor)
 {
//Traslaciones:

//Giros:
	 case GLUT_KEY_UP:
		 beta+=INCREMENTO;
		 break;
	 case GLUT_KEY_DOWN:
		 beta+=INCREMENTO;
		 break;
	 case GLUT_KEY_RIGHT:
		 alpha-=INCREMENTO;
		 break;
	 case GLUT_KEY_LEFT:
		 alpha+=INCREMENTO;
		 break;
	 default:
		 break;
 }

 if(alpha>=PI*2.0 && alpha<=0 ) alpha=0;
 if(beta>=PI*2.0 && beta<=0 ) beta=0; //hay que repasarlo para evitar el salto
	 glutPostRedisplay();
}

int circulo(){
	int Icadrado;
	Icadrado=glGenLists(1);
	glNewList(Icadrado,GL_COMPILE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin(GL_POLYGON);
		 for (int i = 0; i < 100 + 3; i++) {  // +1 para cerrar
				 glVertex3f( 0 + 0.5 * cos(2.0 * PI * i / 100), 0 + 0.5 * sin(2.0 * PI * i / 100),0);
		}
	glEnd();
	glEndList();
	return Icadrado;
}

int cadrado(){
	int Icadrado;
	Icadrado=glGenLists(1);
	glNewList(Icadrado,GL_COMPILE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(-0.5f,0.5f,0.0f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-0.5f,-0.5f,0.0f);
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(0.5f,-0.5f,0.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(0.5f,0.5f,0.0f);
		glEnd();
	glEndList();
	return Icadrado;
}

int fantasmaAzul(){
	int Icadrado;
	Icadrado=glGenLists(1);
	glNewList(Icadrado,GL_COMPILE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glPushMatrix();
		glTranslatef(-0.15,0.25,0.3);
		glPushMatrix();
			glScalef(0.15,0.15,0.15);
			glColor3f(1.0,1.0,1.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.15,0.25,0.3);
		glPushMatrix();
			glScalef(0.15,0.15,0.15);
			glColor3f(1.0,1.0,1.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,-0.05,0.3);
		glPushMatrix();
			glScalef(0.15,0.15,0.15);
			glColor3f(0.0,0.0,0.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,0.25,0);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glColor3f(0.0,0.0,1.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,0);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glColor3f(0.0,0.0,1.0);
			glCallList(fCadrado);
		glPopMatrix();
	glPopMatrix();
	glEnd();
	glEndList();

	return Icadrado;
}

int fantasmaVerde(){
	int Icadrado;
	Icadrado=glGenLists(1);
	glNewList(Icadrado,GL_COMPILE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glPushMatrix();
		glTranslatef(-0.15,0.25,0.3);
		glPushMatrix();
			glScalef(0.15,0.15,0.15);
			glColor3f(1.0,1.0,1.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.15,0.25,0.3);
		glPushMatrix();
			glScalef(0.15,0.15,0.15);
			glColor3f(1.0,1.0,1.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,-0.05,0.3);
		glPushMatrix();
			glScalef(0.15,0.15,0.15);
			glColor3f(0.0,0.0,0.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,0.25,0);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glColor3f(0.0,1.0,0.0);
			glCallList(fCirculo);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,0);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glColor3f(0.0,1.0,0.0);
			glCallList(fCadrado);
		glPopMatrix();
	glPopMatrix();
	glEnd();
	glEndList();

	return Icadrado;
}

void myCamara() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0,100.0f,-100.0,100.0f,-100.0,10000.0f);
	gluLookAt(((float)DISTANCIA*(float) sin(alpha)*cos(beta)),((float)DISTANCIA*(float) sin(beta)), ((float)DISTANCIA*cos(alpha)*cos(beta)), 0,0,0,0,1,0);

}
void luces (){
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_FACE, GL_SPECULAR);
  glColorMaterial(GL_FRONT_FACE, GL_DIFFUSE);
  glShadeModel(GL_SMOOTH);
  GLfloat difusa[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat posicion[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat especular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
  glLightfv(GL_LIGHT0, GL_POSITION, posicion);
  glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
}
int t=0;
void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamara();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
		glTranslatef(central.px, 0.0, 0.0);
		glPushMatrix();
			glScalef(central.ex,central.ey,central.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(central.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(centralFondo.px, centralFondo.py, centralFondo.pz);
		glPushMatrix();
			glScalef(centralFondo.ex,centralFondo.ey,centralFondo.ez);
			glColor3f(0.0f,0.0f,0.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(centralFondo.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(bCentroArriba.px, bCentroArriba.py, bCentroArriba.pz);
		glPushMatrix();
			glScalef(bCentroArriba.ex,bCentroArriba.ey,bCentroArriba.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(bCentroArriba.listarender);
		glPopMatrix();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(bCentroAbajo.px, bCentroAbajo.py, bCentroAbajo.pz);
		glPushMatrix();
			glScalef(bCentroAbajo.ex,bCentroAbajo.ey,bCentroAbajo.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(bCentroAbajo.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ppalArriba.px, ppalArriba.py, ppalArriba.pz);
		glPushMatrix();
			glScalef(ppalArriba.ex,ppalArriba.ey,ppalArriba.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(ppalArriba.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ppalAbajo.px, ppalAbajo.py, ppalAbajo.pz);
		glPushMatrix();
			glScalef(ppalAbajo.ex,ppalAbajo.ey,ppalAbajo.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(ppalAbajo.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ppalIzqArriba.px, ppalIzqArriba.py, ppalIzqArriba.pz);
		glPushMatrix();
			glScalef(ppalIzqArriba.ex,ppalIzqArriba.ey,ppalIzqArriba.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(ppalIzqArriba.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ppalIzqAbajo.px, ppalIzqAbajo.py, ppalIzqAbajo.pz);
		glPushMatrix();
			glScalef(ppalIzqAbajo.ex,ppalIzqAbajo.ey,ppalIzqAbajo.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(ppalIzqAbajo.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ppalDerArriba.px, ppalDerArriba.py, ppalDerArriba.pz);
		glPushMatrix();
			glScalef(ppalDerArriba.ex,ppalDerArriba.ey,ppalDerArriba.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(ppalDerArriba.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ppalDerAbajo.px, ppalDerAbajo.py, ppalDerAbajo.pz);
		glPushMatrix();
			glScalef(ppalDerAbajo.ex,ppalDerAbajo.ey,ppalDerAbajo.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(ppalDerAbajo.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(horiArribaIzq.px, horiArribaIzq.py, horiArribaIzq.pz);
		glPushMatrix();
			glScalef(horiArribaIzq.ex,horiArribaIzq.ey,horiArribaIzq.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(horiArribaIzq.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(horiAbajoIzq.px, horiAbajoIzq.py, horiAbajoIzq.pz);
		glPushMatrix();
			glScalef(horiAbajoIzq.ex,horiAbajoIzq.ey,horiAbajoIzq.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(horiAbajoIzq.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(horiArribaDer.px, horiArribaDer.py, horiArribaDer.pz);
		glPushMatrix();
			glScalef(horiArribaDer.ex,horiArribaDer.ey,horiArribaDer.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(horiArribaDer.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(horiAbajoDer.px, horiAbajoDer.py, horiAbajoDer.pz);
		glPushMatrix();
			glScalef(horiAbajoDer.ex,horiAbajoDer.ey,horiAbajoDer.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(horiAbajoDer.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(verArribaIzq.px, verArribaIzq.py, verArribaIzq.pz);
		glPushMatrix();
			glScalef(verArribaIzq.ex,verArribaIzq.ey,verArribaIzq.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(verArribaIzq.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(verAbajoIzq.px, verAbajoIzq.py, verAbajoIzq.pz);
		glPushMatrix();
			glScalef(verAbajoIzq.ex,verAbajoIzq.ey,verAbajoIzq.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(verAbajoIzq.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(verArribaDer.px, verArribaDer.py, verArribaDer.pz);
		glPushMatrix();
			glScalef(verArribaDer.ex,verArribaDer.ey,verArribaDer.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(verArribaDer.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(verAbajoDer.px, verAbajoDer.py, verAbajoDer.pz);
		glPushMatrix();
			glScalef(verAbajoDer.ex,verAbajoDer.ey,verAbajoDer.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(verAbajoDer.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(barreraAbajoDer.px, barreraAbajoDer.py, barreraAbajoDer.pz);
		glPushMatrix();
			glScalef(barreraAbajoDer.ex,barreraAbajoDer.ey,barreraAbajoDer.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(barreraAbajoDer.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(barreraAbajoIzq.px, barreraAbajoIzq.py, barreraAbajoIzq.pz);
		glPushMatrix();
			glScalef(barreraAbajoIzq.ex,barreraAbajoIzq.ey,barreraAbajoIzq.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(barreraAbajoIzq.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(barreraArribaIzq.px, barreraArribaIzq.py, barreraArribaIzq.pz);
		glPushMatrix();
			glScalef(barreraArribaIzq.ex,barreraArribaIzq.ey,barreraArribaIzq.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(barreraArribaIzq.listarender);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(barreraArribaDer.px, barreraArribaDer.py, barreraArribaDer.pz);
		glPushMatrix();
			glScalef(barreraArribaDer.ex,barreraArribaDer.ey,barreraArribaDer.ez);
			glColor3f(0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D,tmuro);
			glCallList(barreraArribaDer.listarender);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_CULL_FACE);

		glDisable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(pacMan.px, pacMan.py, pacMan.pz);
		glPushMatrix();
			glScalef(pacMan.ex,pacMan.ey,pacMan.ez);
			glColor3f(1.0f,1.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D, pacMan.tex);
			glCallList(pacMan.listarender);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
		glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);

	for(int i=0;i<162;i++){
		glPushMatrix();
		glTranslatef(coins[i].px,coins[i].py,coins[i].pz);
		glPushMatrix();
		glScalef(1,1,1);
		glColor3f(1.0f,1.0f,0.0f);
		glCallList(coins[i].listarender);
		glPopMatrix();
		glPopMatrix();
	}
	glDisable(GL_LIGHTING);

	glPushMatrix();
		glTranslatef(verde.px, verde.py, 6);
		glPushMatrix();
			glScalef(verde.ex,verde.ey,verde.ez);
			glColor3f(0.0f,1.0f,0.0f);
			glCallList(verde.listarender);
		glPopMatrix();
	glPopMatrix();
		glEnable(GL_LIGHTING);
		glDisable(GL_LIGHTING);

	glPushMatrix();
		glTranslatef(azul.px, azul.py, 6);
		glPushMatrix();
			glScalef(azul.ex,azul.ey,azul.ez);
			glColor3f(0.0f,1.0f,0.0f);
			glCallList(azul.listarender);
		glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
int intersec(struct objeto a, struct objeto b){
	return (fabs(a.px - b.px)*2 < (a.ex + b.ex)) &&
	(fabs(a.py - b.py)*2 < (a.ey + b.ey));
}
int intersecMap(objeto a){
	for (int i=0; i<21;i++){
		if(intersec(a, mapa[i])){
			return 1;
		}
	}
	return 0;
}
void initCoins(){
	int k=-85, z=-40,i=0;;
	for (k=-85; k<=85; k+=10) {
    for (z=-40; z<=40; z+=10) {
      coins[i].px=k;
			coins[i].py=z;
			coins[i].pz=-1;
			coins[i].listarender=fCirculo;
			if(intersecMap(coins[i])){
				coins[i].px=400;
				coins[i].py=400;
			}
      i++;
    }
  }

}


void comer(){
	for (int i=0; i<162;i++){
		if(intersec(pacMan, coins[i])){
			coins[i].px=400;
			coins[i].py=400;
			return;
		}
	}

}
void loop(){
	if (pacMan.px>100 && pacMan.py==0){
		pacMan.px=-99;
	}
	if (pacMan.px<-100 && pacMan.py==0){
		pacMan.px=99;
	}
}
void loopV(){
	if (verde.px>100 &&verde.py==0){
		verde.px=-99;
	}
	if (verde.px<-100 && verde.py==0){
		verde.px=99;
	}
}
void loopA(){
	if (azul.px>100 && azul.py==0){
		azul.px=-99;
	}
	if (azul.px<-100 && azul.py==0){
		azul.px=99;
	}
}
void cazar(){
	if(intersec(pacMan,verde) || intersec(pacMan,azul)){
		printf("Los fantasmas ganan\n");
		exit(EXIT_SUCCESS);
	}
}
int todasCoins(){
	for(int i=0;i<162;i++){
		if(!(coins[i].px==400 && coins[i].py==400)){
			return 0;
		}
	}
	return 1;
}
void ganar(){
	if(todasCoins()){
		printf("Pacman gana.\n");
		exit(EXIT_SUCCESS);
	}
}
void calculo() {
	ganar();
	glutPostRedisplay();
	glutTimerFunc(40, calculo, 0);
}
void myTeclado(unsigned char tras,int x,int y){
	switch (tras) {
		case 'w':
			pacMan.py+=1;//1
			pacMan.tex=tarri;
			//ganar();
			cazar();
			loop();
			comer();
			if(intersecMap(pacMan)){
					pacMan.py-=1;
			}
		break;
		case 's'://2
		pacMan.py-=1;
		pacMan.tex=taba;
		//ganar();
		cazar();
		loop();
		comer();
			if(intersecMap(pacMan)){
				pacMan.py+=1;
			}
		break;
		case 'd'://3
		pacMan.px+=1;
		pacMan.tex=tder;
		//ganar();
		cazar();
		loop();
		comer();
			if(intersecMap(pacMan)){
				pacMan.px-=1;
			}
		break;
		case 'a'://4
			pacMan.px-=1;
			pacMan.tex=tizq;
			//ganar();
			cazar();
			loop();
			comer();
			if(intersecMap(pacMan)){
				pacMan.px+=1;
			}
		break;
		case 't'://1
			verde.py+=1;
			cazar();
			loopV();
			if(intersecMap(verde)){
					verde.py-=1;
			}
		break;
		case 'g'://2
			verde.py-=1;
			cazar();
			loopV();
			if(intersecMap(verde)){
				verde.py+=1;
			}
		break;
		case 'h'://3
			verde.px+=1;
			cazar();
			loopV();
			if(intersecMap(verde)){
				verde.px-=1;
			}
		break;
		case 'f'://4
		verde.px-=1;
		cazar();
		loopV();
		if(intersecMap(verde)){
			verde.px+=1;
		}
		break;
		case 'i':
			azul.py+=1;
			cazar();
			loopA();
			if(intersecMap(azul)){
					azul.py-=1;
			}
		break;
		case 'k':
			azul.py-=1;
			cazar();
			loopA();
			if(intersecMap(azul)){
				azul.py+=1;
			}
		break;
		case 'l':
			azul.px+=1;
			cazar();
			loopA();
			if(intersecMap(azul)){
				azul.px-=1;
			}
		break;
		case 'j':
		azul.px-=1;
		cazar();
		loopA();
		if(intersecMap(azul)){
			azul.px+=1;
		}
		break;
	}
		glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize (glutGet(GLUT_SCREEN_HEIGHT), glutGet(GLUT_SCREEN_HEIGHT));
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Proyecto CoGa Nolas");


	glClearDepth( 1.0f );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);


		mapa[0]=central;mapa[1]=bCentroAbajo;mapa[2]=bCentroArriba;mapa[3]=ppalDerArriba;mapa[4]=ppalIzqArriba;
		mapa[5]=ppalArriba;mapa[6]=ppalAbajo;mapa[7]=horiAbajoDer;mapa[8]=horiAbajoIzq;mapa[9]=horiArribaDer;
		mapa[10]=horiArribaIzq;mapa[11]=verAbajoDer;mapa[12]=verAbajoIzq;mapa[13]=verArribaDer;mapa[14]=verArribaIzq;
		mapa[15]=barreraAbajoDer;mapa[16]=barreraAbajoIzq;mapa[17]=barreraArribaDer;mapa[18]=barreraArribaIzq;
		mapa[19]=ppalDerAbajo;mapa[20]=ppalIzqAbajo;
	fCadrado=cadrado();
	fCirculo=circulo();
	fEsfera=myEsfera();
		initCoins();
		texturas();
			luces();

	central.listarender=fCadrado;
	centralFondo.listarender=fCadrado;
	bCentroArriba.listarender=fCadrado;
	bCentroAbajo.listarender=fCadrado;
	ppalArriba.listarender=fCadrado;
	ppalAbajo.listarender=fCadrado;
	ppalDerArriba.listarender=fCadrado;
	ppalIzqArriba.listarender=fCadrado;
	ppalDerAbajo.listarender=fCadrado;
	ppalIzqAbajo.listarender=fCadrado;
	horiArribaIzq.listarender=fCadrado;
	horiAbajoIzq.listarender=fCadrado;
	horiArribaDer.listarender=fCadrado;
	horiAbajoDer.listarender=fCadrado;
	verArribaIzq.listarender=fCadrado;
	verAbajoIzq.listarender=fCadrado;
	verArribaDer.listarender=fCadrado;
	verAbajoDer.listarender=fCadrado;
	barreraAbajoDer.listarender=fCadrado;
	barreraAbajoIzq.listarender=fCadrado;
	barreraArribaIzq.listarender=fCadrado;
	barreraArribaDer.listarender=fCadrado;
	pacMan.listarender=fCadrado;
	fFanAzul=fantasmaAzul();
	fFanVerde=fantasmaVerde();
	azul.listarender=fFanAzul;
	verde.listarender=fFanVerde;

	glutKeyboardFunc(myTeclado);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(myTeclasespeciales);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glViewport(0,0,W_WIDTH,W_HEIGHT);
	glutPostRedisplay();
	glutTimerFunc(40, calculo, 0);
	glutMainLoop();
}
