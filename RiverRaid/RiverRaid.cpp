#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura  400
#define janela_largura 800
float rotacao = 1;
float zoom = 1;
float pontax = 20, pontay = 20, velocidadebola = 10, pontaxPkb = -20, pontayPkb = -20;
float trans = 1;
float tx = 0.0, ty = 0.0, xStep = 4, yStep = 4, raiox = 20, raioy = 25;
void tela(GLsizei w, GLsizei h);
void keyboard();
void display(void);
void mousemoveu(int x, int y);
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
    glutPassiveMotionFunc(mousemoveu);
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
void mousemoveu(int x, int y) {

}
void tela(GLsizei w, GLsizei h)
{

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, janela_largura, 0, janela_altura);
    glMatrixMode(GL_PROJECTION);
}
static class Jogador {
public:
    static void desenharP1() {
        glPushMatrix();//empilha uma matriz

        glTranslatef(pontax, pontay, 0);//realoca a matriz no plano

        //centro do avião
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 0.7);
        glVertex2d(-2, -15);
        glVertex2d(-2, 15);
        glVertex2d(2, 15);
        glVertex2d(2, -15);
        //asa direita inferior
        glVertex2d(2, -12);
        glVertex2d(6, -12);
        glVertex2d(6, -15);
        glVertex2d(10, -15);
        glVertex2d(10, -12);
        glVertex2d(6, -12);
        glVertex2d(6, -10);
        glVertex2d(2, -10);

        glEnd();
          
        glPopMatrix();//desempilha matriz pra desenhar apartir da matriz original

    }

};
void desenhar() {
    Sleep(5);
    Jogador::desenharP1();


    glFlush();
}
void display() {
    keyboard();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(janela_largura / 2, janela_altura / 2, 0.0);
    glClearColor(0.001f, 0.5f, 0.02f, 1.0f);  // cor do fundo
    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo
    glViewport(0, 0, janela_largura, janela_altura);

    desenhar();

    glFlush(); // executa o desenho
}
void keyboard()
{

    if (GetAsyncKeyState('W') != 0) {
        if (pontayPkb < 200) {
            pontayPkb += 2;
        }
    }
    if (GetAsyncKeyState('A') != 0) {
        if (pontaxPkb > -300) {
            pontaxPkb -= 2;
        }
    }
    if (GetAsyncKeyState('S') != 0) {
        if (pontayPkb > -200) {
            pontayPkb -= 2;
        }
    }
    if (GetAsyncKeyState('D') != 0) {
        if (pontaxPkb < -20) {
            pontaxPkb += 2;
        }
    }
    glutPostRedisplay();
}
