void loop() {
  if(digitalRead(GATILHO) == LOW) {
    switch (modo) {
      case 1:
        intervalo = 400;
        digitalWrite(COMUNIC_OUT, HIGH);   //ENVIA SINAL HIGH PARA O OUTRO ARDUINO/GATILHO  
        digitalWrite(PINLARANJA1, LOW);   // LOW = ACIONA O RELE
        delay(intervalo);                       
        digitalWrite(PINLARANJA1, HIGH);    
        digitalWrite(PINLARANJA2, LOW);
        delay(intervalo);          
        digitalWrite(PINLARANJA2, HIGH);    
        digitalWrite(PINLARANJA3, LOW);
        delay(intervalo);
        digitalWrite(PINLARANJA3, HIGH);    
        digitalWrite(PINVERDE, LOW);
        digitalWrite(COMUNIC_OUT, LOW);    //FINALIZA O SINAL
        delay(3000);    
        digitalWrite(PINVERDE, HIGH);    
        break;
      case 2:
        intervalo = 300;
        digitalWrite(COMUNIC_OUT, HIGH);   //ENVIA SINAL HIGH PARA O OUTRO ARDUINO/GATILHO  
        digitalWrite(PINLARANJA1, LOW);   // LOW = ACIONA O RELE
        delay(intervalo);                       
        digitalWrite(PINLARANJA1, HIGH);    
        digitalWrite(PINLARANJA2, LOW);
        delay(intervalo);          
        digitalWrite(PINLARANJA2, HIGH);    
        digitalWrite(PINLARANJA3, LOW);
        delay(intervalo);
        digitalWrite(PINLARANJA3, HIGH);    
        digitalWrite(PINVERDE, LOW);
        digitalWrite(COMUNIC_OUT, LOW);    //FINALIZA O SINAL
        delay(3000);    
        digitalWrite(PINVERDE, HIGH);    
        break;
      case 3: //nesse modo tem entrelaçamento de luzes, pode exigir mais da bateria
        intervalo = 350;
        digitalWrite(COMUNIC_OUT, HIGH);   //ENVIA SINAL HIGH PARA O OUTRO ARDUINO/GATILHO  
        digitalWrite(PINLARANJA1, LOW);   // LOW = ACIONA O RELE
        delay(intervalo);                   
        digitalWrite(PINLARANJA2, LOW);
        delay(50);
        digitalWrite(PINLARANJA1, HIGH);    
        delay(intervalo);          
        digitalWrite(PINLARANJA3, LOW);
        delay(50);
        digitalWrite(PINLARANJA2, HIGH);    
        delay(intervalo);
        digitalWrite(PINVERDE, LOW);
        delay(50);
        digitalWrite(PINLARANJA3, HIGH);    
        digitalWrite(COMUNIC_OUT, LOW);    //FINALIZA O SINAL
        delay(3000);    
        digitalWrite(PINVERDE, HIGH);    
        break;
      case 4: //modo em que todas as luzes amarelas acendem
        intervalo = 500;
        digitalWrite(COMUNIC_OUT, HIGH);   //ENVIA SINAL HIGH PARA O OUTRO ARDUINO/GATILHO  
        digitalWrite(PINLARANJA1, LOW);   // LOW = ACIONA O RELE
        digitalWrite(PINLARANJA2, LOW);
        digitalWrite(PINLARANJA3, LOW);
        delay(intervalo);
        digitalWrite(PINVERDE, LOW);
        digitalWrite(PINLARANJA2, HIGH);    
        digitalWrite(PINLARANJA3, HIGH);    
        digitalWrite(PINLARANJA1, HIGH);    
        digitalWrite(COMUNIC_OUT, LOW);    //FINALIZA O SINAL
        delay(3000);    
        digitalWrite(PINVERDE, HIGH);    
        break;
      default: //se nenhum modo estiver ativo funciona esse 
/*        intervalo = 400;
        digitalWrite(COMUNIC_OUT, HIGH);   //ENVIA SINAL HIGH PARA O OUTRO ARDUINO/GATILHO  
        digitalWrite(PINLARANJA1, LOW);   // LOW = ACIONA O RELE
        delay(intervalo);                       
        digitalWrite(PINLARANJA1, HIGH);    
        digitalWrite(PINLARANJA2, LOW);
        delay(intervalo);          
        digitalWrite(PINLARANJA2, HIGH);    
        digitalWrite(PINLARANJA3, LOW);
        delay(intervalo);
        digitalWrite(PINLARANJA3, HIGH);    
        digitalWrite(PINVERDE, LOW);
        digitalWrite(COMUNIC_OUT, LOW);    //FINALIZA O SINAL
        delay(3000);    
        digitalWrite(PINVERDE, HIGH);              */
        intervalo = 40;
        digitalWrite(COMUNIC_OUT, HIGH);   //ENVIA SINAL HIGH PARA O OUTRO ARDUINO/GATILHO  
        digitalWrite(PINLARANJA1, LOW); //LOW Acende
        leds[0] = CRGB::Green;
        for (int i = (NUM_LEDS-1); i >= (NUM_LEDS-10); i--) {
          leds[i] = CRGB::Yellow;
          FastLED.show();
          delay(intervalo);
        }
        digitalWrite(PINLARANJA1, HIGH);    
        digitalWrite(PINLARANJA2, LOW);
        for (int i = (NUM_LEDS-11); i >= (NUM_LEDS-20); i--) {
          leds[i] = CRGB::Yellow;
          FastLED.show();
          delay(intervalo);
        }
        digitalWrite(PINLARANJA2, HIGH);    
        digitalWrite(PINLARANJA3, LOW);
        for (int i = (NUM_LEDS-21); i >= (NUM_LEDS-30); i--) {
          leds[i] = CRGB::Yellow;
          FastLED.show();
          delay(intervalo);
        }               
        digitalWrite(PINLARANJA3, HIGH);    
        digitalWrite(PINVERDE, LOW);
        for (int i = 0; i <= (NUM_LEDS-1); i++) {
          leds[i] = CRGB::Green;
        }
        FastLED.show();
        digitalWrite(COMUNIC_OUT, LOW);    //FINALIZA O SINAL
        delay(3000);    
        digitalWrite(PINVERDE, HIGH);    
        for (int i = 0; i <= (NUM_LEDS-1); i++) {
          leds[i] = CRGB ( 0, 0, 0);
        }
        FastLED.show();

        break;
    }
  }
}
