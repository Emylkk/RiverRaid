#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <thread>
#include<ntddbeep.h>
#include<iostream>
#include<string>
#include<locale>

#define janela_altura  800
#define janela_largura 800
const  int Y = 1;
const int X = 0;
//pontos
int pontuacao = 0;
unsigned char pontos[20] = {"0"};
int combustivel = 200;
//Variaveis de animação
int t = 0, animaHelice = 0;
bool dead = false;
bool striked = false;
bool refill = false;
bool started = false;
int girar=0;
int animaexplosao=0;
bool nimeexpl = false;
int lastExplosion[2] = { 0,0 };

//Vetor de Inimigos
int inimigosVet[2][20] = {
	23,     -50,    220,    -220,       0,      50,      50,     150,    50,     -100,   10,     200,    -240,   0,      0,      0,      0,    -10,  -10,    0,
	450,    1100,    1800,    1700,    2000,    2500,    3200,    6200,   6800,   7400,  650,   1700,   1800,   2700,   3000,   4000,   4100,  6300, 6800, 7000
};
//Vetor de Combustiveis
int gasolinaVet[2][8] = {
	50	,0		,0		,0		,0		,0		,0		,0,
	1100,2000	,3200	,4500	,5000	,6500	,7000	,7500
};
//Ilhas
int ilhasYDim[2][3]{
	1550,3300,5500,
	175,100,200
};
//dimensões de metade dos objetos- Inicio
int tamPlayerXY[2] = { 18,15 };
int tamHelicopteroXY[2] = { 38,18 };
int tamNavioXY[2] = { 45,12 };

//Posicionamento 
int mod = 400, translMapa = 0, posicao_relativaY = 0, distanciaMapa = -400, paredeAtual = 0, posicao_relativaYshoot = 0;
//Posicionamento do Jogador 
float player_posX = 0, player_posY = 20;

// Larguras de Paredes laterais
int x[10]{ 20, 100, 300, 150, 250, 100, 30, 300, 200, 350 };

//Posição do tiro
int xy_Shoot[2] = { 0,0 };
bool rota = false;
bool shoot = false, teste = false;

//Funcões
void reshape(GLsizei w, GLsizei h);
void keyboard();
void display(void);
void desenhar();
void restart();
bool colisao();
//Testes
const unsigned char menu[] = { "Aperte Espaco Para Iniciar" };
using namespace std;
void menuDraw(){
	glPushMatrix();
	glLoadIdentity();
	glScalef(0.0025, 0.0025, 0.0025);
	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0.5);
	glVertex3f(-janela_largura/2,-janela_altura/2,0);
	glVertex3f(-janela_largura/2,janela_altura/2,0);
	glVertex3f(janela_largura/2,janela_altura/2,0);
	glVertex3f(janela_largura/2,-janela_altura/2,0);
	glEnd();
	//Texto
	glColor3f(0.8,0.8,1);
	glRasterPos3i(-150,-300,-1);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, menu);
	//fundo
	glPushMatrix();
	glRotatef(girar,1,0.51,1);
		glColor3b(1, 1, 1);
		glutWireSphere(100, 40, 10);
	glPopMatrix();
	girar++;
	if (girar > 360) {
		girar = 0;
	}
	glPopMatrix();
	glFlush(); // executa o desenho
	glutSwapBuffers();
}
class Inimigos {
public:
	Inimigos();
	~Inimigos();
	//explosao dos inimigos 
	static void explosao(int x, int y) {
		glPushMatrix();
		glTranslatef(x, y, 0);

		glBegin(GL_LINES);
		if (!nimeexpl) {
		lastExplosion[X] = x;
		lastExplosion[Y] = y;
	}
		nimeexpl = true;
		animaexplosao++;
		if (animaexplosao == 20) {
			animaexplosao = -10;
			nimeexpl = false;
		}
		if (animaexplosao < 0) {
			//explosao branca
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(-18, 10, 1);
			glVertex3f(-14, 10, 1);

			glVertex3f(-10, -10, 1);
			glVertex3f(-6, -10, 1);

			glVertex3f(-4, 0, 1);
			glVertex3f(-0, 0, 1);

			//explosao vermelho
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-14, 9, 1);
			glVertex3f(-10, 9, 1);

			glVertex3f(18, -10, 1);
			glVertex3f(14, -10, 1);

			glVertex3f(18, 10, 1);
			glVertex3f(14, 10, 1);

			//explosa bege
			glColor3f(1.0, 1.0, 0.3);
			glVertex3f(-18, 0, 1);
			glVertex3f(-14, 0, 1);

			glVertex3f(-10, 5, 1);
			glVertex3f(-6, 5, 1);

			glVertex3f(4, -6, 1);
			glVertex3f(8, -6, 1);

		}
		else if (animaexplosao > 0 && animaexplosao < 10)
		{
			//explosao branca
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(18, -10, 1);
			glVertex3f(14, -10, 1);

			glVertex3f(10, 10, 1);
			glVertex3f(6, 10, 1);

			glVertex3f(4, 0, 1);
			glVertex3f(0, 0, 1);

			//explosao vermelho
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(14, -9, 1);
			glVertex3f(10, -9, 1);

			glVertex3f(-18, 10, 1);
			glVertex3f(-14, 10, 1);

			glVertex3f(-18, -10, 1);
			glVertex3f(-14, -10, 1);


			//explosa bege
			glColor3f(1.0, 1.0, 0.3);
			glVertex3f(18, 0, 1);
			glVertex3f(14, 0, 1);

			glVertex3f(10, -5, 1);
			glVertex3f(6, -5, 1);

			glVertex3f(-4, 6, 1);
			glVertex3f(-8, 6, 1);
		}

