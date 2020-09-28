#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <math.h>
#include<iostream>

#define janela_altura  800
#define janela_largura 800

int t = 0, animaHelice=0;
//dimensões x de metade dos objetos- Inicio
int tamPlayer = 18;
int tamHelicoptero = 38;
int tamNavio = 45;
//fim dimensoes

//Posicionamento
float player_posX = 0, player_posY = 20;
int translMapa = 0, posicao_relativaY = 0, distanciaMapa = -400, paredeAtual=0;
//Fim Posicionamento

// Larguras de Paredes laterais
int x[10]{ 20, 100, 300, 150, 250, 100, 30, 300, 200, 350 };
//Posição do tiro
int xy_Shoot[2]= {0,0};
bool rota = false;
bool shoot = false;

void reshape(GLsizei w, GLsizei h);
void keyboard();
void display(void);
void desenhar();
void colisao();
const unsigned char tete[] = { "Marine" };

class Inimigos {
public:
    Inimigos();
    ~Inimigos();
    int inimigosVet[10][10] = {};
    static void desenharNavio() {
        glPushMatrix();
        glTranslatef(-50, 70, 0);


        //parte de baixo do barco
        glColor3f(0, 0, 0);
        glRasterPos3f(-20, 0, 0);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10,tete);

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

        animaHelice++;
        if (animaHelice == 10) {
            animaHelice = -10;
        }

        //primeira parte da helice 
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.5);
        if (animaHelice < 0) {
            glVertex2f(14, 27);
            glVertex2f(38, 27);
            glVertex2f(38, 32);
            glVertex2f(14, 32);
        }
        else if (animaHelice > 0)
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
        if (animaHelice < 0) {
            glVertex2f(22, 23);
            glVertex2f(-2, 23);
            glVertex2f(-2, 28);
            glVertex2f(22, 28);
        }
        else if (animaHelice > 0)
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
    
    ///Se a Posicao Atual do jogador alcançar a altura de troca de parede
    if ((posicao_relativaY) % 400 == 0 && posicao_relativaY > 0) {
        paredeAtual++;
        printf("%i Parede", paredeAtual);
    }
    if ( true) {

    }
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
    posicao_relativaY = translMapa + player_posY;
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
        Inimigos::desenharNavio();
        Inimigos::desenharHeli();
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
            xy_Shoot[0] = 0;
            xy_Shoot[1] = 0;
            rota = false;

        }
        //testa se todos os tiros cessaram
        if ((xy_Shoot[0] == 0) && (xy_Shoot[1] == 0)) {
            teste = false;
            rota = false;
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
            player_posY -= 1;
        }
    }
    colisao();
    shoot = (GetAsyncKeyState(0x20) != 0) ? TRUE : FALSE;

    glutPostRedisplay();
}
