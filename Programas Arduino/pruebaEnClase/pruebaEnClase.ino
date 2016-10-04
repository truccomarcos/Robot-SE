#include <DCMotor.h>
#include <Ping.h>

#define minimoGris 80 //Valor menor a 100 NEGRO
                       // Gris Valores entre 100 y 400
#define maximoGris 750 //Valor mayor a 400 BLANCO
# define distancia 15
float s2, s3;
PingSensor ping(A1);
int dir;
DCMotor motor0(M0_EN, M0_D0, M0_D1);
DCMotor motor1(M1_EN, M1_D0, M1_D1);

void buscarAtacar();
void comenzarAtaque();
void irAlCentro();

void setup()
{
  Serial.begin(115200);
  pinMode(25, INPUT);
  digitalWrite(25, HIGH);
  motor0.setClockwise(false);
/*digitalWrite(11, LOW);
  digitalWrite(10, LOW);*/
  //comenzarAtaque();
  
}
  
void loop()
{
  motor0.setSpeed(50.0);
  motor1.setSpeed(-50.0);
  s2 = analogRead(2); //VISTO DE FRENTE S2 = DERECHO S3 = IZQUIERDO
  s3 = analogRead(3);
  delay(100);
  if( (s2 > maximoGris) || (s3 > maximoGris) )
  { 
    //marchaAtras();
    motor0.brake();
    motor1.brake();
    delay(1000);
    motor0.setSpeed(-50.0);
    motor1.setSpeed(50.0);
    delay(1000); 
    motor0.brake();
    motor1.brake();
     
  }
  //irAlCentro();
  //buscarAtacar();  
}

void comenzarAtaque()
{
  motor0.setSpeed(-50.0); //90
  motor1.setSpeed(-50.0);
  delay(500);
  motor0.setSpeed(0.0);
  motor1.setSpeed(0.0);
  delay(500);
  dir = decidirDireccion();
  if (dir == 0)
  {
    giro(-1);
  }
  else if (dir == 1)
  {
    giro(1);    
  }  
  buscarEmbestir(dir);  
}

void irAlCentro()
{
  motor0.setSpeed(40.0);
  motor1.setSpeed(-95.0); //Revisar giro   
  if( (s2 >= minimoGris ) && ( s2 <= maximoGris) )
  {
    motor0.brake();
  }  
  else if ( (s3 >= minimoGris ) && ( s3 <= maximoGris) )
  {
    motor1.brake(); //
    if ( (s2 < minimoGris ) && ( s2 > maximoGris) ) motor0.setSpeed(70.0);   
  }     
}  

void buscarAtacar()
{
  if (ping.measureCM()>distancia) 
  {
    motor0.setSpeed(70.0); 
    motor1.setSpeed(-70.0);    
  }
  else
  {
    motor0.setSpeed(-95.0); //95
    motor1.setSpeed(-95.0);
    delay(3000);
    motor0.setSpeed(0.0);
    motor1.setSpeed(0.0);
  }
}

void marchaAtras()
{
  motor0.setSpeed(0.0); // 95
  motor1.setSpeed(0.0);
  delay(1000);
  motor0.setSpeed(-50.0); // 95
  motor1.setSpeed(-50.0);
  delay(800); 
  buscarAtacar();
}
 

int decidirDireccion()
{
  int valor = random(0, 2);
  return valor;
}

void giro(int sentido) // -1 para izquierda,1 para derecha
{
  float velocidad1=95.0, velocidad2 = 45.0;
  motor0.setSpeed(sentido * 75.0);
  motor1.setSpeed(sentido * -75.0);
  delay(300);
  if (sentido == -1)
  {
    motor0.setSpeed(velocidad1);
    motor1.setSpeed(velocidad2);
  }
  else //if(sentido == 1)
  {
    motor0.setSpeed(velocidad2);
    motor1.setSpeed(velocidad1);
  }
  delay(2000);
  motor0.setSpeed(0.0);
  motor1.setSpeed(0.0);  
}

void buscarEmbestir(int sentido)
{
    if (ping.measureCM()>distancia) 
  {
    if (sentido == 0)
    {
      motor0.setSpeed(70.0);
      motor1.setSpeed(-70.0);
    }
    else //if (sentido == 1)
    {
      motor0.setSpeed(-70.0);
      motor1.setSpeed(70.0);   
    }      
  }
  else
  {
    motor0.setSpeed(-95.0);
    motor1.setSpeed(-95.0);
    delay(2000);
    motor0.setSpeed(0.0);
    motor1.setSpeed(0.0);
  } 
}