		else if (animaexplosao > 10)
		{
			//explosao branca
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(-18, 10, 1);
			glVertex3f(-14, 10, 1);

			glVertex3f(-10, -10, 1);
			glVertex3f(-6, -10, 1);

			glVertex3f(-4, 0, 1);
			glVertex3f(-0, 0, 1);

			//explosao vermelho
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-14, 9, 1);
			glVertex3f(-10, 9, 1);

			glVertex3f(18, -10, 1);
			glVertex3f(14, -10, 1);

			glVertex3f(18, 10, 1);
			glVertex3f(14, 10, 1);

			//explosa bege
			glColor3f(1.0, 1.0, 0.3);
			glVertex3f(-18, 0, 1);
			glVertex3f(-14, 0, 1);

			glVertex3f(-10, 5, 1);
			glVertex3f(-6, 5, 1);

			glVertex3f(4, -6, 1);
			glVertex3f(8, -6, 1);
		}



		glEnd();


		glPopMatrix();

	}
	static void desenharNavio() {



		for (size_t i = 0; i < 10; i++) {
			glPushMatrix();

			glTranslatef(inimigosVet[X][i], inimigosVet[Y][i], 0);

			//parte de baixo do barco


			glBegin(GL_POLYGON);
			glColor3f(0, 0.7, 0.9);
			glVertex2d(-31, -15);
			glVertex2d(22, -15);
			glVertex2d(42, -9);
			glVertex2d(-45, -9);
			glEnd();

			//parte do meio do barco 
			glBegin(GL_POLYGON);
			glColor3f(0.75, 0, 0);
			glVertex2d(-42, -9);
			glVertex2d(42, -9);
			glVertex2d(42, -2);
			glVertex2d(-45, -2);
			glEnd();

			//parte de cima do barco
			glBegin(GL_QUADS);
			glColor3f(0.0, 0.0, 0.0);
			//parte inferior
			glVertex2d(-23, -2);
			glVertex2d(23, -2);
			glVertex2d(23, 4);
			glVertex2d(-23, 4);

			//parte chamine
			glVertex2d(-5, -2);
			glVertex2d(15, -2);
			glVertex2d(15, 12);
			glVertex2d(-5, 12);
			glEnd();

			glPopMatrix();
		}
	}


