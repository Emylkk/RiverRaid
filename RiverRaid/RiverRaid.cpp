#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <random>
#include <time.h>
#include<iostream>

#define janela_altura  800
#define janela_largura 800
float rotacao = 1;
float zoom = 1;
float direcaoX = 0, direcaoY = 0, velocidadebola = 10, pontaxPkb = -20, pontayPkb = -20;
int translMapa = 0;
float tx = 0.0, ty = 0.0, xStep = 4, yStep = 4, raiox = 20, raioy = 25;
int distanciaMapa = -400;
int ciclo = 0;
int x[10]{ 20, 100, 300, 150, 250, 100, 30, 300, 200, 350 };




void tela(GLsizei w, GLsizei h);
void keyboard();
void display(void);

void anima(int valor);
void colisao();

class Inimigos {
public:
    Inimigos();
    ~Inimigos();
    int inimigosVet[10][10] = {};
    static void desenharNavio() {
        glPushMatrix();
        glTranslatef(-50, 70, 0);


        //parte de baixo do barco
        glBegin(GL_POLYGON);
        glColor3f(0, 0.7, 0.9);
        glVertex2d(-31, -2);
        glVertex2d(22, -2);
        glVertex2d(42, 4);
        glVertex2d(-45, 4);
        glEnd();

        //parte do meio do barco 
        glBegin(GL_POLYGON);
        glColor3f(0.75, 0, 0);
        glVertex2d(-42, 4);
        glVertex2d(42, 4);
        glVertex2d(42, 11);
        glVertex2d(-45, 11);
        glEnd();

        //parte de cima do barco
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        //parte inferior
        glVertex2d(-23, 11);
        glVertex2d(23, 11);
        glVertex2d(23, 17);
        glVertex2d(-23, 17);

        //parte chamine
        glVertex2d(-5, 11);
        glVertex2d(15, 11);
        glVertex2d(15, 25);
        glVertex2d(-5, 25);



        glEnd();

        glPopMatrix();
    }


public:
    static void desenharHeli() {

        glPushMatrix();

        glTranslatef(50, 50, 0);


        //base do heli
        glBegin(GL_POLYGON);
        glColor3f(0.0, 0.6, 0.0);
        glVertex2d(20, 1);
        glVertex2d(28, 4);
        glVertex2d(7, 4);
        glVertex2d(14, 1);
        glVertex2d(10, -4);
        glVertex2d(24, -4);
        glEnd();

        //parte de tras do heli
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.5, 1.0);
        glVertex2f(-22, 0);
        glVertex2f(-30, 0);
        glVertex2f(-30, 18);
        glVertex2f(-22, 18);
        glEnd();


        //parte do meio do heli
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.4);
        glVertex2f(30, 4);
        glVertex2f(-30, 4);
        glVertex2f(-30, 14);
        glVertex2f(30, 14);
        glEnd();


        //teto do heli
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.3);
        glVertex2f(30, 14);
        glVertex2f(0, 14);
        glVertex2f(0, 20);
        glVertex2f(30, 20);

        glEnd();

        //pilar da helice 
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.5);
        glVertex2f(22, 20);
        glVertex2f(12, 20);
        glVertex2f(12, 26);
        glVertex2f(22, 26);
        glEnd();

        ciclo++;
        if (ciclo == 10) {
            ciclo = -10;
        }

        //primeira parte da helice 
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.5);
        if (ciclo < 0) {
            glVertex2f(14, 27);
            glVertex2f(38, 27);
            glVertex2f(38, 32);
            glVertex2f(14, 32);
        }
        else if (ciclo > 0)
        {
            glVertex2f(14, 23);
            glVertex2f(38, 23);
            glVertex2f(38, 28);
            glVertex2f(14, 28);
        }

        glEnd();

        //segunda parte da helice 
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.5);
        if (ciclo < 0) {
            glVertex2f(22, 23);
            glVertex2f(-2, 23);
            glVertex2f(-2, 28);
            glVertex2f(22, 28);
        }
        else if (ciclo > 0)
        {
            glVertex2f(22, 27);
            glVertex2f(-2, 27);
            glVertex2f(-2, 32);
            glVertex2f(22, 32);
        }
        glEnd();

        glPopMatrix();

    }
};

int main(int argc, char** argv)
{

    glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA
    glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela

    //glutInitWindowPosition(100, 0); // posicao inicial da janela
    glutCreateWindow("GLUT");   /// cria a janela
    //glutFullScreen();  // full screen

    glutReshapeFunc(tela);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(velocidadebola, anima, 1);
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    glutMainLoop();

    return EXIT_SUCCESS;
}
void anima(int valor) {
    colisao();
    glutPostRedisplay();
    glutTimerFunc(velocidadebola, anima, 1);
}
void colisao() {

}
void tela(GLsizei w, GLsizei h)
{

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, janela_largura, 0, janela_altura);
    glMatrixMode(GL_PROJECTION);
}


