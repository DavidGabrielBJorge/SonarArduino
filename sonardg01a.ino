// Trabalho de referência de um sonar experimental
// IFTM 2018 - Microprocessados
// discente: David Gabriel Beilfuss Jorge

// O código a seguir foi obtido após estudo e análise de várias referências, citadas quando a mesma ocorre

// Biblioteca modificada para a placa SPFD5408 por Joao Lopes
// Versão 0.9.2

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>

// Pinos de controle do LCD
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Código de cores do LCD:
#define	WHITE   0x0000
#define	YELLOW  0x001F
#define	BLUE    0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define RED     0xFFE0
#define BLACK   0xFFFF
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Inclui a bibliotecas adaptadas do:
// prof.Lucas Marcon Trichez / Turma STAI 2015/1 Faculdade SENAI de tecnologia 
// Equipe : Alberto Alves Neves e Marcos Alejandro Silva (2017)

#define xcentro   120 // ponto x do central do scan
#define ycentro   120 // ponto y do central do scan
#define rscan     100 // raio do scan

#include <Ultrasonic.h>
//Define os pinos para o trigger e echo ultra som
#define pino_trigger 10
#define pino_echo 11
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

//Biblioteca servo motor
#include <Servo.h>
Servo myservo;  //controle do servo
#define angulomax  180  // para angulo maximo do servo
#define angulomin    0  // para angulo minimo do servo
unsigned int angulo=90; // variavel global , saida de dados da funcao
boolean direcao = 1;    // indicativa direcao servo


void setup(void) {

  myservo.attach(12);                 // ligacao do comando do servo no pino 12
  
  Serial.begin(9600);
  
  tft.reset();
  tft.begin(0x9341); // SDFP5408

  tft.fillScreen(BLACK); 

  tft.setRotation(180); // Need for the Mega, please changed for your choice or rotation initial

}

void servo() {

  myservo.write(angulo);      // move servo para posicao ANGULO
  if (angulo >= angulomax )   {direcao = 1;}
  if (angulo <= angulomin )   {direcao = 0;}
  
  if (direcao == 0 ) { angulo++;}
  if (direcao == 1 ) { angulo--;}

  calculo(angulo);// passa valor de angulo para funcao calculo

}//end servo
//**************************************************************
float ultraSom(){
  
   float cmMsec; 
   //Le as informacoes do sensor em cm 
   long microsec = ultrasonic.timing();
   cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
   return cmMsec;// saida de dados da funcao
   
   }//end ultraSom

void calculo(unsigned int angulo){
   int dist = 0;// seta variavel indicativa de distancia para menos de 50cm
   float cmMsec= ultraSom(); // variavel que pega seu valor da funcao ultrasom
   int anguloSonar = map(angulo,(angulomax),(angulomin),-90,90); //faz adequacao de valores
   int x1 = (xcentro + (sin(anguloSonar/57.296 ) * rscan)); //calcula cordenada x1,final do rscan, transformando-a em radianos 
   int y1 = (ycentro - (cos(anguloSonar/57.296 ) * rscan)); //calcula cordenada y1,final do rscan, transformando-a em radianos

   if (cmMsec > 50) {cmMsec=50;  dist = 1;} //delimita distancia maxima em 50 cm , ajusta a variavel indicativa de distancia para mais de 50cm 
   unsigned int dectado = map(cmMsec,0,50,1,48); //faz adequacao de valores-
   int x2 = (xcentro + (sin(anguloSonar/57.296 )* dectado)); //calcula cordenada x1,para mostrar objeto detectado
   int y2 = (ycentro - (cos(anguloSonar/57.296 )* dectado)); //calcula cordenada y1,para mostrar objeto detectado
  
   tftlcd(x1,y1,x2,y2,cmMsec,dist);//envia coordenadas de x1 e y1 para final da linha do rscan,
                                    //coordenadas x2,y2 para posicao objeto detectado e ditancia do objeto detectado, em cm e
                                    // valor dist , indicando se objeto esta mais de 50 cm

}//end calculo

void tftlcd(int x1,int y1, int x2,int y2,float cmMsec,int dist){
   
   tft.fillCircle(x2,y2,4, YELLOW);//desenha circulo no lugar aonde tem objeto  
  
   tft.drawLine(xcentro,ycentro,x1,y1, RED);//desenha rscan (inicio x e y, final x1 e y1)    
   int anguloSonar = map(angulo,(angulomax),(angulomin),-90,90); //faz adequacao de valores
   int x3 = (xcentro -2 + (sin(anguloSonar/57.296 ) * rscan)); //calcula cordenada x1,final do rscan, transformando-a em radianos 
   int y3 = (ycentro +2 - (cos(anguloSonar/57.296 ) * rscan)); //calcula cordenada y1,final do rscan, transformando-a em radianos

   
  tft.drawLine(xcentro,ycentro,x3,y3, BLACK);// apaga a linha no final x1,y1
       
}//end tftlcd

void loop(void) {  servo();}


