#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#define PI 3.1415926535898
#define janela_altura 700
#define janela_largura 700
/*PROTOTIPAÇÃO INCOMPLETA*/
void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void anima(int valor);
void casaarvore();
/*TRANSLAÇÕES PARA A CAMERA*/
float ty = 0;
float yStep = 20;
/*TRANSLAÇÕES PARA A NAVE*/
float tcontrol = 0;
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /*MULTISAMPLE*/
	glutInitWindowSize(janela_largura, janela_altura);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("teste");
	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(100, anima, 1);
	glutMainLoop();
	return(0);
}

void anima(int valor) {
	if (ty < -700) {
		ty = ty;
	} else {
		ty -= yStep;
	} 
	int aux = rand() % 3;
	glutPostRedisplay();
	glutTimerFunc(100, anima, 1);
}

void keyboard(unsigned char tecla, int x, int y){
	if (tcontrol < 120 && tecla == 'd') {
		tcontrol = tcontrol + 10;
	}
	if (tcontrol> -120 && tecla == 'a') {
		tcontrol = tcontrol - 10;
	}
	glutPostRedisplay();
}


void rua() {
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-350, -210);
	glVertex2f(-350, -140);
	glVertex2f(-100, -140);
	glVertex2f(-100, -210);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-350, -170);
	glVertex2f(-350, -180);
	glVertex2f(-300, -180);
	glVertex2f(-300, -170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-250, -170);
	glVertex2f(-250, -180);
	glVertex2f(-200, -180);
	glVertex2f(-200, -170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-150, -170);
	glVertex2f(-150, -180);
	glVertex2f(-100, -180);
	glVertex2f(-100, -170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(350, -210);
	glVertex2f(350, -140);
	glVertex2f(100, -140);
	glVertex2f(100, -210);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(150, -170);
	glVertex2f(150, -180);
	glVertex2f(100, -180);
	glVertex2f(100, -170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(250, -170);
	glVertex2f(250, -180);
	glVertex2f(200, -180);
	glVertex2f(200, -170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(350, -170);
	glVertex2f(350, -180);
	glVertex2f(300, -180);
	glVertex2f(300, -170);
	glEnd();
}

void casaarvore() {
	/*casa*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-310, -50);
	glVertex2f(-310, -70);
	glVertex2f(-230, -70);
	glVertex2f(-230, -50);
	glEnd();
	/*telhado casa*/
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-320, -50);
	glVertex2f(-220, -50);
	glVertex2f(-270, -30);
	glEnd();
	/*tronco árvore*/
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.3f, 1.0f);
	glVertex2f(-250, -90);
	glVertex2f(-250, -110);
	glVertex2f(-240, -110);
	glVertex2f(-240, -90);
	glEnd();
	/*folhas árvore*/
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-260, -90);
	glVertex2f(-230, -90);
	glVertex2f(-245, -60);
	glEnd();
}

void baixoinfo() {
	/*canto em baixo FUNÇÃO PARA LETRAS*/
	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(-350, -350);
	glVertex2f(-350, -240);
	glVertex2f(350, -240);
	glVertex2f(350, -350);
	glEnd();
}

void lvl1map(){
	rua();
	/*primeira parte lago*/
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.8f);
	glVertex2f(-100, -240);
	glVertex2f(-100, -100);
	glVertex2f(100, -100);
	glVertex2f(100, -240);
	glEnd();

	/*segunda parte lago*/
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.8f);
	glVertex2f(-150, -100);
	glVertex2f(-150, 1000);
	glVertex2f(150, 1000);
	glVertex2f(150, -100);
	glEnd();

	/*bordas lago*/
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.5f);
	glVertex2f(-100, -100);
	glVertex2f(-150, -100);
	glVertex2f(-150, -70);
	glEnd();

	/*bordas lago*/
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.5f);
	glVertex2f(100, -100);
	glVertex2f(150, -100);
	glVertex2f(150, -70);
	glEnd();
}

void aviao() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-30, 0);
	glVertex2f(30, 0);
	glVertex2f(0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-10, 0);
	glVertex2f(10, 0);
	glVertex2f(10, -40);
	glVertex2f(-10, -40);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0, -20);
	glVertex2f(40, -70);
	glVertex2f(5, -45);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0, -20);
	glVertex2f(-40, -70);
	glVertex2f(-5, -45);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-10, 0);
	glVertex2f(-30, 0);
	glVertex2f(-40, -30);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-10, -40);
	glVertex2f(-20, 0);
	glVertex2f(0, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(10, 0);
	glVertex2f(30, 0);
	glVertex2f(40, -30);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(10, -40);
	glVertex2f(20, 0);
	glVertex2f(0, 0);
	glEnd();
}

void desenhar() {
	glPushMatrix();
	glTranslatef(0, ty, 0); 
	lvl1map();
	/*melhorar o level, tornar spawn de casas aleatório, e adicionar sprites de obstaculos*/
	glPopMatrix();
	/*movimentar avião e atirar*/
	glPushMatrix();
	glTranslatef(0, -150, 0);
	aviao();
	glPopMatrix();
	baixoinfo();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 1.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(janela_largura / 2, janela_altura / 2, 0);
	desenhar();
	glFlush();
}

void tela(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, janela_largura, 0, janela_altura);
	glMatrixMode(GL_MODELVIEW);
}
