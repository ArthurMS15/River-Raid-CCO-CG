#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#define janela_largura 700
#define janela_altura 700
typedef struct sItem {
    float x;
    float y;
    int xaux;
    int yaux;
    int show = 1;
} Item;
Item posaviao; //posaviao
Item postela;
Item posinfobaixo; //posinfobaixo
Item posind; //posind
Item postiro; //postiro
int iniciar = 0;
void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);
void arrow_keys(int tecla, int x, int y);
void animate(int value);
void inicializar(Item posaviao);
void ajuiniciarela();
std::string text = "RIVER RAID";
std::string text2 = "Aperte ENTER para comecar ou ESC para sair";
Item combs[5];
Item helis[15];
Item navios[15];
Item ruas[2];
int main(int argc, char** argv) {
    ajuiniciarela();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_largura, janela_altura);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("mapa raid");
    glutKeyboardFunc(&keyboard);
    glutReshapeFunc(&resize);
    glutDisplayFunc(display);
    glutTimerFunc(50, animate, 1);
    glutMainLoop();
    return EXIT_SUCCESS;
}


bool checkCollide(int x, int y, int oWidth, int oHeight, int xTwo, int yTwo, int oTwoWidth, int oTwoHeight) {
    // AABB 1
    int x1Min = x;
    int x1Max = x + oWidth;
    int y1Max = y + oHeight;
    int y1Min = y;

    // AABB 2
    int x2Min = xTwo;
    int x2Max = xTwo + oTwoWidth;
    int y2Max = yTwo + oTwoHeight;
    int y2Min = yTwo;

    // Collision tests
    if (x1Max < x2Min || x1Min > x2Max) return false;
    if (y1Max < y2Min || y1Min > y2Max) return false;

    return true;
}

void desenharText(const char* text, int length, int x, int y) {
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
    desenharText(text.data(), text.size(), 350, 400);
    desenharText(text2.data(), text2.size(), 150, 300);
}
/*ajuste do plano cartesiano*/
void ajuiniciarela() {
    postela.x = 750;
    postela.y = janela_altura / 2;
}
void inicializar(Item Item) {
    postela.y = janela_altura / 2;
    posaviao.y = -120;
    posind.y = 0;
    posinfobaixo.y = 0;
    postela.x = janela_largura / 2;
    posaviao.x = 0;
    posinfobaixo.x = 0;
    posind.x = 250;
    postiro.show = 0;
    ruas[0].x = 0;
    ruas[0].y = 1500;
    ruas[0].xaux = 250;
    ruas[0].yaux = 30;
    ruas[1].x = 0;
    ruas[1].y = 3000;
    ruas[1].xaux = 250;
    ruas[1].yaux = 30;
    for (int i = 0; i < 2; i++) {
        ruas[i].show = 1;
    }
    //////////////////////////
    combs[0].x = -70;
    combs[0].y = 50;
    combs[1].x = 0;
    combs[1].y = 600;
    combs[2].x = 180;
    combs[2].y = 1200;
    combs[3].x = -120;
    combs[3].y = 1800;
    combs[4].x = -150;
    combs[4].y = 2400;
    for (int i = 0; i < 5; i++) {
        combs[i].xaux = 12;
        combs[i].yaux = 22;
        combs[i].show = 1;
    }
    ////////////////////////
    helis[0].x = -100;
    helis[0].y = 10;
    navios[0].x = -155;
    navios[0].y = 200;
    for (int i = 1; i < 15; i++) {
        int aux = i - 1;
        if (i % 2 == 0) {
            helis[i].x = (rand() % 180);
            helis[i].y = (helis[aux].y) + 200;
            navios[i].x = (rand() % 180);
            navios[i].y = (navios[aux].y) + 200;
        }
        else {
            helis[i].x = (rand() % 180) * -1;
            helis[i].y = (helis[aux].y) + 200;
            navios[i].x = (rand() % 180);
            navios[i].y = (navios[aux].y) + 200;
        }
        helis[i].xaux = 25;
        helis[i].yaux = 15;
        navios[i].xaux = 27;
        navios[i].yaux = 17;
    }
    for (int i = 0; i < 15; i++) {
        helis[i].show = 1;
    }
    for (int i = 0; i < 15; i++) {
        navios[i].show = 1;
    }
}
int colisao(Item a, Item b) {
    float leftA = (a.x - a.xaux);
    float leftB = (b.x - b.xaux);
    float rightA = (a.x + a.xaux);
    float rightB = (b.x + b.xaux);
    float upA = (a.y + a.yaux);
    float downB = (b.y - b.yaux);
    float downA = (a.y - a.yaux);
    float upB = (b.y + b.yaux);
    if ((upA >= downB) && (downA <= upB) && (leftA < rightB) && (rightA > leftB)) {
        if (b.show) {
            return 1;
        }
    }
    return 0;
}
void animate(int value) {
    if (iniciar == 1) {
        posaviao.y += 4;
        postela.y += -4;
        posinfobaixo.y += 4;
        posind.y += 4;
        posind.x -= 1;
    }
    if (postiro.show) {
        postiro.y += 30;
    }
    if (postiro.y > posaviao.y + 400) {
        postiro.show = 0;
    }
    if (posaviao.x > 180 || posaviao.x < -180) {
        inicializar(posaviao);
    }
    if (posind.x < -250) {
        inicializar(posaviao);
    }
    for (int i = 0; i < 5; i++) {
        if (colisao(posaviao, combs[i]) && combs[i].show) {
            posind.x = 250;
            combs[i].show = 0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(50, animate, 1);
}
void keyboard(unsigned char key, int x, int y) {
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    case '\x0D':
        posaviao.x = 0;
        posaviao.y = 0;
        inicializar(posaviao);
        text = " ";
        desenharText(text.data(), text.size(), 350, 400);
        text2 = " ";
        desenharText(text2.data(), text2.size(), 150, 300);
        iniciar = 1;
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
        colisao(posaviao, combs[0]);
        postiro.x = posaviao.x;
        postiro.y = posaviao.y;
        postiro.show = posaviao.show;
    }
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        gluOrtho2D(0.0f, janela_altura, 0.0f, janela_largura * h / w);
    }
    else {
        gluOrtho2D(0.0f, janela_altura * w / h, 0.0f, janela_largura);
    }
    glMatrixMode(GL_MODELVIEW);
}