public:
	static void desenharHeli() {

		for (size_t i = 10; i < 19; i++) {
			glPushMatrix();

			glTranslatef(inimigosVet[X][i], inimigosVet[Y][i], 0);


			//base do heli
			glBegin(GL_POLYGON);
			glColor3f(0.0, 0.6, 0.0);
			glVertex2d(20, -13);
			glVertex2d(28, -10);
			glVertex2d(7, -10);
			glVertex2d(14, -13);
			glVertex2d(10, -18);
			glVertex2d(24, -18);
			glEnd();

			//parte de tras do heli
			glBegin(GL_QUADS);
			glColor3f(0.0, 0.5, 1.0);
			glVertex2f(-22, -14);
			glVertex2f(-30, -14);
			glVertex2f(-30, 4);
			glVertex2f(-22, 4);
			glEnd();


			//parte do meio do heli
			glBegin(GL_QUADS);
			glColor3f(0.0, 0.0, 0.4);
			glVertex2f(30, -10);
			glVertex2f(-30, -10);
			glVertex2f(-30, 0);
			glVertex2f(30, 0);
			glEnd();


			//teto do heli
			glBegin(GL_QUADS);
			glColor3f(0.0, 0.0, 0.3);
			glVertex2f(30, 0);
			glVertex2f(0, 0);
			glVertex2f(0, 6);
			glVertex2f(30, 6);

			glEnd();

			//pilar da helice 
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 0.5);
			glVertex2f(22, 6);
			glVertex2f(12, 6);
			glVertex2f(12, 12);
			glVertex2f(22, 12);
			glEnd();

			animaHelice++;
			if (animaHelice == 10) {
				animaHelice = -10;
			}

			//primeira parte da helice 
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 0.5);
			if (animaHelice < 0) {
				glVertex2f(14, 13);
				glVertex2f(38, 13);
				glVertex2f(38, 18);
				glVertex2f(14, 18);
			}
			else if (animaHelice > 0)
			{
				glVertex2f(14, 9);
				glVertex2f(38, 9);
				glVertex2f(38, 14);
				glVertex2f(14, 14);
			}

			glEnd();

			//segunda parte da helice 
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 0.5);
			if (animaHelice < 0) {
				glVertex2f(22, 9);
				glVertex2f(-2, 9);
				glVertex2f(-2, 14);
				glVertex2f(22, 14);
			}
			else if (animaHelice > 0)
			{
				glVertex2f(22, 13);
				glVertex2f(-2, 13);
				glVertex2f(-2, 18);
				glVertex2f(22, 18);
			}
			glEnd();

			glPopMatrix();
		}
	}
};
void som() {
	while (true) {
		Sleep(10);

		if (refill) {
			for (size_t i = 10; i < 1000; i += 150)
			{
				Beep(i, 15);
			}
		}
		if (dead) {
			Beep(100, 300);

		}
		if (striked) {
			Beep(BEEP_FREQUENCY_MINIMUM, 30);
			Beep(BEEP_FREQUENCY_MINIMUM, 35);
			Beep(BEEP_FREQUENCY_MINIMUM, 85);
		}
	}
}
void  main(int argc, char** argv)
{
	thread ts(som);
	setlocale(LC_ALL, "Portuguese");
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA
	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(50, 50); // Pos. onde surge a janela
	glutCreateWindow("GLUT");   /// cria a janela
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	ts.join();
}

