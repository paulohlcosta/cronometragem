void acender(String qual) {
  if(qual == "azul") {
    for (int i = 11; i <= 18; i++) {
      leds[i] = CRGB::Blue;
    }    
    for (int i = 41; i <= 48; i++) {
      leds[i] = CRGB::Blue;
    }
  }
  else if(qual == "prestage_d") {
    for (int i = 19; i <= 29; i++) {
      leds[i] = CRGB::Yellow;
    }
    digitalWrite(LED_PRESTAGED, HIGH);
  }
  else if(qual == "prestage_e") {
    for (int i = 0; i <= 10; i++) {
      leds[i] = CRGB::Yellow;
    }
    digitalWrite(LED_PRESTAGEE, HIGH);
  }
  else if(qual == "stage_d") {
    for (int i = 30; i <= 40; i++) {
      leds[i] = CRGB::Yellow;
    }
    digitalWrite(LED_STAGED, HIGH);
  }  
  else if(qual == "stage_e") {
    for (int i = 49; i <= 59; i++) {
      leds[i] = CRGB::Yellow;
    }
    digitalWrite(LED_STAGEE, HIGH);
  }
  else if(qual == "queima_d") {
    for (int i = 19; i <= 40; i++) {
      leds[i] = CRGB::Red;
    }
  }  
  else if(qual == "queima_e") {
    for (int i = 0; i <= 10; i++) {
      leds[i] = CRGB::Red;
    }
    for (int i = 49; i <= 59; i++) {
      leds[i] = CRGB::Red;
    }
  }   
  FastLED.show(); 
}

void apagar(String qual) {
  if(qual == "tudo") {
    for (int i = 0; i <= NUM_LEDS; i++) { leds[i] = CRGB ( 0, 0, 0); } //apagar tudo
  }
  else if(qual == "azul") {
    for (int i = 11; i <= 18; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 41; i <= 48; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
  }
  else if(qual == "prestage_d") {
    for (int i = 19; i <= 29; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    digitalWrite(LED_PRESTAGED, LOW);
  }
  else if(qual == "prestage_e") {
    for (int i = 0; i <= 10; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    digitalWrite(LED_PRESTAGEE, LOW);     
  }
  else if(qual == "stage_d") {
    for (int i = 30; i <= 40; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }     
    digitalWrite(LED_STAGED, LOW);
  }
  else if(qual == "stage_e") {
    for (int i = 49; i <= 59; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }     
    digitalWrite(LED_STAGEE, LOW);
  }
  FastLED.show();
}
