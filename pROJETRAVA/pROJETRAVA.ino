#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int productCount = 0;  // Variável para armazenar a contagem de produtos

// Conteúdo da página web em memória programável
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<style>
  body {text-align: center; font-family: Arial, sans-serif; background-color: #f9f9f9; margin:0; padding:0; box-sizing: border-box;}
  .container {max-width: 600px; margin: auto; padding: 20px; background-color: #fff; border-radius: 8px; box-shadow: 0 0 10px rgba(0,0,0,0.1);}
  .button {font-size: 24px; padding: 10px 20px; margin: 10px; background-color: #008CBA; color: white; border: none; border-radius: 5px; cursor: pointer;}
  .button:hover {background-color: #005f5f;}
</style>
</head>
<body>
<div class="container">
  <h1>Demonstracao WiFi Fechadura Eletrica</h1><br>
  <button class="button" onclick="sendRequest('/unlock')">Desbloquear</button><br>
  <button class="button" onclick="sendRequest('/lock')">Bloquear</button><br>
  <p>Produtos Sairam: <span id="productCount"></span></p>
</div>
<script>
  function sendRequest(url){
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    xhr.send();
  }

  function updateProductCount() {
    fetch('/productCount')
      .then(response => response.text())
      .then(data => {
        document.getElementById('productCount').innerText = data;
      });
  }

  updateProductCount();
  setInterval(updateProductCount, 1000);  // Atualiza a contagem de produtos a cada 1 segundo
</script>
</body>
</html>
)=====";

// SSID e Senha do seu roteador WiFi
const char* ssid = "INTELBRAS";
const char* password = "12345678";

ESP8266WebServer server(80);  // Servidor na porta 80
#define port 13

void handleRoot() {
  Serial.println("Acesso a página raiz");
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void handleUnlock() {
  Serial.println("Desbloquear");
  digitalWrite(port,HIGH);  // Ativa o relé para desbloquear
}

void handleLock() {
  Serial.println("Bloquear");
  digitalWrite(port,LOW);  // Desativa o relé para bloquear
}

void handleProductCount() {
  server.send(200, "text/plain", String(productCount));
}

void setup(void){
   Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(port,OUTPUT); 
  digitalWrite(port,LOW);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/unlock", handleUnlock);
  server.on("/lock", handleLock);
  server.on("/productCount", handleProductCount);  // Nova rota para obter a contagem de produtos

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop(void){
  while (Serial.available() > 0) {
    String serialData = Serial.readStringUntil('\n');  // Lê a linha da comunicação serial
    if (serialData.startsWith("Contador: ")) {
      productCount = serialData.substring(10).toInt();  // Extrai e converte a contagem de produtos
    }
  }
  server.handleClient();  // Lida com as requisições do cliente
}
