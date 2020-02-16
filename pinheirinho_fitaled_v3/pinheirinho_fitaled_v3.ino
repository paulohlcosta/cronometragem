/* SCRIPT DO ARDUINO MESTRE (FICA JUNTO AOS SENSORES)
 * A PARTIR DA VERSAO 2.2 O PINHEIRINHO PASSOU A SER CONTROLADO POR UM ESCRAVO
 * NESSA VERSAO PRECISA APERTAR O GATILHO PARA DAR A LARGADA
 * PODEMOS USAR A0, A1, A2... etc COMO DIGITAL INPUT, PULLUP E OUTPUT (8 PORTAS)
 * v2.3 INCLUSO COMUNICACAO SERIAL E SOFTSERIAL PARA CALCULO DOS TEMPOS DE PISTA
 * software serial comunica via RS485 com chegada, recebendo codigos "E" e "D"
 * serial comunica com d1 mini, enviando informacoes dos tempos de reacao e pista
 * v2.4 corrigido envio de dados para d1mini, com validação. invertido serial e soft serial.
 * v2.5 limpeza de buffer e zerar todos os tempos na largada, atualizar() na sequencia 5
 * v2.6 correcoes na sequencia e recebimento de dados RS485 serial; APROVADO
 * V2.7 ajustes da exibicao dos tempos, reiniciar no gatilho
 * v2.7.1 APROVADO
 * v2.7.2 APROVADO: timeout: poder zerar quando estiver na sequencia 5 ou 7; 
 * corrigido reacoes erradas quando a ultima puxada foi interrompida;
 * corrigido permitir enviar tempo mesmo quando um piloto nao largou;
 * v2.7.3 tentar corrigir erro na exibicao do ultimo resultado;
 * v2.7.4 incluir leds indicadores da placa
 * v2.7.5 resolver problema dos 65 segundos de tempo de pista: OK
 * v2.7.6 resolver problema de nao ler o tempo do segundo colocado: OK
 * v2.7.7 (em teste) permitir ler tempo de pista mesmo se o oponente nao largou
 * v2.7.8 funcao largada automatica (para ativar, manter gatilho apertado ao ligar)
 * removidos leds de feedback dentro do case
 * v3 trocado library fastLED para light_ws2812 devido ao consumo de memoria
 */

#include <cRGB.h>
#include <WS2812.h> //light_ws2812 library
#include <SoftwareSerial.h>
#define LED_PIN 6 //fio laranja
#define NUM_LEDS    60
#define GATILHO    9
#define PRESTAGED    2
#define PRESTAGEE    3
#define STAGED    4
#define STAGEE    5
#define COMUNIC_OUT 7 //fio amarelo
#define COMUNIC_IN 10 //fio verde
#define S_RX 12
#define S_TX 11
#define TXENABLE 8
#define LED_PRESTAGED A1
#define LED_PRESTAGEE A2
#define LED_STAGED A0
#define LED_STAGEE A3

SoftwareSerial mySerial(S_RX, S_TX); // portas software serial RX, TX
WS2812 LED(60); // 60 LEDs
cRGB value;

boolean tem_queima_d = false;
boolean tem_queima_e = false;
boolean largou_d = false;
boolean largou_e = false;
boolean finalizou_d = false;
boolean finalizou_e = false;
boolean automatica = false;

unsigned long em_espera_desde = 0;
unsigned long millis_largada = 0;
unsigned long millis_reacao_d = 0;
unsigned long millis_reacao_e = 0;
unsigned long millis_total_d = 0;
unsigned long millis_total_e = 0;

const int delay_chegada = 50;
int espera = 0;
int sequencia = 0;
/* NUMEROS DE SEQUENCIA PARA CONTROLE DA LARGADA
 * 0 - PRESTAGE DE AMBOS
 * 1 - STAGE DE AMBOS (gatilho pressionado)
 * 2 - LUZ AZUL
 * 3 - CONTAGEM EM ANDAMENTO
 * 4 - LARGADA AUTORIZADA
 * 5 - AMBOS OS PILOTOS LARGARAM/ENVIADOS OS TEMPOS DE REACAO PARA SERVER
 * 6 - UM PILOTO FINALIZOU E O TEMPO FOI ENVIADO AO SERVER
 * 7 - AMBOS OS PILOTOS FINALIZARAM E OS TEMPOS FORAM ENVIADOS AO SERVER
 * 8 - AGUARDANDO REINICIO */

