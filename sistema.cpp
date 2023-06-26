#include <Servo.h>
#include <IRremote.h>
#include <LiquidCrystal.h>

#define CONTROL 11
#define SERVON 9
#define LEDVERDE 13
#define LEDROJO 12
Servo miServo;

int end = 180;
bool activar_sistema = true;
String estacion = "";
bool bandera_msj = false;
bool in_run = true;
bool cambio_led = false;


LiquidCrystal lcd(4,3,5,6,7,8);


// C++ code
//
void setup()
{
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  miServo.attach(SERVON); 
  Serial.begin(9600);
  lcd.begin(16,2);
  IrReceiver.begin(CONTROL, DISABLE_LED_FEEDBACK); 
}

void loop()
{
 
  if (in_run){
    int temp = detectar_temperatura();
  	verificar_rangos_temperatura(temp);
    manejo_leds(cambio_led);
    cambio_led = false;
  }                    
  if(IrReceiver.decode()){
    detectar_ir();
    in_run = run_sistema();
    	
  }
}

void detectar_ir(){
  int res = IrReceiver.decodedIRData.decodedRawData; // Print "old" raw data
  IrReceiver.resume(); 
    
    //REFACTORIZAR , NO ES SOLO APAGAR Y PRENDER
	// ES INDICAR CON LOS BOTONES DEL CONTROL REMOTO EN QUE ESTACION DEL AÑO ESTAMOS.
  if(IrReceiver.decodedIRData.decodedRawData == 0xFF00BF00){
     activar_sistema = !activar_sistema;
  }
}

bool run_sistema(){
  if (activar_sistema == HIGH){
 
    Serial.println("Prendemos Sistema");
    miServo.attach(SERVON);
    
    return true;
    	
  }else{
    Serial.println("Apagamos Sistema");
    lcd.clear();
    miServo.detach();
    apagar_leds();
    return false;
  }
}
void verificar_rangos_temperatura(int temperatura){
  if (temperatura <=10){
    imprimir_lcd("invierno",temperatura);
  }else if(temperatura > 10 && temperatura < 19){
    imprimir_lcd("otonio",temperatura);
  }else if (temperatura > 19 && temperatura < 26){
    imprimir_lcd("primavera",temperatura);
  }else if (temperatura > 26 && temperatura <60){
    imprimir_lcd("verano",temperatura);
  }else if(temperatura > 60){
  	imprimir_lcd("ALERTA INCENDIO",temperatura);
    cambio_led = true;
    movimiento_servo();
    
  }
}

int detectar_temperatura(){
  int temp = analogRead(A0);
  int conversor = map(temp,20,358,-40,125);
  return conversor;
}
void imprimir_lcd(String estacion,int temp){
  String str = estacion + " t:"+String(temp)+" C";
  String alert = "ALERTA! t:"+String(temp)+" C";
  	lcd.clear();
    lcd.print(str);
  	delay(300);
  if(temp > 60){
    
  	lcd.setCursor(0,1);
    lcd.print(alert);
    delay(2000);
  };
	
}
void movimiento_servo(){
 	
    miServo.write(0); 
    delay(400);      
    miServo.write(end);
    delay(400);      
}
void manejo_leds(bool cambio_led){
  if(cambio_led == true){
  	digitalWrite(LEDROJO,HIGH);
    digitalWrite(LEDVERDE,LOW);
  }else{
  	digitalWrite(LEDVERDE,HIGH);
    digitalWrite(LEDROJO,LOW);
  }
}
void apagar_leds(){
	digitalWrite(LEDVERDE,LOW);
  	digitalWrite(LEDROJO,LOW);

}
