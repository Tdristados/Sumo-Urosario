/* Sensor ultrasónico HC-SR04
   Pines:
   - VCC: +5VDC
   - Trig: Trigger (INPUT) - Pin 11
   - Echo: Echo (OUTPUT) - Pin 12
   - GND: GND
*/

const int trigPin1 = 2; // Disparador (Trigger) para el primer sensor
const int echoPin1 = 6; // Eco (Echo) para el primer sensor
const int echoPin2 = 7; // Eco (Echo) para el segundo sensor
const int echoPin3 = 8; // Eco (Echo) para el tercer sensor
const int echoPin4 = 9; // Eco (Echo) para el tercer sensor

#define PWMA 12
#define AIN2 11
#define AIN1 10
#define PWMB 5
#define BIN2 4
#define BIN1 3

void setup() {
  Serial.begin(9600); // Inicia el puerto serial
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
}

void loop() {
  // Función para medir la distancia
  int d1 = getDistance(trigPin1, echoPin1);
  int d2 = getDistance(trigPin1, echoPin2);
  int d3 = getDistance(trigPin1, echoPin3);
  int d4 = getDistance(trigPin1, echoPin4);

  // Imprime las distancias en centímetros
  Serial.print("[");
  Serial.print(d1);
  Serial.print(",");
  Serial.print(d2);
  Serial.print(",");
  Serial.print(d3);
  Serial.print(",");
  Serial.print(d4);
  Serial.println("]");
  delay(1000); // Espera 1 segundo antes de la siguiente lectura


  if(d1==0)
  {
    if(d2==0)
    {
       if(d3==0)
       {
        if(d4==0)
        { //1
        Serial.print("caso 1");
          
        }
        else
        { //2
          Serial.print("caso 2");
        }
       }
       else
       { 
        if(d4==0)
        { //3
          Serial.print("caso 3");
        }
        else
        { //4
          Serial.print("caso 4");
        }
       }
    }else{
      if(d3==0){
        if(d4==0){ //5
        Serial.print("caso 5");
        }
       }else{
        if(d4==0){ //7
          Serial.print("caso 7");
        }
       }
    }
  }
  else
  {
    if(d2==0)
    {
       if(d3==0)
       {
        if(d4==0)
        { //9
          Serial.print("caso 9");
        }
       }
       else
       {
       }
    }
    else
    {
      if(d3==0)
      {
        if(d4==0)
        { //13
          Serial.print("caso 13");
        }
       }
       else
       {
       }
    }
  }
}

// Función para obtener la distancia
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 5000);
  float cm = duration / 58.0; // Conversión a centímetros
  if(cm>40) return 0;
  if(cm>0) return 1;
  
}



