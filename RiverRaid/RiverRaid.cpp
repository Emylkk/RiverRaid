#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include<iostream>

#define janela_altura  800
#define janela_largura 800
float rotacao = 1,zoom = 1;;
bool shoot = false;
int t = 0;

float player_posX = 0, player_posY = 20, player_speed = 10, posicao_relativa=0;
int translMapa = 0;
int distanciaMapa = -400;
int x[10]{ 20, 100, 300, 150, 250, 100, 30, 300, 200, 350 };
int xy_Shoot[2]= {0,0};
bool rota = false;
void reshape(GLsizei w, GLsizei h);
void keyboard();
void display(void);
void desenhar();
void colisao();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA
    glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
    glutInitWindowPosition(50, 50); // Pos. onde surge a janela
    glutCreateWindow("GLUT");   /// cria a janela
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void colisao() {
    posicao_relativa = translMapa + player_posY;
}
void reshape(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1; // previne a divisão por zero
    GLfloat aspecto = (GLfloat)w / (GLfloat)h; glViewport(0, 0, w,h); glMatrixMode(GL_PROJECTION);// manipulando matriz de projeção
    glLoadIdentity(); // zerando a matriz
    gluPerspective(0.0f, aspecto, -10.0f, 10.0f);
    glClearColor(0.0f, 0.0f, 0.7f, 1.0f); // configura fundo sem transparencia
    glEnable(GL_DEPTH_TEST); // alunos devem testar
    glShadeModel(GL_SMOOTH); // acabamento com suavização
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    keyboard();
    desenhar();
    glFlush(); // executa o desenho
    glutSwapBuffers();
}
static class Mapa {
public:
    static void DesenharParede() {

        glPushMatrix();
        //Parede Direita
        
            glBegin(GL_QUADS);
            glColor3f(0, 0.8, 0);
            

            for (size_t i = 0; i < 10; i++)
            {
                glVertex3f(x[i], distanciaMapa,0);//esquerda abaixo
                glVertex3f(x[i], distanciaMapa+800,0);//subir na esquerda ↑
                glVertex3f(400, distanciaMapa + 800,0);//direita acima
                glVertex3f(400, distanciaMapa,0);//direita ↓

                distanciaMapa += 800;
            }
            distanciaMapa = -400;

            glEnd();

            //Parede Esquerda
            glBegin(GL_QUADS);
            glColor3f(0, 0.8, 0);


            for (size_t i = 0; i < 10; i++)
            {
                glVertex3f(-x[i], distanciaMapa,0);//esquerda abaixo
                glVertex3f(-x[i], distanciaMapa + 800,0);//subir na esquerda ↑
                glVertex3f(-400, distanciaMapa + 800,0);//direita acima
                glVertex3f(-400, distanciaMapa,0);//direita ↓

                distanciaMapa += 800;
            }
            glEnd();

            glPopMatrix();
            distanciaMapa = -400;
            
    }
};
bool teste=false;
 bool tirosValidar() {
    bool teste = true;
    //Zera os tiros sumiram ou colidiram
  
        if (xy_Shoot[1] > janela_altura / 2) {
            printf("ué");
            xy_Shoot[0] = 0;
            xy_Shoot[1] = 0;
            rota = false;

        }
        //testa se todos os tiros cessaram
        if ((xy_Shoot[0] == 0) && (xy_Shoot[1] == 0)) {
            teste = false;
            rota = false;
            printf("%i %i", xy_Shoot[1], xy_Shoot[0]);
        }

    return(teste);

}

static class Jogador {
    Jogador();
    ~Jogador();
public:
    
    static void desenharP1() {

        glPushMatrix();//Matriz de movimentação
        teste = tirosValidar();

        if (shoot or rota ) {

            Jogador::desenharProjetil();

        }
        glTranslatef(player_posX, player_posY, 0);//realoca a matriz no plano
        glPushMatrix();//Matriz de giro
        
        glRotatef(t, 0, 1, 0);
        
        //centro do avião
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 0.7);
        glVertex3d(-2, -15,0.0f);
        glVertex3d(-2, 15,0.0f);
        glVertex3d(2, 15,0.0f);
        glVertex3d(2, -15,0.0f);
        glEnd();
        printf("%d", translMapa);

