/*----- SCRIPT DO ARDUINO ESCRAVO (PINHEIRINHO) QUE PODE FUNCIONAR INDEPENDENTE-----//
 * v1 aprovado
 * v1.1 usava reles 1 canal de tipos diferentes
 * v2 criado sobre a versao 1 que estava funcionando perfeitamente
 * FEATURES:
 * Chave DIP switch para 5 modos de funcionamento (velocidades da largada)
 * Conexão para fita LED indicadora no verso do pinheirinho??
 * 
 * SUGESTAO: colocar botao para RESET
 */
#include <FastLED.h>

#define PINLARANJA1  12  //LOW ACENDE
#define PINLARANJA2  11
#define PINLARANJA3  10
#define PINVERDE  6
#define GATILHO 9
#define COMUNIC_OUT 7
#define DIPA 16 // A2
#define DIPB 17 // A3
#define DIPC 18 // A4
#define DIPD 19 // A5
#define LED_PIN 3 // SINAL FITA LED (FastLED)
#define NUM_LEDS 30

CRGB leds[NUM_LEDS];

int intervalo = 400;
int modo = 0;

void setup() {
  pinMode(PINLARANJA1, OUTPUT);
  pinMode(PINLARANJA2, OUTPUT);
  pinMode(PINLARANJA3, OUTPUT);
  pinMode(PINVERDE, OUTPUT);
  pinMode(COMUNIC_OUT, OUTPUT);
  pinMode(GATILHO, INPUT_PULLUP);
  pinMode(DIPA, INPUT_PULLUP);
  pinMode(DIPB, INPUT_PULLUP);
  pinMode(DIPC, INPUT_PULLUP);
  pinMode(DIPD, INPUT_PULLUP);

  if(digitalRead(DIPA)) modo++;
  if(digitalRead(DIPB)) modo++;
  if(digitalRead(DIPC)) modo++;
  if(digitalRead(DIPD)) modo++;

//APAGAR AS LAMPADAS AO INICIAR - POUPAR BATERIA
  digitalWrite(PINLARANJA1, HIGH);
  digitalWrite(PINLARANJA2, HIGH); 
  digitalWrite(PINLARANJA3, HIGH);
  digitalWrite(PINVERDE, HIGH); 

//EXECUTA A SEQUENCIA DE BAIXO PARA CIMA
  digitalWrite(PINVERDE, LOW);  // LOW = ACIONA O RELE
  delay(400);    
  digitalWrite(PINVERDE, HIGH);     
  digitalWrite(PINLARANJA3, LOW);
  delay(400);               
  digitalWrite(PINLARANJA3, HIGH);    
  digitalWrite(PINLARANJA2, LOW);
  delay(400);          
  digitalWrite(PINLARANJA2, HIGH);    
  digitalWrite(PINLARANJA1, LOW);   
  delay(400);                       
  digitalWrite(PINLARANJA1, HIGH);    
}
