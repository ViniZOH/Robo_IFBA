/********************************************************
Projeto de Sistemas Mecatrônicos
 ********************************************************/

#include <PID_v1.h>

// Definições para os drivers
#define DRIVER_1_IN_1  2      // Motor 1 
#define DRIVER_1_IN_2  3      // Motor 1
#define DRIVER_1_IN_3  4      // Motor 2
#define DRIVER_1_IN_4  5      // Motor 2
#define DRIVER_2_IN_1  6      // Motor 3
#define DRIVER_2_IN_2  7      // Motor 3
#define DRIVER_2_IN_3  8      // Motor 4
#define DRIVER_2_IN_4  9      // Motor 4
#define DRIVER_3_IN_1  10     // Motor 5
#define DRIVER_3_IN_2  11     // Motor 5
#define DRIVER_3_IN_3  44     // RESERVA
#define DRIVER_3_IN_4  46     // RESERVA

// Definições para os potenciômetros e o fim de curso
#define POT_1_MOT_2 A0
#define POT_2_MOT_3 A1
#define POT_3_MOT_4 A2
#define POT_4_MOT_5 A3
#define FIM_DE_CURSO 42

#define MOTOR_1_MAX 837  // Definir se esse máximo indica subida, descida, direita, esquerda
#define MOTOR_1_MIN 125
#define MOTOR_2_MAX 905
#define MOTOR_2_MIN 135
#define MOTOR_3_MAX 837
#define MOTOR_3_MIN 125
#define MOTOR_4_MAX 649
#define MOTOR_4_MIN 371
#define MOTOR_5_MAX 920
#define MOTOR_5_MIN 93


double set_point_mot_1, set_point_mot_2, set_point_mot_3, set_point_mot_4, set_point_mot_5;
double input_garra, input_mot_2, input_mot_3, input_mot_4, input_mot_5;
double output_mot_1, output_mot_2, output_mot_3, output_mot_4, output_mot_5;

// Criando objetos PID e linkando as variáveis
double Kp=20, Ki=3, Kd=3;
PID myPID1(&input_garra, &output_mot_1, &set_point_mot_1, Kp, Ki, Kd, DIRECT);
PID myPID2(&input_mot_2, &output_mot_2, &set_point_mot_2, Kp, Ki, Kd, DIRECT);
PID myPID3(&input_mot_3, &output_mot_3, &set_point_mot_3, Kp, Ki, Kd, DIRECT);
PID myPID4(&input_mot_4, &output_mot_4, &set_point_mot_4, Kp, Ki, Kd, DIRECT);
PID myPID5(&input_mot_5, &output_mot_5, &set_point_mot_5, Kp, Ki, Kd, DIRECT);

void setup()
{
  Serial.begin(9600);
  pinMode(DRIVER_1_IN_1, OUTPUT);
  pinMode(DRIVER_1_IN_2, OUTPUT);
  pinMode(DRIVER_1_IN_3, OUTPUT);
  pinMode(DRIVER_1_IN_4, OUTPUT);
  pinMode(DRIVER_2_IN_1, OUTPUT);
  pinMode(DRIVER_2_IN_2, OUTPUT);
  pinMode(DRIVER_2_IN_3, OUTPUT);
  pinMode(DRIVER_2_IN_4, OUTPUT);
  pinMode(DRIVER_3_IN_1, OUTPUT);
  pinMode(DRIVER_3_IN_2, OUTPUT);
  pinMode(DRIVER_3_IN_3, OUTPUT);
  pinMode(DRIVER_3_IN_4, OUTPUT);

  // Inicializando as variáveis
  //input_mot_1 = analogRead(POT_1_MOT_2);
//  set_point_mot_2 = 512;
//  input_mot_2 = analogRead(POT_1_MOT_2);
  set_point_mot_3 = 512;
  input_mot_3 = analogRead(POT_2_MOT_3);
  set_point_mot_4 = 400;
  input_mot_4 = analogRead(POT_3_MOT_4);
//  set_point_mot_5 = 512;
//  input_mot_1 = analogRead(POT_1_MOT_2);
//  set_point_mot_2 = 512;

  // Ligando o PID
//  myPID1.SetMode(AUTOMATIC);
//  myPID2.SetMode(AUTOMATIC);
  myPID3.SetMode(AUTOMATIC);
  myPID4.SetMode(AUTOMATIC);
//  myPID5.SetMode(AUTOMATIC);
}

void loop()
{
  input_mot_3 = analogRead(POT_2_MOT_3);
  myPID3.Compute();
  input_mot_4 = analogRead(POT_3_MOT_4);
  myPID4.Compute();

  if (input_mot_3 > MOTOR_3_MIN && input_mot_3 < MOTOR_3_MAX)
  {
    if (input_mot_3 < set_point_mot_3)
    {
      Serial.print("if  input:   ");
      Serial.print(input_mot_3);
      Serial.print("   ||  output:   ");
      Serial.println(output_mot_3);
      analogWrite(DRIVER_2_IN_1, 0);
      analogWrite(DRIVER_2_IN_2, output_mot_3);
    }
    else if (input_mot_3 > set_point_mot_3)
    {
      Serial.print("else  input:   ");
      Serial.print(input_mot_3);
      Serial.print("   ||  output:   ");
      Serial.println(output_mot_3);
      analogWrite(DRIVER_2_IN_1, output_mot_3);
      analogWrite(DRIVER_2_IN_2, 0);
    }
  }
  else // Dentro do setpoint
  {
    digitalWrite(DRIVER_2_IN_1, LOW);
    digitalWrite(DRIVER_2_IN_2, LOW);
  }

  if (input_mot_4 > MOTOR_4_MIN && input_mot_4 < MOTOR_4_MAX)
  {
    if (input_mot_4 < set_point_mot_4)
    {
//      Serial.print("if  input:   ");
//      Serial.print(input_mot_4);
//      Serial.print("   ||  output:   ");
//      Serial.println(output_mot_4);
      analogWrite(DRIVER_2_IN_3, 0);
      analogWrite(DRIVER_2_IN_4, output_mot_4);
    }
    else if (input_mot_4 > set_point_mot_4)
    {
//      Serial.print("else  input:   ");
//      Serial.print(input_mot_4);
//      Serial.print("   ||  output:   ");
//      Serial.println(output_mot_4);
      analogWrite(DRIVER_2_IN_3, output_mot_4);
      analogWrite(DRIVER_2_IN_4, 0);
    }
  }
  else
  {
    digitalWrite(DRIVER_2_IN_3, LOW);
    digitalWrite(DRIVER_2_IN_4, LOW);
  }

  
}
