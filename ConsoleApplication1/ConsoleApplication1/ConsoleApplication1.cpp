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

typedef struct sIem {
	double x;
	double xaux;
	double y;
	double yaux;
	bool show = true;
} Item;

int auxstart = 0;

Item casa[10];
Item posaviao;
Item comb[10];
/*startar as houses*/

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void drawText(const char* text, int length, int x, int y);
void anima(int valor);
void casaarvore(int x, int y);
void inicializar(Item posaviao);

float ty = 0;
float yStep = 20;
std::string text = "RIVER RAID";
std::string text2 = "Aperte ENTER para comecar ou ESC para sair";

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
	if (auxstart == 1) {
		posaviao.y += 1;
	}
	if (ty < -3700) {
		ty = ty;
	}
	else {
		ty -= yStep;
	}
	if (posaviao.x > 180 || posaviao.x < -180) {
		inicializar(posaviao);
	}
	glutPostRedisplay();
	glutTimerFunc(100, anima, 1);
}

void inicializar(Item item) {
	casa[0].x = -310;
	casa[0].y = -50;
	comb[0].x = 160;
	comb[0].y = 0;
	for (int i = 1; i < 10; i++) {
		int aux = i - 1;
		if (i % 2 == 0) {
			casa[i].x = 270;
			casa[i].y = (casa[aux].y) + 450;
			comb[i].x = (rand() % 180) * -1;
			comb[i].y = (comb[aux].y) + 500;

		}
		else {
			casa[i].x = -310;
			casa[i].y = (casa[aux].y) + 450;
			comb[i].x = (rand() % 180);
			comb[i].y = (comb[aux].y) + 500;
		}
	}
	for (int i = 0; i < 10; i++) {
		comb[i].show = true;
	}
	if (item.y > 1600) {
		posaviao.y = 1700;
	}
	else {
		posaviao.y = -100;
	}
	posaviao.x = 0;
	posaviao.xaux = 15;
	posaviao.yaux = 25;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	case '\x0D':
		posaviao.x = 0;
		posaviao.y = 0;
		posaviao.xaux = 15;
		posaviao.yaux = 25;
		auxstart = 1;
		inicializar(posaviao);
		text = " ";
		drawText(text.data(), text.size(), 350, 400);
		text2 = " ";
		drawText(text2.data(), text2.size(), 150, 300);
		break;
	}
	if (key == 'd') {
		posaviao.x += 5;
	}
	if (key == 'a') {
		posaviao.x -= 5;
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

void combustivel(Item item) {
	int x = item.x;
	int y = item.y;
	int xaux = item.xaux;
	int yaux = item.yaux;
	glScalef(1, 1, 1);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x - xaux + 20), y + yaux - 5);
	glVertex2f((x - xaux + 20), (y + yaux));
	glVertex2f((x - xaux + 5), (y + yaux));
	glVertex2f((x - xaux + 5), (y + yaux - 5));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x - xaux + 25), y + yaux - 20);
	glVertex2f((x - xaux + 25), y + yaux - 10);
	glVertex2f((x - xaux), y + yaux - 10);
	glVertex2f((x - xaux), y + yaux - 20);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x - xaux + 25), y + yaux - 35);
	glVertex2f((x - xaux + 25), y + yaux - 25);
	glVertex2f((x - xaux), y + yaux - 25);
	glVertex2f((x - xaux), y + yaux - 35);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x - xaux + 25), y + yaux - 50);
	glVertex2f((x - xaux + 25), y + yaux - 40);
	glVertex2f((x - xaux), y + yaux - 40);
	glVertex2f((x - xaux), y + yaux - 50);
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

void lago() {
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
	glVertex2f(-200, -100);
	glVertex2f(-200, 4000);
	glVertex2f(200, 4000);
	glVertex2f(200, -100);
	glEnd();
}

void lvlmap() {
	lago();
	rua();
	for (int i = 0; i < 10; i++) {
		casaarvore(casa[i].x, casa[i].y);
	}
	for (int i = 0; i < 10; i++) {
		if (comb[i].show) {
			combustivel(comb[i]);
		}
	}
}

void aviao(Item item) {
	int x = item.x;
	int y = item.y;
	int xaux = item.xaux;
	int yaux = item.yaux;
	glScalef(1, 1, 1);
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x - 3, y - yaux + 5);
	glVertex2f(x - 3, y + yaux);
	glVertex2f(x + 3, y + yaux);
	glVertex2f(x + 3, y - yaux + 5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f((x - xaux), y);
	glVertex2f((x - xaux), y + 8);
	glVertex2f(x, y + 16);
	glVertex2f(x, y + 8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f((x + xaux), y);
	glVertex2f((x + xaux), y + 8);
	glVertex2f(x, y + 16);
	glVertex2f(x, y + 8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f((x - xaux + 5), y - yaux);
	glVertex2f((x - xaux + 5), y - yaux + 5);
	glVertex2f(x, y - yaux + 10);
	glVertex2f(x, y - yaux + 5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f((x + xaux - 5), y - yaux);
	glVertex2f((x + xaux - 5), y - yaux + 5);
	glVertex2f(x, y - yaux + 10);
	glVertex2f(x, y - yaux + 5);
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
	drawText(text.data(), text.size(), 350, 400);
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
	aviao(posaviao);
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