bool colisao() {

	///Se a Posicao Atual do jogador alcançar a altura de troca de parede "limite de 6"
	if ((((posicao_relativaY % mod >= 0) && (posicao_relativaY % mod <= 6)) && posicao_relativaY > 6)) {
		paredeAtual++;
		mod += 800;
		printf("%i Parede", paredeAtual);
	}
	//paredes à esquerda

	if (player_posX - tamPlayerXY[X] < (-x[paredeAtual])) {
		dead = true;
		Inimigos::explosao(player_posX, posicao_relativaY);

		restart();

	}
	//Paredes à Direita

	if (player_posX + tamPlayerXY[X] > (x[paredeAtual])) {
		dead = true;
		Inimigos::explosao(player_posX, posicao_relativaY);
		restart();

	}
	for (size_t i = 0; i < 10; i++)
	{
		if ((posicao_relativaY + tamPlayerXY[Y] >= inimigosVet[Y][i] - tamNavioXY[Y]) && (posicao_relativaY - tamPlayerXY[Y] < inimigosVet[Y][i] + tamNavioXY[Y]) && (player_posX - tamPlayerXY[X] <= inimigosVet[X][i] + tamNavioXY[X]) && (player_posX + tamPlayerXY[X] >= inimigosVet[X][i] - tamNavioXY[X])) {
			xy_Shoot[X] = 0;
			xy_Shoot[Y] = 0;
			restart();
			dead = true;
		}

	}
	for (size_t i = 10; i < 20; i++)
	{
		if ((posicao_relativaY + tamPlayerXY[Y] >= inimigosVet[Y][i] - tamHelicopteroXY[Y]) && (posicao_relativaY - tamPlayerXY[Y] < inimigosVet[Y][i] + tamHelicopteroXY[Y]) && (player_posX - tamPlayerXY[X] <= inimigosVet[X][i] + tamHelicopteroXY[X]) && (player_posX + tamPlayerXY[X] >= inimigosVet[X][i] - tamHelicopteroXY[X])) {
			xy_Shoot[X] = 0;
			xy_Shoot[Y] = 0;
			restart();
			dead = true;
		}

	}
	for (size_t i = 0; i < 8; i++)
	{
		if ((posicao_relativaY + tamPlayerXY[Y] >= gasolinaVet[Y][i] - 15) && (posicao_relativaY - tamPlayerXY[Y] < gasolinaVet[Y][i] + 15) && (player_posX - tamPlayerXY[X] <= gasolinaVet[X][i] + 15) && (player_posX + tamPlayerXY[X] >= gasolinaVet[X][i] - 15)) {
			xy_Shoot[X] = 0;
			xy_Shoot[Y] = 0;
			gasolinaVet[Y][i] = -500;
			refill = true;
		}

	}
	for (size_t i = 0; i < 3; i++)
	{
		if ((posicao_relativaY + tamPlayerXY[Y] >= ilhasYDim[0][i] - ilhasYDim[1][i]) && (posicao_relativaY - tamPlayerXY[Y] < ilhasYDim[0][i] + ilhasYDim[1][i]) && (player_posX - tamPlayerXY[X] <= 0 + ilhasYDim[1][i]) && (player_posX + tamPlayerXY[X] >= 0 - ilhasYDim[1][i])) {
			xy_Shoot[X] = 0;
			xy_Shoot[Y] = 0;
			restart();
			dead = true;
		}

	}
	return(false);
}

void reshape(GLsizei w, GLsizei h)
{
	if (h == 0) h = 1; // previne a divisão por zero
	GLfloat aspecto = (GLfloat)w / (GLfloat)h; glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION);// manipulando matriz de projeção
	glLoadIdentity(); // zerando a matriz
	gluPerspective(0.0f, aspecto, -10.0f, 10.0f);
	glClearColor(0.0f, 0.0f, 0.7f, 1.0f); // configura fundo sem transparencia
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH); // acabamento com suavização
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva
}

//gasolina
static class objeto {
public:
	static void galaoGasolina() {
		if(nimeexpl){
			Inimigos::explosao(lastExplosion[X],lastExplosion[Y]);
		}
		for (size_t i = 0; i < 8; i++) {
			char parte1 = 'L';
			char parte2 = 'E';
			char parte3 = 'U';
			char parte4 = 'F';

			glPushMatrix();
			glTranslatef(gasolinaVet[X][i], gasolinaVet[Y][i], 0);

			//parte 1 de 4

			glColor3f(0, 0, 0);

			glRasterPos3f(-7, -37, -1);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, parte1);

			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(-15, -40, 0);
			glVertex3f(15, -40, 0);
			glVertex3f(15, -20, 0);
			glVertex3f(-15, -20, 0);
			glEnd();

			//parte 2 de 4

			glColor3f(0, 0, 0);
			glRasterPos3f(-7, -17, -1);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, parte2);

