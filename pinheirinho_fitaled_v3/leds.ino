void acender(String qual) {
  if(qual == "azul") {
    value.b = 255; value.g = 0; value.r = 0; // RGB Value -> Blue
    for (int i = 11; i <= 18; i++) {
      LED.set_crgb_at(i, value); // Set value at LED found at index i
    }    
    for (int i = 41; i <= 48; i++) {
      LED.set_crgb_at(i, value);
    }
  }
  else if(qual == "prestage_d") {
    if (automatica) {value.b = 255; value.g = 255; value.r = 255;} //branco
    else {value.b = 0; value.g = 255; value.r = 255;} //amarelo
    for (int i = 19; i <= 29; i++) {
      LED.set_crgb_at(i, value);
    }
    digitalWrite(LED_PRESTAGED, HIGH);
  }
  else if(qual == "prestage_e") {
    if (automatica) {value.b = 255; value.g = 255; value.r = 255;} //branco
    else {value.b = 0; value.g = 255; value.r = 255;} //amarelo
    for (int i = 0; i <= 10; i++) {
      LED.set_crgb_at(i, value);
    }
    digitalWrite(LED_PRESTAGEE, HIGH);
  }
  else if(qual == "stage_d") {
    if (automatica) {value.b = 255; value.g = 255; value.r = 255;} //branco
    else {value.b = 0; value.g = 255; value.r = 255;} //amarelo
    for (int i = 30; i <= 40; i++) {
      LED.set_crgb_at(i, value);
    }
//    digitalWrite(LED_STAGED, HIGH);
  }  
  else if(qual == "stage_e") {
    if (automatica) {value.b = 255; value.g = 255; value.r = 255;} //branco
    else {value.b = 0; value.g = 255; value.r = 255;} //amarelo
    for (int i = 49; i <= 59; i++) {
      LED.set_crgb_at(i, value);
    }
//    digitalWrite(LED_STAGEE, HIGH);
  }
  else if(qual == "queima_d") {
    value.b = 0; value.g = 0; value.r = 255; //vermelho
    for (int i = 19; i <= 40; i++) {
      LED.set_crgb_at(i, value);
    }
  }  
  else if(qual == "queima_e") {
    value.b = 0; value.g = 0; value.r = 255; //vermelho
    for (int i = 0; i <= 10; i++) {
      LED.set_crgb_at(i, value);
    }
    for (int i = 49; i <= 59; i++) {
      LED.set_crgb_at(i, value);
    }
  }
  else if(qual =="start") {
    for (int i = 0; i <= 59; i++) {
      value.b = 0; value.g = 0; value.r = 255; //vermelho
      LED.set_crgb_at(i, value);
      value.b = 0; value.g = 255; value.r = 0; //verde
      LED.set_crgb_at(59-i, value);
      LED.sync();
      delay(30);
      value.b = 0; value.g = 0; value.r = 0; //preto
      LED.set_crgb_at(i, value);
      LED.set_crgb_at(59-i, value);
    }   
  }
  LED.sync(); // Sends the value to the LED 
}

void apagar(String qual) {
  value.b = 0; value.g = 0; value.r = 0; //preto
  if(qual == "tudo") {
    for (int i = 0; i <= NUM_LEDS; i++) { LED.set_crgb_at(i, value); } //apagar tudo
  }
  else if(qual == "azul") {
    for (int i = 11; i <= 18; i++) {
      LED.set_crgb_at(i, value);
    }
    for (int i = 41; i <= 48; i++) {
      LED.set_crgb_at(i, value);
    }
  }
  else if(qual == "prestage_d") {
    for (int i = 19; i <= 29; i++) {
      LED.set_crgb_at(i, value);
    }
    digitalWrite(LED_PRESTAGED, LOW);
  }
  else if(qual == "prestage_e") {
    for (int i = 0; i <= 10; i++) {
      LED.set_crgb_at(i, value);
    }
    digitalWrite(LED_PRESTAGEE, LOW);     
  }
  else if(qual == "stage_d") {
    for (int i = 30; i <= 40; i++) {
      LED.set_crgb_at(i, value);
    }     
    digitalWrite(LED_STAGED, LOW);
  }
  else if(qual == "stage_e") {
    for (int i = 49; i <= 59; i++) {
      LED.set_crgb_at(i, value);
    }     
    digitalWrite(LED_STAGEE, LOW);
  }
  LED.sync(); // Sends the value to the LED
}
