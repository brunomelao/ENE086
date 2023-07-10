// ------------------ Controle PID - Biblioteca ------------------

// Incluindo os pacotes necessários
#include <PID_v1.h>

// ------- Pinos de Saída -------
#define pinmotor1A 5	           // Definindo o pino do motor 1 - Sentido de rotação A -Sinal PWM 
#define sinal_pwm_interrupcoes 11  // Definindo o pino do sinal de referência para as interrupções


// ------- Pinos de Entrada -------
#define potenciometro A0          // Definindo o pino em que será conectado o potênciômetro
#define tensao_saida_gerador A1   // Definindo o pino onde será conectado o gerador
#define pininterrupcao 3          // Definindo o pino de interrupção


// Variáveis do controlador
double leitura_pot;      // Referência
double leitura_tensao;   // Entrada
double U;                // Saída

double leitura_pot_volts;
double leitura_tensao_volts;

// Ganhos do controlador
double Kp = 14.2049; 
double Ki = 70.5184; 
double Kd = 0.63608;

//double Kp = 3.8019; 
//double Ki = 71.4399; 
//double Kd = 0;

// Definindo o controlador PID
PID myPID(&leitura_tensao, &U, &leitura_pot, Kp, Ki, Kd, DIRECT);

// ------- Função executada na interrupção -------
void F_ISR(){
  
  // Leitura
  leitura_pot_volts = round(analogRead(potenciometro) / 204.6);
  leitura_tensao_volts = analogRead(tensao_saida_gerador) / 210.49;

  leitura_pot = round(analogRead(potenciometro) / 204.6); // Leitura da referência (Potenciômetro)  
  leitura_tensao = analogRead(tensao_saida_gerador) / 210.49 // Leitura da saída do sistema (Tensão Gerador)

  // Executando o PID
  myPID.Compute();

  // Atualizando a saída do controlador
  analogWrite(pinmotor1A,U);  
  
}


void setup(){

    Serial.begin(9600);    // Habilitando o modo de comunicação através da porta serial. 9600: Velocidade de comunicação.

  	// Definindo os pinos de saída
  	pinMode(pinmotor1A, OUTPUT);
  	pinMode(sinal_pwm_interrupcoes, OUTPUT);
    
  
  	// Definindo os pinos de entrada
  	pinMode(potenciometro, INPUT);
  	pinMode(tensao_saida_gerador, INPUT);
    pinMode(pininterrupcao, INPUT);
  
    // Alterando a frequência do sinal PWM para 7812.5 Hz
    TCCR0B = TCCR0B & 0b11111000 | 0X02;
  
  	// Definindo os parâmetros da interrupção
  	attachInterrupt(digitalPinToInterrupt(3), F_ISR, RISING);
	
    // Obs.: No arduino Uno as interrupções só podem ser feitas nos pinos 2 e 3
    // Parâmetros: -> digitalPinToInterrupt(3) - Pino de interrupção (Pino 3)
    //             -> ISR - Função executada quando se detecta uma interrupção
    //             -> RISING - Indica que a interrupção será executada na borda de subida do sinal PWM

    // Setando o PID no modo automático
    myPID.SetMode(AUTOMATIC);
      
}


void loop(){

  // Sinal PWM de referência para as Interrupções 
  analogWrite(sinal_pwm_interrupcoes, 255);      // Sinal PWM qualquer de 7812.5Hz para servir de base para as interrupções 
  

  // Plotagem dos gráficos
  Serial.print(leitura_pot_volts);
  Serial.print(" ");
  Serial.print(leitura_tensao_volts);
  Serial.print(" ");
  Serial.print(U);
  Serial.print(" ");
  Serial.print(5);
  Serial.print(" ");
  Serial.print(0);
  Serial.println(" ");


}



