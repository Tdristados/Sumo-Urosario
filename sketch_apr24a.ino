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

const int SLL = 12; // Sensor de Linea izquierdo
const int SLR = 11; // Sensor de Linea derecho

const int INIT = 13; 

#define PWML 10  // Potencia del motor izquierdo (valores entre 0-255)
#define LDIR 5  // Direccionamiento del motor izquierdo 
#define PWMR 4   // Potencia del motor derecho (valores entre 0-255)
#define RDIR 3   // Direccionamiento del motor derecho

int velmax = 255;
int velizq = 255;
int velder = 255;
int n = 0;

void setup() {
  Serial.begin(9600); // Inicia el puerto serial

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);

  pinMode(SLL, INPUT);
  pinMode(SLR, INPUT);

  pinMode(PWML, OUTPUT);
  pinMode(PWMR, OUTPUT);
  pinMode(LDIR, OUTPUT);
  pinMode(RDIR, OUTPUT);

  pinMode(INIT, INPUT);
}

void loop() {
  // INIT para inicializar 
  int inicializacion = digitalRead(INIT);
  
//while (inicialitation){

    // Función para medir la distancia
    int d1 = getDistance(trigPin1, echoPin1);
    int d2 = getDistance(trigPin1, echoPin2);
    int d3 = getDistance(trigPin1, echoPin3);
    int d4 = getDistance(trigPin1, echoPin4);
    
    int sensorValue1 = digitalRead(SLL);
    int sensorValue2 = digitalRead(SLR);


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

//}

/*------------ Funciones-------*/

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

// Función para imprimir distancias en cm [d1,d2,d3,d4]
void printing(int d1, int d2, int d3, int d4){
  Serial.print("[");
  Serial.print(d1);
  Serial.print(",");
  Serial.print(d2);
  Serial.print(",");
  Serial.print(d3);
  Serial.print(",");
  Serial.print(d4);
  Serial.println("]");
  }

// Función para controlar cada motor: Recibe el valor del 'pwm' y del 'dir'.
// pwm es un valor de potencia del motor entre 0 y 255
// dir es la dirección de giro del motor, ir hacía adelante es 1 y ir hacía atrás es 0
// Con la variable 'motor' identificamos si es el motor derecho (motor=1) o izquierdo (motor=0) 

void driveMotor(int motor, int pwm, int dir){
  if (motor){    //motor=1, es decir motor derecho
    analogWrite(PWMR, pwm);
    digitalWrite(RDIR, dir);
  }else{      //motor=0, es decir motor izquierdo
    analogWrite(PWML, pwm);
    digitalWrite(LDIR, dir);
  }
}

void avanzar(int pwm){
  pwm = pwm>=velmax? velmax:pwm; // Si de casualidad el valor se excede, se corrige
  driveMotor(PWML,pwm,1); // El motor izquierdo va hacía adelante con una potencia de pwm
  driveMotor(PWMR,pwm,1); // El motor derecho  va hacía adelante con una potencia de pwm
}

void retroceder(int pwm){
  pwm = pwm>=velmax? velmax:pwm; 
  driveMotor(PWML,pwm,0); 
  driveMotor(PWMR,pwm,0); 
}

// Gira pero es necesario saber qué pwms toma cada valor, yendo siempre hacía adelante ambos.
// Así, es posible girar a la derecha (pwml>pwmr) o a izquierda (pwml<pwmr)
void girar(int pwml, int pwmr){
  pwml = pwml>=velmax? velmax:pwml;
  pwmr = pwmr>=velmax? velmax:pwmr; 
  driveMotor(PWML,pwml,1);
  driveMotor(PWMR,pwmr,1);
}

// Se gira el robot de manera brusca, por lo tanto, una llanta va hacía el frente y la otra hacía atrás.
// De nuevo, es necesario cada pwm para cada uno.
// Si direccion = 1 el robot se voltea hacía la derecha, si es 0 hacía la izquierda 
void voltear(int direccion, int pwml, int pwmr){ //Hay que revisar cuánto gira
  pwml = pwml>=velmax? velmax:pwml;
  pwmr = pwmr>=velmax? velmax:pwmr;  
  if (direccion){ // si direccion = 1, entonces el motor izquierdo va hacia adelante y el derecho hacía atrás
    driveMotor(PWML,pwml,1);
    driveMotor(PWMR,pwmr,0);
  }else{     // si direccion = 0, entonces el motor izquierdo va hacia adelante y el derecho hacía atrás
    driveMotor(PWML,pwml,0);
    driveMotor(PWMR,pwmr,1);
  }
}

// Función, protocolo de seguridad para evitar que se salga el robot de la pista
void protocoloReversa(){
  // La idea es ir hacía atrás y dar vuelta para ir hacia el centro
  retroceder(velmax);
  delay(50);
  voltear(1,velmax,velmax/2);  // que la llanta derecha vaya hacía atrás, pero con menos fuerza
}
