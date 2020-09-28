#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <math.h>
#include <thread>
#include<iostream>

#define janela_altura  800
#define janela_largura 800
const  int Y = 1;
const int X = 0;
//Variaveis de animação
int t = 0, animaHelice = 0;

//Vetor de Inimigos
int inimigosVet[2][20] = {
	23,     -50,    220,    -220,       0,      50,      50,     150,    50,     -100,   0,     200,    -240,   0,      0,      0,      0,    -10,  -10,    0,
	450,    1100,    1800,    1700,    2000,    2500,    3200,    6200,   6800,   7400,  500,   1700,   1800,   2700,   3000,   4000,   4100,  6300, 6800, 7000
};
//Vetor de Combustiveis
int gasolinaVet[2][8] = {
	50	,0		,0		,0		,0		,0		,0		,0,
	1100,2000	,3200	,4500	,5000	,6500	,7000	,7500
};

//dimensões de metade dos objetos- Inicio
int tamPlayerXY[2] = { 18,15 };
int tamHelicopteroXY[2] = { 38, };
int tamNavioXY[2] = { 45,1 };

//Posicionamento 
int mod = 400, translMapa = 0, posicao_relativaY = 0, distanciaMapa = -400, paredeAtual = 0;
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
const unsigned char tete[] = { "Marine" };

class Inimigos {
public:
	Inimigos();
	~Inimigos();
	static void desenharNavio() {



		for (size_t i = 0; i < 10; i++) {
			glPushMatrix();

			glTranslatef(inimigosVet[X][i], inimigosVet[Y][i], 0);

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
	}


public:
	static void desenharHeli() {

		for (size_t i = 10; i < 19; i++) {
			glPushMatrix();

			glTranslatef(inimigosVet[X][i], inimigosVet[Y][i], 0);


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
	}
};

void  main(int argc, char** argv)
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
}

bool colisao() {

	///Se a Posicao Atual do jogador alcançar a altura de troca de parede "razão de 6"
	if ((((posicao_relativaY % mod >= 0) && (posicao_relativaY % mod <= 6)) && posicao_relativaY > 6)) {
		paredeAtual++;
		mod += 800;
		printf("%i Parede", paredeAtual);
	}
	//paredes à esquerda
	if (player_posX - tamPlayerXY[X] < (-x[paredeAtual])) {
		Beep(100, 2000);
		restart();
	}
		//Paredes à Direita
	if (player_posX + tamPlayerXY[X] > (x[paredeAtual])) {
		Beep(100, 2000);
		restart();
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

		for (size_t i = 0; i < 8; i++) {
			char parte1 = 'L';
			char parte2 = 'E';
			char parte3 = 'U';
			char parte4 = 'F';

			glPushMatrix();
			glTranslatef(gasolinaVet[X][i], gasolinaVet[Y][i], 0);

			//parte 1 de 4

			glColor3f(0, 0, 0);
			glRasterPos3f(7, 1, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, parte1);

			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(0, 0, 0);
			glVertex3f(30, 0, 0);
			glVertex3f(30, 20, 0);
			glVertex3f(0, 20, 0);
			glEnd();

			//parte 2 de 4

			glColor3f(0, 0, 0);
			glRasterPos3f(7, 21, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, parte2);

			glBegin(GL_QUADS);
			glColor3f(0.7, 0.0, 0.0);
			glVertex3f(0, 20, 0);
			glVertex3f(30, 20, 0);
			glVertex3f(30, 40, 0);
			glVertex3f(0, 40, 0);
			glEnd();

			//parte 3 de 4

			glColor3f(0, 0, 0);
			glRasterPos3f(7, 41, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, parte3);

			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(0, 40, 0);
			glVertex3f(30, 40, 0);
			glVertex3f(30, 60, 0);
			glVertex3f(0, 60, 0);
			glEnd();

			//parte 4 de 4

			glColor3f(0, 0, 0);
			glRasterPos3f(7, 61, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, parte4);

			glBegin(GL_QUADS);
			glColor3f(0.7, 0.0, 0.0);
			glVertex3f(0, 60, 0);
			glVertex3f(30, 60, 0);
			glVertex3f(30, 80, 0);
			glVertex3f(0, 80, 0);
			glEnd();
			glPopMatrix();
		}
	}
};

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	posicao_relativaY = translMapa + player_posY;
	colisao();
	keyboard();
	desenhar();
	glFlush(); // executa o desenho
	glutSwapBuffers();
}

static class Mapa {
public:
	static void translacaoVertical() {
		translMapa += 1;
		glTranslatef(0, -translMapa, 0);
	}
	static void desenharParede() {
		
		glPushMatrix();
		//Parede Direita
		Inimigos::desenharNavio();
		Inimigos::desenharHeli();
		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);
		for (size_t i = 0; i < 10; i++)
		{
			glVertex3f(x[i], distanciaMapa, 0);//esquerda abaixo
			glVertex3f(x[i], distanciaMapa + 800, 0);//subir na esquerda ↑
			glVertex3f(400, distanciaMapa + 800, 0);//direita acima
			glVertex3f(400, distanciaMapa, 0);//direita ↓

			distanciaMapa += 800;
		}
		distanciaMapa = -400;
		glEnd();
		//Parede Esquerda
		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);


		for (size_t i = 0; i < 10; i++)
		{
			glVertex3f(-x[i], distanciaMapa, 0);//esquerda abaixo
			glVertex3f(-x[i], distanciaMapa + 800, 0);//subir na esquerda ↑
			glVertex3f(-400, distanciaMapa + 800, 0);//direita acima
			glVertex3f(-400, distanciaMapa, 0);//direita ↓

			distanciaMapa += 800;
		}
		glEnd();

		glPopMatrix();
		distanciaMapa = -400;

	}
	static void ilha1() {
		//ilha 2
		glPushMatrix();
		glTranslatef(-150, 1400, 0);

		glBegin(GL_QUADS);
		glColor3f(0, 0.8, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(350, 0, 0);
		glVertex3f(350, 350, 0);
		glVertex3f(0, 350, 0);
		glEnd();

		glPopMatrix();

	}
	//ilha 2
	static void ilha2() {
		glPushMatrix();
		glTranslatef(-100, 3300, 0);

		glBegin(GL_QUADS);
			glColor3f(0, 0.8, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(200, 0, 0);
			glVertex3f(200, 200, 0);
			glVertex3f(0, 200, 0);
		glEnd();

		glPopMatrix();

	}
	//ilha 3
	static void ilha3() {
		glPushMatrix();
		glTranslatef(-200, 5500, 0);

		glBegin(GL_QUADS);
			glColor3f(0, 0.8, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(400, 0, 0);
			glVertex3f(400, 400, 0);
			glVertex3f(0, 400, 0);
		glEnd();

		glPopMatrix();

	}
};

bool tirosValidar() {
	bool teste = true;
	//Zera os tiros que sumiram ou colidiram

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
		Mapa::translacaoVertical();
		Mapa::desenharParede();
		Mapa::ilha1();
		Mapa::ilha3();
		Mapa::ilha3();
		objeto::galaoGasolina();
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
		if (player_posY > -385) {
			player_posY -= 1;
		}
	}
	shoot = (GetAsyncKeyState(0x20) != 0) ? TRUE : FALSE;

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