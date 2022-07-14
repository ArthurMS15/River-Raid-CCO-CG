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

typedef struct sItem {
	double x;
	double y;
	bool show = true;
} Item;

int auxstart = 0;

Item posaviao;
Item postiro;
Item posinfobaixo;
Item posind;
Item casa[10];
Item comb[10];
Item rua[2];
Item navio[20];
Item heli[20];

/*startar as houses*/

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void drawText(const char* text, int length, int x, int y);
void anima(int valor);
void casaarvore(int x, int y);
void inicializar(Item posaviao);

float ty = 0;
float yStep = 10;
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
	glutTimerFunc(50, anima, 1);
	glutMainLoop();
	return(0);
}

bool checkCollide(double x, double y, double oWidth, double oHeight, double xTwo, double yTwo, double oTwoWidth, double oTwoHeight) {
	// AABB 1
	double x1Min = x;
	double x1Max = x + oWidth;
	double y1Max = y + oHeight;
	double y1Min = y;

	// AABB 2
	double x2Min = xTwo;
	double x2Max = xTwo + oTwoWidth;
	double y2Max = yTwo + oTwoHeight;
	double y2Min = yTwo;

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	return true;
}

void anima(int valor) {
	if (auxstart == 1) {
		posaviao.y += 1;
		posind.x -= 5;
	}
	if (postiro.show) {
		postiro.y += 30;
	}
	if (posaviao.y > posaviao.y + 250) {
		postiro.show = 0;
	}
	ty = ty - yStep;
	if (posind.x < -250) {
		inicializar(posaviao);
	}
	if (posaviao.x > 180 || posaviao.x < -180) {
		inicializar(posaviao);
	}
	for (int i = 0; i < 10; i++) {
		if (checkCollide(posaviao.x, posaviao.y, 19, 26, comb[i].x, comb[i].y, 26, 51) && comb[i].show) {
			posind.x = 150;
			comb[i].show = 0;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, anima, 1);
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
	postiro.show = 0;
	posaviao.y = -100;
	posaviao.x = 0;
	posinfobaixo.y = 0;
	posinfobaixo.x = 0;
	posind.y = 0;
	posind.x = 250;
	rua[0].x = 0;
	rua[0].y = 2000;
	rua[1].x = 0;
	rua[1].y = 4100;
	for (int i = 0; i < 2; i++) {
		rua[i].show = true;
	}
	navio[0].x = 150;
	navio[0].y = 10;
	heli[0].x = -150;
	heli[0].y = 10;
	for (int i = 1; i < 20; i++) {
		int aux = i - 1;
		if (i % 2 == 0) {
			navio[i].x = (rand() % 180) * -1;
			navio[i].y = (navio[aux].y) + 250;
			heli[i].x = (rand() % 180);
			heli[i].y = (heli[aux].y) + 100;
		}
		else {
			navio[i].x = (rand() % 180);
			navio[i].y = (navio[aux].y) + 100;
			heli[i].x = (rand() % 180) * -1;
			heli[i].y = (heli[aux].y) + 350;
		}
	}
	for (int i = 0; i < 20; i++) {
		navio[i].show = true;
		heli[i].show = true;
	}

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	case '\x0D':
		posaviao.x = 0;
		posaviao.y = 0;
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
	if (key == 'w') {
		posaviao.y += 5;
	}
	if (key == 's') {
		posaviao.y -= 5;
	}
	if (key == ' ') {
		checkCollide(posaviao.x, posaviao.y, 19, 26, comb[0].x, comb[0].y, 26, 51);
		postiro.x = posaviao.x;
		postiro.y = posaviao.y;
		postiro.show = posaviao.show;
	}
}

void indica(Item item) {
	int x = item.x;
	int y = item.y;
	glScalef(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(x - 5, y - 280);
	glVertex2f((x - 5), y - 310);
	glVertex2f((x + 5), (y - 310));
	glVertex2f(x + 5, (y - 280));
	glEnd();
}


void helis(Item item) {
	int x = item.x;
	int y = item.y;
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f((x + 20), (y + 30));
	glVertex2f((x - 10), (y + 30));
	glVertex2f((x - 10), (y + 10));
	glVertex2f((x + 20), (y + 10));
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0.8);
	glVertex2f((x + 4), (y + 10));
	glVertex2f((x + 8), (y + 10));
	glVertex2f((x + 8), y);
	glVertex2f((x + 4), y);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0.8);
	glVertex2f((x), (y - 5));
	glVertex2f((x + 10), (y - 5));
	glVertex2f((x + 10), y);
	glVertex2f((x), (y));
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f((x + 20), (y + 30));
	glVertex2f((x + 20), (y + 10));
	glVertex2f((x + 30), (y + 15));
	glVertex2f((x + 30), (y + 25));
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f((x - 10), (y + 30));
	glVertex2f((x - 10), (y + 10));
	glVertex2f((x - 20), (y + 15));
	glVertex2f((x - 20), (y + 25));
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f((x - 20), (y + 20));
	glVertex2f((x - 30), (y + 20));
	glVertex2f((x - 30), (y + 12.5));
	glVertex2f((x - 20), (y + 12.5));
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0.8);
	glVertex2f(x, (y + 30));
	glVertex2f((x + 5), (y + 30));
	glVertex2f((x + 5), (y + 50));
	glVertex2f(x, (y + 50));
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x, y + 55);
	glVertex2f(x, y + 50);
	glVertex2f(x - 20, y + 50);
	glVertex2f(x - 20, y + 55);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x + 5, y + 55);
	glVertex2f(x + 5, y + 50);
	glVertex2f(x + 25, y + 50);
	glVertex2f(x + 25, y + 55);
	glEnd();
}