void setup() {
  LED.setOutput(LED_PIN); // Digital Pin NUMBER

  mySerial.begin(4800); //----------------INICIA PROTOCOLO SoftSERIAL comunica com d1mini
  mySerial.println("pinheirinho_fitaled_v3");

  Serial.begin(9600); //----------------INICIA PROTOCOLO SERIAL
  Serial.println("pinheirinho_fitaled_v3"); //-----COMUNICA COM CHEGADA
  
  pinMode(13, OUTPUT);
  pinMode(GATILHO, INPUT_PULLUP);
  pinMode(PRESTAGED, INPUT_PULLUP);
  pinMode(PRESTAGEE, INPUT_PULLUP);
  pinMode(STAGED, INPUT_PULLUP);
  pinMode(STAGEE, INPUT_PULLUP);
  pinMode(TXENABLE, OUTPUT);
  pinMode(LED_PRESTAGED, OUTPUT);  
  pinMode(LED_PRESTAGEE, OUTPUT);  
  pinMode(LED_STAGED, OUTPUT);  
  pinMode(LED_STAGEE, OUTPUT);  
  pinMode(COMUNIC_OUT, OUTPUT);
  pinMode(COMUNIC_IN, INPUT);
    digitalWrite(COMUNIC_OUT, HIGH);

  if(digitalRead(GATILHO) == LOW) automatica = true;

  apagar("tudo");
  acender("start");
 
}

void largada() {
  acender("azul");
  sequencia = 2; // LUZ AZUL
                                digitalWrite(LED_BUILTIN, HIGH); //informacaoteste
  delay(800);
  apagar("azul");
  digitalWrite(COMUNIC_OUT, LOW); //NESSE MOMENTO INICIA A CONTAGEM DAS 3 LUZES
  largou_d = largou_e = finalizou_d = finalizou_e = false;
  millis_largada = millis_reacao_d = millis_reacao_e = millis_total_d = millis_total_e = 0;
  if(!automatica) atualizar(); //SE A LUZ AZUL FICAR ACESA, PRECISA RESETAR O D1 MINI
  delay(300);                     //TEMPO ENVIANDO SINAL LOW PARA EXECUTAR CONTAGEM
                                 digitalWrite(LED_BUILTIN, LOW); //informacaoteste
  digitalWrite(COMUNIC_OUT, HIGH);
}

//-------------------------------------funcao de atualizar o d1 mini
void atualizar() {
  bool aprovado = false;
  int reacao_d = millis_reacao_d - millis_largada;
  int reacao_e = millis_reacao_e - millis_largada;
  unsigned int pista_d = millis_total_d - millis_reacao_d;
  unsigned int pista_e = millis_total_e - millis_reacao_e;
  if (millis_total_e < millis_largada) pista_e = 0;
  if (millis_total_d < millis_largada) pista_d = 0;
  
  while (!aprovado) {
//    digitalWrite(LED_BUILTIN, HIGH);

   mySerial.print(reacao_d);
   mySerial.print("x");     //deixar essa linha pra ele entender que acabou o numero
   mySerial.print(reacao_e);
   mySerial.print("x");
   mySerial.print(pista_d);
   mySerial.print("x");
   mySerial.print(pista_e); 
   mySerial.print("x");  
//------------------------------------------------verificacao da integridade dos dados
    while (mySerial.available()==0) {             
                                       //Wait for input
    } 
    int lido =mySerial.parseInt(); //deve ser a soma dos 4 numeros enviados
    mySerial.read(); // limpa o buffer ("x")
    if (lido == (reacao_d+reacao_e+pista_d+pista_e)) {
      aprovado = true;
//      digitalWrite(LED_BUILTIN, LOW);
    } else {
      delay(100);
    }
//-------------------------------------------------------------------fim da verificacao 
  }
}
