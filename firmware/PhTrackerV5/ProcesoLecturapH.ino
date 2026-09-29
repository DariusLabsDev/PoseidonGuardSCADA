
void procesoLecturaPh(){
  int analogValue = analogRead(PH_PIN);  // valor entre 0 y 1023
  float pHLeidoActual =  map(analogValue, 0, 1023, 14.0, 0.0);
  

  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print("//");
  Serial.print("pH: ");
  Serial.println(pHLeidoActual, 1);

  if( pHLeidoActual != pHLeidoAnterior){
    pHLeidoAnterior = pHLeidoActual;
    lcd.setCursor(2, 1);
    lcd.print("    ");
    lcd.setCursor(1, 1);
    lcd.print(pHLeidoActual, 1);
  }
  

  delay(500);  
}



float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




String peticionHttp() {
  Serial.println("Entregando Peticion");

  String phNivel = String(pHLeidoAnterior);
  String URLPETICION = "http://192.168.4.1/guardarPhLeido?ph=" + phNivel;

  http.begin(client, URLPETICION);  // ¡OJO! Es HTTP, no HTTPS
  http.addHeader("Content-Type", "application/json");
  
  int httpCode = http.GET();
  Serial.print("httpCode: ");
  Serial.println(httpCode);

  if (httpCode == 200) {
    respuesta = http.getString();
    Serial.println("Respuesta del servidor: " + respuesta);
    http.end();
    return respuesta;
  } else {
    Serial.println("Error en la petición HTTP");
    http.end();
    return "";
  }
}