			glBegin(GL_QUADS);
			glColor3f(0.7, 0.0, 0.0);
			glVertex3f(-15, -20, 0);
			glVertex3f(15, -20, 0);
			glVertex3f(15, 0, 0);
			glVertex3f(-15, 0, 0);
			glEnd();

			//parte 3 de 4

			glColor3f(0, 0, 0);
			glRasterPos3f(-7, 3, -1);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, parte3);

			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(-15, 0, 0);
			glVertex3f(15, 0, 0);
			glVertex3f(15, 20, 0);
			glVertex3f(-15, 20, 0);
			glEnd();

			//parte 4 de 4

			glColor3f(0, 0, 0);
			glRasterPos3f(-7, 23, -1);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, parte4);

			glBegin(GL_QUADS);
			glColor3f(0.7, 0.0, 0.0);
			glVertex3f(-15, 20, 0);
			glVertex3f(15, 20, 0);
			glVertex3f(15, 40, 0);
			glVertex3f(-15, 40, 0);
			glEnd();
			glPopMatrix();
		}
	}
};

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	posicao_relativaY = translMapa + player_posY;
	keyboard();
	if (started) {
		colisao();
		desenhar();
		glFlush(); // executa o desenho
		glutSwapBuffers();
		dead = false;
		striked = false;
		refill = false;
	}
	else {
		menuDraw();
	}
}

static class Mapa {
public:
	static void translacaoVertical() {
		translMapa += 1;
		glTranslatef(0, -translMapa, 0);
	}
	static void desenharParede() {

		glPushMatrix();
		Inimigos::desenharNavio();
		Inimigos::desenharHeli();
		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);
		for (size_t i = 0; i < 10; i++)
		{
			//Parede Direita
			glVertex3f(x[i], distanciaMapa, 0);//esquerda abaixo
			glVertex3f(x[i], distanciaMapa + 800, 0);//subir na esquerda ↑
			glVertex3f(400, distanciaMapa + 800, 0);//direita acima
			glVertex3f(400, distanciaMapa, 0);//direita ↓
			//Parede Esquerda
			glVertex3f(-x[i], distanciaMapa, 0);//esquerda abaixo
			glVertex3f(-x[i], distanciaMapa + 800, 0);//subir na esquerda ↑
			glVertex3f(-400, distanciaMapa + 800, 0);//direita acima
			glVertex3f(-400, distanciaMapa, 0);//direita ↓

			if (x[i] <= 30) {
				//PonteDireita

				glColor3f(.5, .5, .5);
				glVertex3f(x[i], distanciaMapa+350, -1);//esquerda abaixo
				glVertex3f(x[i], distanciaMapa + 450, -1);//subir na esquerda ↑
				glVertex3f(400, distanciaMapa + 450, -1);//direita acima
				glVertex3f(400, distanciaMapa+350, -1);//direita ↓
							//Ponte Esquerda
				glVertex3f(-x[i], distanciaMapa+350, -1);//esquerda abaixo
				glVertex3f(-x[i], distanciaMapa + 450, -1);//subir na esquerda ↑
				glVertex3f(-400, distanciaMapa + 450, -1);//direita acima
				glVertex3f(-400, distanciaMapa+350, -1);//direita ↓
			}
			glColor3f(0, 0.8, 0);

			distanciaMapa += 800;

		}
		distanciaMapa = -400;
		glEnd();
		//Parede Esquerda
		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);


		for (size_t i = 0; i < 10; i++)
		{

			distanciaMapa += 800;
		}
		glEnd();

		glPopMatrix();
		distanciaMapa = -400;

	}
	static void ilha1() {
		//ilha 2
		glPushMatrix();
		glTranslatef(0, 1550, 0);

		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);
		glVertex3f(-175, -175, 0);
		glVertex3f(175, -175, 0);
		glVertex3f(175, 175, 0);
		glVertex3f(-175, 175, 0);
		glEnd();

		glPopMatrix();

	}
	//ilha 2
	static void ilha2() {
		glPushMatrix();
		glTranslatef(0, 3300, 0);

		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);
		glVertex3f(-100, -100, 0);
		glVertex3f(100, -100,0 );
		glVertex3f(100, 100, 0);
		glVertex3f(-100, 100, 0);
		glEnd();

		glPopMatrix();

	}
	//ilha 3
	static void ilha3() {
		glPushMatrix();
		glTranslatef(0, 5500, 0);

		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);
		glVertex3f(-200, -200, 0);
		glVertex3f(200, -200, 0);
		glVertex3f(200, 200, 0);
		glVertex3f(-200, 200, 0);
		glEnd();

		glPopMatrix();

	}
};