void mapa() {
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
    glVertex2f(-200, -250);
    glVertex2f(-200, 3000);
    glVertex2f(200, 3000);
    glVertex2f(200, -250);
    glEnd();
}

void aviao(Item Item) {
    int x = Item.x;
    int y = Item.y;
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f((x - 15), y);
    glVertex2f((x - 15), y + 8);
    glVertex2f(x, y + 16);
    glVertex2f(x, y + 8);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f((x + 15), y);
    glVertex2f((x + 15), y + 8);
    glVertex2f(x, y + 16);
    glVertex2f(x, y + 8);
    glEnd();
}
void comb(Item Item) {
    int x = Item.x;
    int y = Item.y;
    int xaux = Item.xaux;
    int yaux = Item.yaux;
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - xaux, (y - yaux + 5));
    glVertex2f((x + xaux), (y - yaux + 5));
    glVertex2f((x + xaux), (y - yaux + 10));
    glVertex2f(x - xaux, (y - yaux + 10));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x - xaux, (y - yaux + 10));
    glVertex2f((x + xaux), (y - yaux + 10));
    glVertex2f((x + xaux), (y - yaux + 15));
    glVertex2f(x - xaux, (y - yaux + 15));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - xaux, (y - yaux + 15));
    glVertex2f((x + xaux), (y - yaux + 15));
    glVertex2f((x + xaux), (y + yaux - 20));
    glVertex2f(x - xaux, (y + yaux - 20));
    glEnd();
}
void rua(Item Item) {
    int x = Item.x;
    int y = Item.y;
    int xaux = Item.xaux;
    int yaux = Item.yaux;
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(x - xaux - 1500, y - yaux);
    glVertex2f((x + xaux + 1500), y - yaux);
    glVertex2f((x + xaux + 1500), (y + yaux));
    glVertex2f(x - xaux - 1500, (y + yaux));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x - xaux + 50, y - 5);
    glVertex2f((x - xaux + 50), y + 5);
    glVertex2f((x - 100), (y + 5));
    glVertex2f(x - 100, (y - 5));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x - 50, y - 5);
    glVertex2f((x - 50), y + 5);
    glVertex2f((x + 50), (y + 5));
    glVertex2f(x + 50, (y - 5));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x + 100, y - 5);
    glVertex2f((x + 100), y + 5);
    glVertex2f((x + 200), (y + 5));
    glVertex2f(x + 200, (y - 5));
    glEnd();
}
void navio(Item Item) {
    int x = Item.x;
    int y = Item.y;
    int xaux = Item.xaux;
    int yaux = Item.yaux;
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.33, 0.13);
    glVertex2f((x - xaux), y - yaux);
    glVertex2f((x + xaux), y - yaux);
    glVertex2f((x + xaux + 15), (y - yaux + 15));
    glVertex2f((x - xaux - 15), (y - yaux + 15));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f((x - xaux), (y - yaux + 24));
    glVertex2f((x + xaux - 20), (y - yaux + 24));
    glVertex2f((x + xaux - 20), (y - yaux + 30));
    glVertex2f((x - xaux), (y - yaux + 30));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f((x - xaux + 25), (y - yaux + 24));
    glVertex2f((x + xaux - 20), (y - yaux + 24));
    glVertex2f((x + xaux - 20), (y + yaux - 20));
    glVertex2f((x - xaux + 25), (y + yaux - 20));
    glEnd();
}
void heli(Item Item) {
    int x = Item.x;
    int y = Item.y;
    int xaux = Item.xaux;
    int yaux = Item.yaux;
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f((x - 2), y - yaux + 10);
    glVertex2f((x - 2), y + 20);
    glVertex2f((x + 2), y + 20);
    glVertex2f((x + 2), (y - yaux + 10));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f((x - 10), y - yaux + 30);
    glVertex2f((x - 10), y - yaux + 32);
    glVertex2f((x + 10), y - yaux + 32);
    glVertex2f((x + 10), (y - yaux + 30));
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex2f((x - xaux), y);
    glVertex2f((x - xaux), (y + 5));
    glVertex2f((x + xaux), (y + 5));
    glVertex2f((x + xaux), y);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex2f((x - xaux + 15), y - 5);
    glVertex2f((x - xaux + 15), (y + 5));
    glVertex2f((x + xaux - 10), (y + 5));
    glVertex2f((x + xaux - 10), y - 5);
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

void indica(Item item) {
    int x = item.x;
    int y = item.y;
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - 5, y - 280);
    glVertex2f((x - 5), y - 310);
    glVertex2f((x + 5), (y - 310));
    glVertex2f(x + 5, (y - 280));
    glEnd();
}

