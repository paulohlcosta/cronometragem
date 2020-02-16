/* wemos D1 mini
 *  
 *  Create a WiFi access point and provide a web server on it.
** For more details see http://42bots.com.
* https://42bots.com/tutorials/esp8266-example-wi-fi-access-point-web-server-static-ip-remote-control/
* 
* descritivo rapido do webserver: https://www.esp8266.com/viewtopic.php?t=2153
* função de gerar o html: https://pt.wikipedia.org/wiki/Printf
* exibir em fullscreen: https://www.w3schools.com/howto/howto_js_fullscreen.asp
* 
* PROGRAMA DE CRONOMETRAGEM
* CONECTA AO RASPBERRY PI/celular ATRAVES DO SERVIDOR WIFI, EXIBINDO PAGINA HTML
* CONECTA AO ARDUINO MESTRE ATRAVÉS DAS GPIOs
* CONECTA AO ARDUINO CHEGADA ATRAVÉS DE RS485
* 
* conectar SDA no pino A4/(D2 no wemosd1mini)
* conectar SCK no pino A5/(D1 no wemosd1mini)
* 
* PINOS DISPONIVEIS PARA TRABALHAR: D0 D1 D2   D5 D6 D7
* 
* v1: criado o design basico, para exibicao html, sem comunicacao com outros dispositivos
* v1.1: 
* V2.2: esse codigo funcionou para receber dados PRINT, ler como INTEIRO 
* e exibir no OLED, sem manipular ou atribuir a alguma variavel
* v2.3: atribuir numeros nas variaveis... precisa receber 4 números em sequencia
* via Serial.print() separados por um caractere de texto ex.: Serial.print("x");
* o caractere de texto serve pra dizer que o numero "acabou". boa velocidade de transmissao.
* v2.4: APROVADO ajustes no display oled e necessario revisar o programa que envia os dados validados
*/
#define PRESTAGE_D D1
#define PRESTAGE_E D2
#define VERDE      D5
#define GATILHO    D0
#define OLED_Address 0x3C

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(1);

IPAddress    apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "cronometro";
const char *password = "1234567890";

int reacao_e = 8888;
int pista_e = 8888;
int total_e = 8888;
int reacao_d = 8888;
int pista_d = 8888;
int total_d = 8888;

ESP8266WebServer server(80);

void handleRoot() {
  char html[2000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

// Build an HTML page to display on the web-server root address
  snprintf ( html, 2000,

"<html><head><meta http-equiv='refresh' content='5'/><style> \
body {background-color: #000000; font-family: Arial, Helvetica, Sans-Serif; font-size: 2em; Color: #CCCCCC; } \
h1 {font-size: 3em; Color: #AA0000; text-align: center;} h2 {font-size: 6em; margin-top: -25px;}\
.colunastempos { font-weight: bold; color: #FF0; text-align: right; vertical-align: middle; width: 100%%; border: 0; }\
</style> </head> <body> <table width='100%%' height='100%%' border='0' cellspacing='0' cellpadding='0'> <tr>\
<td height='10'><h1>* CRONOMETRAGEM EM DESENVOLVIMENTO *</h1></td></tr>\
<tr><td><table  class='colunastempos' cellspacing='0' cellpadding='10'><tr><td align='left'>\
<p>REACAO:</p><h2>%d%</h2>\
<p>TEMPO DE PISTA:</p><h2>%d%</h2>\
<p>TEMPO TOTAL:</p><h2>%d%</h2></td>\
<td align='right'><p>REACAO:</p><h2>%d%</h2>\
<p>TEMPO DE PISTA:</p><h2>%d%</h2>\
<p>TEMPO TOTAL:</p><h2>%d%</h2></td></tr></table></td></tr>\
<tr><td align='center'><p>Uptime: %02d:%02d:%02d | This page refreshes every 5 seconds. Click <a href=\"javascript:window.location.reload();\">here</a> to refresh the page now. </p></td></tr>\
<tr><td height='10'><h1>* PISTA MOTOR RACE LUCAS DO RIO VERDE *</h1></td></tr></table></body></html>",

    reacao_e,
    pista_e,
    total_e,
    reacao_d,
    pista_d,
    total_d,
    hr, min % 60, sec % 60
  );
  server.send ( 200, "text/html", html );
}

void handleNotFound() {
  digitalWrite ( LED_BUILTIN, 0 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( LED_BUILTIN, 1 ); //turn the built in LED on pin DO of NodeMCU off
}

void setup() {

  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.display();
  delay(1000);
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(30,6);
  oled.print("CRONOMETRO");
  oled.display();  
  delay(1500);

  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.println();
  oled.println("Configuring access \npoint...\n");
  oled.println(ssid);
  oled.print("senha: ");
  oled.println(password);
//  oled.setCursor(30,40);
//  oled.println("CRONOMETRO");
  oled.display();
  
  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  oled.print("AP IP address: ");
  oled.println(myIP);
 
  server.on ( "/", handleRoot );
  server.on ( "/led=1", handleRoot);
  server.on ( "/led=0", handleRoot);
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  
  server.begin();

  Serial.begin(4800);
  Serial.println("HTTP server started");
}

void loop() {
  if(Serial.available()) {        //abre a escuta kkkkkkk
    reacao_d = Serial.parseInt(); //recebendo 4 dados em sequencia
    Serial.read(); //limpa a entrada de dados (usado "x" pra saber que acabou de enviar o numero)
    reacao_e = Serial.parseInt();
    Serial.read();
    pista_d = Serial.parseInt();
    Serial.read();
    pista_e = Serial.parseInt();
    Serial.read();
    oled.clearDisplay();
    oled.drawRect(0, 0, 128, 64, WHITE);
    oled.setCursor(10,5);
    oled.setTextSize(1);
    oled.println("dados recebidos: \n");
    oled.print(" reacao_d: ");
    oled.println(reacao_d);
    oled.print(" reacao_e: ");
    oled.println(reacao_e);
    oled.print(" pista_d: ");
    oled.println(pista_d);
    oled.print(" pista_e: ");
    oled.println(pista_e);
    oled.display();
    total_d = reacao_d + pista_d;
    total_e = reacao_e + pista_e;
    Serial.print(reacao_d + pista_d + reacao_e + pista_e); //verificacao
    Serial.print("x");
    digitalWrite (LED_BUILTIN, LOW);
    delay(50);
    digitalWrite ( LED_BUILTIN, HIGH);
  }
  server.handleClient();
}