bool tirosValidar() {
	bool teste = true;
	if (xy_Shoot[X] > (x[paredeAtual])) {
		xy_Shoot[X] = 0;
		xy_Shoot[Y] = 0;
		rota = false;
		striked = true;

	}
	if (xy_Shoot[X] != 0 || xy_Shoot[Y] != 0) {
		for (size_t i = 0; i < 10; i++)
		{
			if ((xy_Shoot[Y] + translMapa >= inimigosVet[Y][i] - tamNavioXY[Y]) && (xy_Shoot[Y] + translMapa < inimigosVet[Y][i] + tamNavioXY[Y]) && (xy_Shoot[X] <= inimigosVet[X][i] + tamNavioXY[X]) && (xy_Shoot[X] >= inimigosVet[X][i] - tamNavioXY[X])) {
				xy_Shoot[X] = 0;
				xy_Shoot[Y] = 0;
				rota = false;
				Inimigos::explosao(inimigosVet[X][i], inimigosVet[Y][i]);
				inimigosVet[Y][i] = -500;
				striked = true;
			}

		}
		for (size_t i = 10; i < 20; i++)
		{
			if ((xy_Shoot[Y] + translMapa >= inimigosVet[Y][i] - tamHelicopteroXY[Y]) && (xy_Shoot[Y] + translMapa < inimigosVet[Y][i] + tamHelicopteroXY[Y]) && (xy_Shoot[X] <= inimigosVet[X][i] + tamHelicopteroXY[X]) && (xy_Shoot[X] >= inimigosVet[X][i] - tamHelicopteroXY[X])) {
				xy_Shoot[X] = 0;
				xy_Shoot[Y] = 0;
				rota = false;
				Inimigos::explosao(inimigosVet[X][i], inimigosVet[Y][i]);
				inimigosVet[Y][i] = -500;
				striked = true;
			}

		}
		for (size_t i = 0; i < 3; i++)
		{
			if ((xy_Shoot[Y] + translMapa >= ilhasYDim[0][i] - ilhasYDim[1][i]) && (xy_Shoot[Y] + translMapa < ilhasYDim[0][i] + ilhasYDim[1][i]) && (xy_Shoot[X] <= 0 + ilhasYDim[1][i]) && (xy_Shoot[X] >= 0 - ilhasYDim[1][i])) {
				xy_Shoot[X] = 0;
				xy_Shoot[Y] = 0;
				rota = false;
				Inimigos::explosao(player_posX,posicao_relativaY);
				inimigosVet[Y][i] = -500;
				striked = true;
			}

		}
	}
	//Zera os tiros que sumiram ou colidiram
	if (xy_Shoot[Y] > janela_altura / 2) {
		xy_Shoot[X] = 0;
		xy_Shoot[Y] = 0;
		rota = false;

	}
	//testa se todos os tiros cessaram
	if ((xy_Shoot[X] == 0) && (xy_Shoot[Y] == 0)) {
		teste = false;
		rota = false;
	}

	return(teste);

}

