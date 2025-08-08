#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // Biblioteca para criar o JSON

BH1750 lightMeter;
Adafruit_BME280 bme; 

const char* ssid = "XXXXXX"; //SSID da rede 
const char* password = "XXXXXXX"; //Senha da rede
const String google_apps_script_url = "https://XXXXXXXX"; //URL da API

const int micPin = 34;
const int pirAPin = 14;
const int pirBPin = 12;

unsigned long pirA_lastTrigger = 0;
unsigned long pirB_lastTrigger = 0;
const int debounceDelay = 200;

void setup() {
  Serial.begin(115200);
  pinMode(pirAPin, INPUT); 
  pinMode(pirBPin, INPUT);
  Wire.begin(); 

  // Inicializa o Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando-se ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());

  // Inicializa os sensores
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Sensor BH1750 inicializado com sucesso.");
  } else {
    Serial.println("Erro ao inicializar o BH1750.");
  }
  
  if (bme.begin(0x76)) { 
    Serial.println("Sensor BME280 inicializado com sucesso.");
  } else {
    Serial.println("Erro ao inicializar o BME280.");
  }
  
  Serial.println("Todos os sensores e Wi-Fi inicializados.");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    // Coleta dos dados
    float lux = lightMeter.readLightLevel(); 
    float temperatura = bme.readTemperature();
    float umidade = bme.readHumidity();
    float pressao = bme.readPressure() / 100.0F; 
    int nivelRuido = analogRead(micPin);
    
    String direcaoMovimento = "Nenhum";

    int pirAState = digitalRead(pirAPin);
    int pirBState = digitalRead(pirBPin);

    if (pirAState == HIGH && millis() > pirA_lastTrigger + debounceDelay) {
      pirA_lastTrigger = millis();
      if (pirA_lastTrigger > pirB_lastTrigger) {
        direcaoMovimento = "A para B";
      }
    }

    if (pirBState == HIGH && millis() > pirB_lastTrigger + debounceDelay) {
      pirB_lastTrigger = millis();
      if (pirB_lastTrigger > pirA_lastTrigger) {
        direcaoMovimento = "B para A";
      }
    }

    // Cria o JSON
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["Luminosidade"] = lux;
    jsonDocument["Temperatura"] = temperatura;
    jsonDocument["Umidade"] = umidade;
    jsonDocument["Pressao"] = pressao;
    jsonDocument["NivelRuido"] = nivelRuido;
    jsonDocument["DirecaoMovimento"] = direcaoMovimento;
    
    String json_string;
    serializeJson(jsonDocument, json_string);

    // Envia os dados para a API
    HTTPClient http;
    http.begin(google_apps_script_url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(json_string);
    
    if(httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("API Response: ");
      Serial.println(response);
    } else {
      Serial.print("Erro no envio HTTP: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }

  delay(5000); // Envia dados a cada 5 segundos
}