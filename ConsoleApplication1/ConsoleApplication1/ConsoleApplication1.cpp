#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#define PI 3.1415926535898
#define janela_altura 700
#define janela_largura 700
/*PROTOTIPAÇÃO INCOMPLETA*/
typedef struct sIem {
	double x;
	double xaux;
	double y;
	double yaux;
	bool show = true;
} Item;

int auxstart = 0;

Item casa[10];
/*startar as houses*/

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void drawText(const char* text, int length, int x, int y);
void anima(int valor);
void casaarvore(int x, int y);
/*TRANSLAÇÕES PARA A CAMERA*/
float ty = 0;
float yStep = 20;
/*TRANSLAÇÕES PARA A NAVE*/
float tcontrol = 0;
int main(int argc, char** argv) {
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
	if (ty < -3700) {
		ty = ty;
	}
	else {
		ty -= yStep;
	}
	glutPostRedisplay();
	glutTimerFunc(100, anima, 1);
}

void inicializar() {
	casa[0].x = -310;
	casa[0].y = -50;
	for (int i = 1; i < 10; i++) {
		int aux = i - 1;
		if (i % 2 == 0) {
			casa[i].x = 270;
			casa[i].y = (casa[aux].y) + 450;
		}
		else {
			casa[i].x = -310;
			casa[i].y = (casa[aux].y) + 450;
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	case '\x0D':
		auxstart = 1;
		inicializar();
		break;
	}
	if (key == 'd') {
	}
	if (key == 'a') {
	}
	if (key == ' ') {
	}
}

void rua() {
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-350, -210);
	glVertex2f(-350, -140);
	glVertex2f(350, -140);
	glVertex2f(350, -210);
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

void casaarvore(int x, int y) {
	/*casa*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x, y);
	glVertex2f(x, y - 20);
	glVertex2f(x + 80, y - 20);
	glVertex2f(x + 80, y);
	glEnd();
	/*telhado casa*/
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x - 10, y);
	glVertex2f(x + 90, y);
	glVertex2f(x + 40, y + 20);
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

void lvlmap() {
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

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.8f);
	glVertex2f(-200, 1000);
	glVertex2f(-200, 4000);
	glVertex2f(200, 4000);
	glVertex2f(200, 1000);
	glEnd();
	rua();
	for (int i = 0; i < 10; i++) {
		casaarvore(casa[i].x, casa[i].y);
	}
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
}

void drawText(const char* text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void titulo(int x, int y) {
	std::string text;
	text = "RIVER RAID";
	drawText(text.data(), text.size(), 350, 400);
	std::string text2;
	text2 = "Aperte ENTER para comecar ou ESC para sair";
	drawText(text2.data(), text2.size(), 150, 300);
}

void desenhar() {
	glPushMatrix();
	if (auxstart == 1) {
		glTranslatef(0, ty, 0);
	}
	lvlmap();
	/*melhorar o level, tornar spawn de casas aleatório, e adicionar sprites de obstaculos*/
	glPopMatrix();
	/*movimentar avião e atirar*/
	glPushMatrix();
	glTranslatef(0, -150, 0);
	aviao();
	glPopMatrix();
	baixoinfo();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 1.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(janela_largura / 2, janela_altura / 2, 0);
	desenhar();
	titulo(-400, 300);
	glFlush();
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, janela_largura, 0, janela_altura);
	glMatrixMode(GL_MODELVIEW);
}
