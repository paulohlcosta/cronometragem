/*  ---------- CONTROLE DA CHEGADA -----------
TECNOLOGIA: FOTOCELULA COM SENSORES INFRAVERMELHO
RELÊS NORMAL FECHADO (HIGH = SEM CONTATO = LED OFF)
Recebendo sinal IR, digitalRead é false

v1.14 testado, aprovado 50ms, sem comunicacao
v2 testado, comunicacao aprovado
v2.1 corrigido manter aceso apos um ciclo
v2.2 aumentado para 70 ms para evitar fantasmas
-------------------------------------------------- */

#define pinSensorE A1
#define pinSensorD A3
#define pinLEDE 13
#define pinLEDD 12
#define ENABLE 3

boolean sinalizarE = false; //qual a necessidade dessa flag?
boolean sinalizarD = false;//R.: ele deve ser ativado quando começar receber sinal
boolean oldE = false;
boolean oldD = false;
boolean valorE = false;
boolean valorD = false;

unsigned long agora = 0;
unsigned long horaInterrompeuE = millis();
unsigned long horaInterrompeuD = millis();
unsigned long millis_vencedor = 0;

int intervalo = 70;
int vencedor = 0;

void intro();
void piscar(int luz);
void finalizou(int luz);

void setup() {
  pinMode(pinSensorE, INPUT);
  pinMode(pinSensorD, INPUT);
  pinMode(pinLEDE, OUTPUT);
  pinMode(pinLEDD, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, HIGH);

  Serial.begin(9600);
  Serial.print("chegada_v2.2");

 /* Serial.write(68); //tabela ascii letra D
  delay(5000);
  Serial.write(69); // tabela ascii letra E */

  intro();
}

void loop() {
  agora = millis();
  valorE = digitalRead(pinSensorE);
  valorD = digitalRead(pinSensorD);
//---------------------------SENSOR ESQUERDO  
  if (valorE && !oldE) { // ALTERNOU PARA INTERROMPIDO
    horaInterrompeuE = agora;
    oldE = valorE;
  }
  if (!valorE && oldE) { // ALTERNOU PARA RECEBENDO
    oldE = valorE;
    sinalizarE = true;
  }
//------------------------------SENSOR DIREITO -------------
  if (valorD && !oldD) { // ALTERNOU PARA INTERROMPIDO
    horaInterrompeuD = agora;
    oldD = valorD;
  }
  if (!valorD && oldD) { // ALTERNOU PARA RECEBENDO
    oldD = valorD;
    sinalizarD = true;
  }

//caso em que ta recebendo sinal, e alternou demorando
//ficou tempo grande interrompido (nao necessariamente recebeu sinal)
  if (valorE && (agora >= (horaInterrompeuE+intervalo)) && sinalizarE) {
    finalizou(pinLEDE);
    sinalizarE = false;
    sinalizarD = false;
  }
  
  if (valorD && (agora >= (horaInterrompeuD+intervalo)) && sinalizarD) {
    finalizou(pinLEDD);
    sinalizarD = false;
    sinalizarE = false;
  }
/*********************************************************** TIMEOUT 8 segundos *****/
  if ((vencedor != 0) and (agora > (millis_vencedor + 8000))) {
    if (vencedor == pinLEDE) finalizou(pinLEDD); //forçando fim de prova
    if (vencedor == pinLEDD) finalizou(pinLEDE);
  }
}

void finalizou(int luz) { //deve enviar os bytes na hora certa e piscar depois do 2º
  if (luz == pinLEDD) {
    Serial.write(48); //enviar no formato byte
    if (vencedor == 0) {     //se ninguem foi atribuido como vencedor
      vencedor = luz;   //esse passa a ser o vencedor
      digitalWrite(luz, HIGH); //apaga LED dele
    } else if (vencedor == pinLEDE){
      piscar(pinLEDE);      //caso contrario o outro pisca
    }
  }
  if (luz == pinLEDE) {
    Serial.write(96); //enviar no formato byte
    if (vencedor == 0) {     //se ninguem foi atribuido como vencedor
      vencedor = luz;   //esse passa a ser o vencedor
      digitalWrite(luz, HIGH); //apaga LED dele
    } else if (vencedor == pinLEDD) {
      piscar(pinLEDD);      //caso contrario o outro pisca
    }
  }
  millis_vencedor = agora;
}

void intro() {
//vamos comecar piscando as luzes
  digitalWrite(pinLEDE, LOW);
  digitalWrite(pinLEDD, HIGH);
  delay(200);
  digitalWrite(pinLEDE, HIGH);
  digitalWrite(pinLEDD, LOW);
  delay(200);
  digitalWrite(pinLEDE, LOW);
  digitalWrite(pinLEDD, HIGH);
  delay(200);
  digitalWrite(pinLEDE, HIGH);
  digitalWrite(pinLEDD, LOW);
  delay(200);
  digitalWrite(pinLEDE, LOW);
  digitalWrite(pinLEDD, HIGH);
  delay(200);
  digitalWrite(pinLEDE, HIGH);
  digitalWrite(pinLEDD, LOW);
  delay(200);  
  digitalWrite(pinLEDE, LOW);
  digitalWrite(pinLEDD, HIGH);
  delay(200);
  digitalWrite(pinLEDE, HIGH);
  digitalWrite(pinLEDD, LOW);
  delay(200);
  digitalWrite(pinLEDE, LOW);
}

void piscar(int luz) {
  vencedor = 0;
  digitalWrite(luz, LOW);//acende
  delay(200);
  digitalWrite(luz, HIGH);
  delay(200);
  digitalWrite(luz, LOW);
  delay(200);
  digitalWrite(luz, HIGH);
  delay(200);
  digitalWrite(luz, LOW);
  delay(200);
  digitalWrite(luz, HIGH);
  delay(200);
  digitalWrite(luz, LOW);
  delay(200);
  digitalWrite(luz, HIGH);
  delay(1000);
  digitalWrite(luz, LOW);
  delay(1000);
  digitalWrite(luz, HIGH);
  delay(1000);
  digitalWrite(luz, LOW);
  delay(1000);
  digitalWrite(luz, HIGH);
  delay(1000);
  digitalWrite(pinLEDD, LOW);
  digitalWrite(pinLEDE, LOW);
  delay(1000);
}
