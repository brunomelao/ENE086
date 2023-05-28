// Gerando um degrau com sinal PWM a uma freq. de 7812.5 Hz

// ------- Pinos de saída -------
#define pinmotor1A 5  // Sinal PWM - Motor 1 - sentido de rotação A
#define pinio 7       // Pino de io


// ------- Pinos de entrada -------
// Potenciômetro
#define potenciometro A0  // Leitura do potenciômetro

// Define a frequência e amplitude da onda senoidal
const float freq = 7812.5 ; // Hz

// Patamares percentuais do degrau (% / 100)
float nivel_alto = 0.8;    // 80% da tensão nominal
float nivel_baixo = 0.6;   // 60% da tensão nominal

// Tempos do degrau (segundos)
float tempo_nivel_alto = 1;    // Tempo no patamar de 80%
float tempo_nivel_baixo = 1;   // Tempo no patamar de 60%

// Divisor da frequência selecionada
int divisor = 8;

void setup()
{
  // Definindo os pinos de saída
  pinMode(pinmotor1A, OUTPUT);
  pinMode(pinio, OUTPUT);
  
  // Definindo os pinos de entrada
  pinMode(potenciometro, INPUT);
  
  // Alterando a frequência do sinal PWM para 7812.5 Hz
  TCCR0B = TCCR0B & 0b11111000 | 0x02;
}



void loop()
{
  analogWrite(pinmotor1A, 255 * nivel_alto);
  digitalWrite(pinio, HIGH);
  delay(tempo_nivel_alto* 10000 * divisor);

  analogWrite(pinmotor1A, 255 * nivel_baixo);
  digitalWrite(pinio, LOW);
  delay(tempo_nivel_baixo * 10000 * divisor); 
}