void navios(Item item) {
	int x = item.x;
	int y = item.y;
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f((x + 50), (y + 24));
	glVertex2f((x - 50), (y + 24));
	glVertex2f((x - 20), y);
	glVertex2f((x + 20), y);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0.8);
	glVertex2f(x, (y + 20));
	glVertex2f((x + 5), (y + 20));
	glVertex2f((x + 5), (y + 50));
	glVertex2f(x, (y + 50));
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x, y + 50);
	glVertex2f(x, y + 30);
	glVertex2f(x - 20, y + 40);
	glEnd();
}

void tiros(Item item) {
	int x = item.x;
	int y = item.y;

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex2f(x - 5, y - 20);
	glVertex2f(x, (y - 10));
	glVertex2f((x + 5), y - 20);
	glEnd();
}

void ruas(Item item) {
	int x = item.x;
	int y = item.y;
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x - 350, y - 210);
	glVertex2f(x + 350, y - 210);
	glVertex2f(x + 350, y - 140);
	glVertex2f(x - 350, y - 140);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(x - 350, y - 170);
	glVertex2f(x - 350, y - 180);
	glVertex2f(x - 300, y - 180);
	glVertex2f(x - 300, y - 170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(x - 250, y - 170);
	glVertex2f(x - 250, y - 180);
	glVertex2f(x - 200, y - 180);
	glVertex2f(x - 200, y - 170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(x - 150, y - 170);
	glVertex2f(x - 150, y - 180);
	glVertex2f(x - 100, y - 180);
	glVertex2f(x - 100, y - 170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(x + 150, y - 170);
	glVertex2f(x + 150, y - 180);
	glVertex2f(x + 100, y - 180);
	glVertex2f(x + 100, y - 170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(x + 250, y - 170);
	glVertex2f(x + 250, y - 180);
	glVertex2f(x + 200, y - 180);
	glVertex2f(x + 200, y - 170);
	glEnd();
	/*rua*/
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(x + 350, y - 170);
	glVertex2f(x + 350, y - 180);
	glVertex2f(x + 300, y - 180);
	glVertex2f(x + 300, y - 170);
	glEnd();
}

void combustivel(Item item) {
	int x = item.x;
	int y = item.y;
	glScalef(1, 1, 1);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x + 20), y - 5);
	glVertex2f((x + 20), (y));
	glVertex2f((x + 5), (y));
	glVertex2f((x + 5), (y - 5));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x + 25), y - 20);
	glVertex2f((x + 25), y - 10);
	glVertex2f(x, y - 10);
	glVertex2f(x, y - 20);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x + 25), y - 35);
	glVertex2f((x + 25), y - 25);
	glVertex2f((x), y - 25);
	glVertex2f((x), y - 35);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((x + 25), y - 50);
	glVertex2f((x + 25), y - 40);
	glVertex2f((x), y - 40);
	glVertex2f((x), y - 50);
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

void infobaixo(Item item) {
	int x = item.x;
	int y = item.y;
	/*canto em baixo FUNÇÃO PARA LETRAS*/
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-350, -350);
	glVertex2f(-350, -240);
	glVertex2f(350, -240);
	glVertex2f(350, -350);
	glEnd();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x - 250, y - 280);
	glVertex2f((x - 250), y - 290);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x + 250, y - 280);
	glVertex2f((x + 250), y - 290);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x, y - 280);
	glVertex2f(x, y - 290);
	glEnd();
	/*F*/
	glLineWidth(1000000000);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x + 240, y - 300);
	glVertex2f((x + 270), y - 300);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x + 240, y - 315);
	glVertex2f((x + 270), y - 315);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x + 240, y - 330);
	glVertex2f((x + 240), y - 300);
	glEnd();
	/*E*/
	glLineWidth(1000000000);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x - 240, y - 330);
	glVertex2f((x - 270), y - 330);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x - 240, y - 315);
	glVertex2f((x - 270), y - 315);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x - 240, y - 300);
	glVertex2f((x - 270), y - 300);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(x - 270, y - 330);
	glVertex2f((x - 270), y - 300);
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
	for (int i = 0; i < 10; i++) {
		casaarvore(casa[i].x, casa[i].y);
	}
	for (int i = 0; i < 10; i++) {
		if (comb[i].show) {
			combustivel(comb[i]);
		}
	}
	for (int i = 0; i < 20; i++) {
		if (navio[i].show) {
			navios(navio[i]);
			helis(heli[i]);
		}
	}
	for (int i = 0; i < 2; i++) {
		if (rua[i].show) {
			ruas(rua[i]);
		}
	}
}

void aviao(Item item) {
	int x = item.x;
	int y = item.y;
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 9, y + 15);
	glVertex2f(x + 9, y + 15);
	glVertex2f(x, y + 30);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(x - 3, y + 25);
	glVertex2f(x - 3, y);
	glVertex2f(x + 3, y);
	glVertex2f(x + 3, y + 25);
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
	glTranslatef(0, -100, 0);
	aviao(posaviao);
	if (postiro.show) {
		tiros(postiro);
	}
	glPopMatrix();
	infobaixo(posinfobaixo);
	indica(posind);
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