static class Mapa {
public:
    static void DesenharParede() {
        Sleep(5);

        glPushMatrix();
        //Parede Direita
        Inimigos::desenharNavio();
        Inimigos::desenharHeli();
        glBegin(GL_QUADS);
        glColor3f(0, 0.8, 0);


        for (size_t i = 0; i < 10; i++)
        {
            glVertex2d(x[i], distanciaMapa);//esquerda abaixo
            glVertex2d(x[i], distanciaMapa + 800);//subir na esquerda ↑
            glVertex2d(400, distanciaMapa + 800);//direita acima
            glVertex2d(400, distanciaMapa);//direita ↓

            distanciaMapa += 800;
        }
        distanciaMapa = -400;

        glEnd();

        //Parede Esquerda
        glBegin(GL_QUADS);
        glColor3f(0, 0.8, 0);


        for (size_t i = 0; i < 10; i++)
        {
            glVertex2d(-x[i], distanciaMapa);//esquerda abaixo
            glVertex2d(-x[i], distanciaMapa + 800);//subir na esquerda ↑
            glVertex2d(-400, distanciaMapa + 800);//direita acima
            glVertex2d(-400, distanciaMapa);//direita ↓

            distanciaMapa += 800;
        }
        glEnd();

        glPopMatrix();
        distanciaMapa = -400;

    }
};


static class Jogador {
public:
    static void desenharP1() {

        glPushMatrix();//empilha uma matriz

        glTranslatef(direcaoX, direcaoY, 0);//realoca a matriz no plano


        //centro do avião
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 0.7);
        glVertex2d(-2, -15);
        glVertex2d(-2, 15);
        glVertex2d(2, 15);
        glVertex2d(2, -15);
        glEnd();

        //asa direita inferior

        glBegin(GL_POLYGON);
        glVertex2d(2, -12);
        glVertex2d(6, -12);
        glVertex2d(6, -15);
        glVertex2d(10, -15);
        glVertex2d(10, -12);
        glVertex2d(6, -12);
        glVertex2d(6, -10);
        glVertex2d(2, -10);
        glEnd();


        //asa esqueda inferior 

        glBegin(GL_POLYGON);
        glVertex2d(-2, -12);
        glVertex2d(-6, -12);
        glVertex2d(-6, -15);
        glVertex2d(-10, -15);
        glVertex2d(-10, -12);
        glVertex2d(-6, -12);
        glVertex2d(-6, -10);
        glVertex2d(-2, -10);
        glEnd();


        //asa direita superior 
        glBegin(GL_POLYGON);
        glVertex2d(2, 0);
        glVertex2d(18, -5);
        glVertex2d(14, 0);
        glVertex2d(2, 10);
        glVertex2d(2, 0);
        glEnd();


        //asa esquerda superior 
        glBegin(GL_POLYGON);
        glVertex2d(-2, 0);
        glVertex2d(-18, -5);
        glVertex2d(-14, 0);
        glVertex2d(-2, 10);
        glVertex2d(-2, 0);
        glEnd();


        glPopMatrix();



    }

};
void desenhar() {
    Sleep(5);
    Jogador::desenharP1();
    srand(time(NULL));
    
    
    

    if (rand() % 100 <= 5) {
       
    }
      
    
    translMapa += 1;
    glTranslatef(0, -translMapa, 0);
    Mapa::DesenharParede();

    glFlush();
}
void display() {
    keyboard();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(janela_largura / 2, janela_altura / 2, 0.0);
    glClearColor(0.00f, 0.0f, 1.0f, 1.0f);  // cor do fundo
    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo
    glViewport(0, 0, janela_largura, janela_altura);

    desenhar();

    glFlush(); // executa o desenho
}
void keyboard()
{

    if (GetAsyncKeyState('W') != 0) {
        if (direcaoY < 384) {
            direcaoY += 2;
        }
    }
    if (GetAsyncKeyState('A') != 0) {
        if (direcaoX > -380) {
            direcaoX -= 2;
        }
    }
    if (GetAsyncKeyState('S') != 0) {
        if (direcaoY > -384) {
            direcaoY -= 2;
        }
    }
    if (GetAsyncKeyState('D') != 0) {
        if (direcaoX < 380) {
            direcaoX += 2;
        }
    }
    glutPostRedisplay();
}