void tiro(Item Item) {
    int x = Item.x;
    int y = Item.y;
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);
    glVertex2f(x - 5, y - 20);
    glVertex2f((x), y - 10);
    glVertex2f((x + 5), (y - 20));
    glEnd();
}
void desenhar() {
    mapa();
    aviao(posaviao);
    if (postiro.show) {
        tiro(postiro);
    }
    for (int i = 0; i < 2; i++) {
        if (colisao(postiro, ruas[i])) {
            ruas[i].show = 0;
            postiro.show = 0;
        }
        if (ruas[i].show) {
            rua(ruas[i]);
        }
        if (checkCollide(posaviao.x, posaviao.y, 31, 9, ruas[i].x, ruas[i].y, 501, 30)) {
            inicializar(posaviao);
        }
    }
    for (int i = 0; i < 5; i++) {
        if (combs[i].show) {
            comb(combs[i]);
        }
    }
    for (int i = 0; i < 15; i++) {
        if (colisao(postiro, helis[i])) {
            helis[i].show = 0;
            postiro.show = 0;
        }
        if (helis[i].show) {
            heli(helis[i]);
        }
        if (colisao(posaviao, helis[i])) {
            inicializar(posaviao);
        }
    }
    for (int i = 0; i < 15; i++) {
        if (colisao(postiro, navios[i])) {
            navios[i].show = 0;
            postiro.show = 0;
        }
        if (navios[i].show) {
            navio(navios[i]);
        }
        if (colisao(posaviao, navios[i])) {
            inicializar(posaviao);
        }
    }
    infobaixo(posinfobaixo);
    indica(posind);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 1.00f, 0.0f, 0.0f);
    glTranslatef(postela.x, postela.y, 0.0f);
    desenhar();
    titulo(-400, 300);
    glFlush();
}