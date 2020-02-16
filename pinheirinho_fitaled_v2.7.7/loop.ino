void loop() {

/*informacaoteste */
  if (sequencia > 6) {
    digitalWrite(LED_BUILTIN, LOW); //informacaoteste
  }
    
  /************************ MARCACAO DO TEMPO DE PISTA *************************/
  if((largou_d or largou_e) and (sequencia <= 6)) {
    digitalWrite(ENABLE, LOW);
    if (Serial.available()) {
      unsigned long currentMillis = millis(); //basicamente le o millis
      byte lado = Serial.read();
      if ((lado == 48) and !finalizou_d) {
        millis_total_d = currentMillis - delay_chegada;
        finalizou_d = true;        //considera carro fora da pista ja, pra nao ler denovo
        sequencia++;
      }
      if ((lado == 96) and !finalizou_e) {
        millis_total_e = currentMillis - delay_chegada;
        finalizou_e = true;        //considera carro fora da pista ja, pra nao ler denovo
        sequencia++;
      }
      atualizar();
    }
  } 
  if ((sequencia < 4) or (sequencia > 6)) digitalWrite(ENABLE, HIGH);
  
  /*********** PROGRAMA PRINCIPAL = LUZES DE PRESTAGE E STAGE e REACAO **************/
  if(!tem_queima_d) {
    if(digitalRead(PRESTAGED)) {
      acender("prestage_d"); 
    }
    else {
      apagar("prestage_d"); 
      if((sequencia >= 4) and !largou_d) { //LARGADA DIREITA, sem queima
        largou_d = true;
        millis_reacao_d = millis();
      }
    }
    if(digitalRead(STAGED)) acender("stage_d"); else apagar("stage_d");//esse nao importa muito
  }
  if(!tem_queima_e) {
    if(digitalRead(PRESTAGEE)) {
      acender("prestage_e"); 
    }
    else {
      apagar("prestage_e");
      if((sequencia >= 4) and !largou_e) { //LARGADA ESQUERDA, sem queima
        largou_e = true;
        millis_reacao_e = millis();
      }
    }
    if(digitalRead(STAGEE)) acender("stage_e"); else apagar("stage_e");//esse nao importa muito
  }
  /****************************************************** ATIVAMENTO DO GATILHO *****/
  if((digitalRead(GATILHO) == LOW) and !tem_queima_d and !tem_queima_e){
    sequencia = 1; //STAGE DE AMBOS
    largada();
  }
  if (digitalRead(COMUNIC_IN) == HIGH) { //SE RECEBE SINAL ALTO INDICA LARGADA EM ANDAMENTO 
    sequencia = 3; //CONTAGEM EM ANDAMENTO
  /******************************************* VERIFICACAO DA QUEIMA DE LARGADA *****/
    if ((digitalRead(PRESTAGED) == LOW) and !tem_queima_d) { //LARGADA DIREITA QUEIMADA
      acender("queima_d");
      tem_queima_d = largou_d = true;
      millis_reacao_d = millis();
    } 
    if ((digitalRead(PRESTAGEE) == LOW) and !tem_queima_e) {//LARGADA ESQUERDA QUEIMADA
      acender("queima_e");
      tem_queima_e = largou_e = true;
      millis_reacao_e = millis();
    }
  }
/***************************MARCANDO HORARIO DA LARGADA**************************/
  if ((sequencia == 3) and (digitalRead(COMUNIC_IN) == LOW)) {//FOI DADA A LARGADA
    sequencia = 4; //LARGADA AUTORIZADA
    millis_largada = millis();
  }
/***************************ENVIANDO TEMPOS DE REACAO****************************/  
  if ((sequencia == 4) and largou_d and largou_e) {
    atualizar();
    sequencia = 5; //AMBOS OS PILOTOS LARGARAM/ENVIADOS TEMPO DE REACAO
  }
/**************************BOTAO LIMPAR TEMPOS E QUEIMA **************************/
  if (((sequencia == 5) or (sequencia == 7)) and (digitalRead(GATILHO) == LOW)) {
    apagar("tudo");
    tem_queima_d = false;
    tem_queima_e = false;
    while(Serial.read() >= 0) ; // flush the receive buffer
    while(mySerial.read() >= 0) ; // flush the receive buffer
    delay(1000);
    sequencia = 0;
  }
}
