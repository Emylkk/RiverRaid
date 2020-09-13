#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include<iostream>

#define janela_altura  800
#define janela_largura 800
float rotacao = 1;
float zoom = 1;
float direcaoX = 20, direcaoY = 20, velocidadebola = 10, pontaxPkb = -20, pontayPkb = -20;
int translMapa = 0;
float tx = 0.0, ty = 0.0, xStep = 4, yStep = 4, raiox = 20, raioy = 25;
int distanciaMapa = -400;
int x[10]{ 20, 100, 300, 150, 250, 100, 30, 300, 200, 350 };


void tela(GLsizei w, GLsizei h);
void keyboard();
void display(void);

void anima(int valor);
void colisao();
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
        
            glBegin(GL_QUADS);
            glColor3f(0, 0.8, 0);
            

            for (size_t i = 0; i < 10; i++)
            {
                glVertex2d(x[i], distanciaMapa);//esquerda abaixo
                glVertex2d(x[i], distanciaMapa+800);//subir na esquerda ↑
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