static class Jogador {
	Jogador();
	~Jogador();
public:
	static void hud() {
		//Hud
		glPushMatrix();
		//Pontos
			glPushMatrix();
			glColor3f(0.8, 0.8, 1);
			glRasterPos3i(-380, -350, -3);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,pontos);
			glBegin(GL_QUADS);
			
				glColor3f(0.4,0.4,0.4);
				glVertex3f(-400,-300,-2);
				glVertex3f(	400,-300,-2);
				glVertex3f(	400,-400,-2);
				glVertex3f(-400,-400,-2);

			glEnd();
			glPopMatrix();
		//Gasolina
			glPushMatrix();
				glPushMatrix();

				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	static void desenharP1() {

		glPushMatrix();//Matriz de movimentação
		teste = tirosValidar();

		if (shoot or rota) {

			Jogador::desenharProjetil();

		}
		glTranslatef(player_posX, player_posY, 0);//realoca a matriz no plano
		glPushMatrix();//Matriz de giro

		glRotatef(t, 0, 1, 0);

		//centro do avião
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 0.7);
		glVertex3d(-2, -15, 0.0f);
		glVertex3d(-2, 15, 0.0f);
		glVertex3d(2, 15, 0.0f);
		glVertex3d(2, -15, 0.0f);
		glEnd();

		//asa direita inferior

		glBegin(GL_POLYGON);
		if (t < 0) {
			glColor3f(0.6, 0.6, 0.7);
		}
		else {
			glColor3f(1, 1, 0.7);

		}
		glVertex3f(2, -12, 0);
		glVertex3f(6, -12, 0);
		glVertex3f(6, -15, 0);
		glVertex3f(10, -15, 0);
		glVertex3f(10, -12, 0);
		glVertex3f(6, -12, 0);
		glVertex3f(6, -10, 0);
		glVertex3f(2, -10, 0);
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
		glVertex3f(-2, -12, 0);
		glVertex3f(-6, -12, 0);
		glVertex3f(-6, -15, 0);
		glVertex3f(-10, -15, 0);
		glVertex3f(-10, -12, 0);
		glVertex3f(-6, -12, 0);
		glVertex3f(-6, -10, 0);
		glVertex3f(-2, -10, 0);
		glEnd();
		//asa esquerda superior 
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 0);
		glVertex3f(-18, -5, 0);
		glVertex3f(-14, 0, 0);
		glVertex3f(-2, 10, 0);
		glVertex3f(-2, 0, 0);
		glEnd();

		glPopMatrix();//matriz de giro
		glPopMatrix();



	}
	static void desenharProjetil() {

		if (!teste || !rota) {
			xy_Shoot[1] = player_posY;
			xy_Shoot[0] = player_posX;
			rota = true;

		}
		else {

			glPushMatrix();
			glLineWidth(3);
			glTranslated(xy_Shoot[0], xy_Shoot[1], 0);

			glBegin(GL_LINES);
			glColor3f(1, 1, 1);
			glVertex3f(-1.5, 10, 0);
			glVertex3f(-1.5, 0, 0);
			xy_Shoot[1] += 6;
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
	Jogador::hud();
	Mapa::translacaoVertical();
	Mapa::desenharParede();
	Mapa::ilha1();
	Mapa::ilha2();
	Mapa::ilha3();
	objeto::galaoGasolina();
	glPopMatrix();

}

void keyboard()
{
	if (started) {
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

		}
		else if (GetAsyncKeyState('D') != 0) {
			if (player_posX < 380) {
				player_posX += 2;
			}
			t = -30;
		}
		else {
			t = 0;
		}
		if (GetAsyncKeyState('S') != 0) {
			if (player_posY > -285) {
				player_posY -= 1;
			}
		}

		shoot = (GetAsyncKeyState(0x20) != 0) ? TRUE : FALSE;
	}
	else {
		started = (GetAsyncKeyState(0x20) != 0) ? TRUE : FALSE;
	}
	glutPostRedisplay();
}

void restart() {
	translMapa = 0;
	posicao_relativaY = 0;
	player_posX = 0;
	player_posY = 0;
	paredeAtual = 0;
	mod = 400;
}