        //asa direita inferior

        glBegin(GL_POLYGON);
        if (t < 0) {
            glColor3f(0.6, 0.6, 0.7);
        }
        else {
            glColor3f(1, 1, 0.7);

        }
        glVertex3f(2, -12,0);
        glVertex3f(6, -12,0);
        glVertex3f(6, -15,0);
        glVertex3f(10, -15,0);
        glVertex3f(10, -12,0);
        glVertex3f(6, -12,0);
        glVertex3f(6, -10,0);
        glVertex3f(2, -10,0);
        glEnd();

        //asa direita superior 
        glBegin(GL_POLYGON);
        glVertex3f(2, 0, 0);
        glVertex3f(18, -5, 0);
        glVertex3f(14, 0, 0);
        glVertex3f(2, 10, 0);
        glVertex3f(2, 0, 0);
        glEnd();

    
        //asa esqueda inferior 

        glBegin(GL_POLYGON);
        if (t > 0) {
            glColor3f(0.6, 0.6, 0.7);

        }
        else {
            glColor3f(1, 1, 0.7);

        }
        glVertex3f(-2, -12,0);
        glVertex3f(-6, -12,0);
        glVertex3f(-6, -15,0);
        glVertex3f(-10, -15,0);
        glVertex3f(-10, -12,0);
        glVertex3f(-6, -12,0);
        glVertex3f(-6, -10,0);
        glVertex3f(-2, -10,0);
        glEnd();





        //asa esquerda superior 
        glBegin(GL_POLYGON);
        glVertex3f(-2, 0,0);
        glVertex3f(-18, -5,0);
        glVertex3f(-14, 0,0);
        glVertex3f(-2, 10,0);
        glVertex3f(-2, 0,0);
        glEnd();
        
        glPopMatrix();//matriz de giro

        glPopMatrix();



    }
    static void desenharProjetil(){
        
        if (!teste|| !rota) {
            xy_Shoot[1] = player_posY;
            xy_Shoot[0] = player_posX;
            rota = true;

        }else {

                    glPushMatrix();
                    glLineWidth(3);
                    glTranslated(xy_Shoot[0], xy_Shoot[1], 0);

                    glBegin(GL_LINES);
                    glColor3f(1, 1, 1);
                        glVertex3f(-1.5, 10,0);
                        glVertex3f(-1.5, 0,0);
                        xy_Shoot[1]+=6;
                        printf("%i",xy_Shoot[1]);
                    glEnd();
                    glPopMatrix();
            
        }
        
    }
};
void desenhar() {
    glPushMatrix();
    glLoadIdentity();
    glScalef(0.0025, 0.0025, 0.0025);
    Jogador::desenharP1();
    glBegin(GL_LINES);
    glColor3f(1,0.5,0.5);
    glVertex2f(-400,0);
    glVertex2f(400,0);
    glEnd();
   translMapa += 1;
   glTranslatef(0, -translMapa, 0);
    Mapa::DesenharParede();
    glPopMatrix();
 
}

void keyboard()
{

    if (GetAsyncKeyState('W') != 0) {
        if (player_posY < 385) {
            player_posY += 2;
            
        }
    }
    if (GetAsyncKeyState('A') != 0) {
        if (player_posX > -380) {
            player_posX -= 2;
            t = 30;
        }
        
    }else if (GetAsyncKeyState('D') != 0) {
        if (player_posX < 380) {
            player_posX += 2;
        }
        t = -30;
    }
    else {
        t = 0;
    }
    if (GetAsyncKeyState('S') != 0) {
        if (player_posY > -385) {
            player_posY -= 2;
        }
    }
    
    shoot = (GetAsyncKeyState(0x20) != 0) ? TRUE : FALSE;

    glutPostRedisplay();
}