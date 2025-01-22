/*
Projeto de Sistemas Mecatrônicos
Alunos: Jorge Palma

*/

#include <PID_v1.h>

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
double output_mot_1_open, output_mot_1_close, output_mot_2_up, output_mot_2_down, output_mot_3_up, output_mot_3_down, output_mot_4_up, output_mot_4_down, output_mot_5_left, output_mot_5_right;

// Criando objetos PID e linkando as variáveis
double kp_mot_1 = 0, kp_mot_2 = 0, kp_mot_3 = 4, kp_mot_4 = 4, kp_mot_5 = 0;
double ki_mot_1 = 0, ki_mot_2 = 0, ki_mot_3 = 3, ki_mot_4 = 3, ki_mot_5 = 0;
double kd_mot_1 = 0, kd_mot_2 = 0, kd_mot_3 = 3, kd_mot_4 = 3, kd_mot_5 = 0;



PID PID_Mot_1_open(&input_garra, &output_mot_1_open, &set_point_mot_1, kp_mot_1, ki_mot_1, kd_mot_1, DIRECT);
PID PID_Mot_1_close(&input_garra, &output_mot_1_close, &set_point_mot_1, kp_mot_1, ki_mot_1, kd_mot_1, REVERSE);

PID PID_Mot_2_up(&input_mot_2, &output_mot_2_up, &set_point_mot_2, kp_mot_2, ki_mot_2, kd_mot_2, DIRECT);
PID PID_Mot_2_down(&input_mot_2, &output_mot_2_down, &set_point_mot_2, kp_mot_2, ki_mot_2, kd_mot_2, REVERSE);

PID PID_Mot_3_up(&input_mot_3, &output_mot_3_up, &set_point_mot_3, kp_mot_3, ki_mot_3, kd_mot_3, DIRECT);
PID PID_Mot_3_down(&input_mot_3, &output_mot_3_down, &set_point_mot_3, kp_mot_3, ki_mot_3, kd_mot_3, REVERSE);

PID PID_Mot_4_up(&input_mot_4, &output_mot_4_up, &set_point_mot_4, kp_mot_4, ki_mot_4, kd_mot_4, DIRECT);
PID PID_Mot_4_down(&input_mot_4, &output_mot_4_down, &set_point_mot_4, kp_mot_4, ki_mot_4, kd_mot_4, REVERSE);

PID PID_Mot_5_left(&input_mot_5, &output_mot_5_left, &set_point_mot_5, kp_mot_5, ki_mot_5, kd_mot_5, DIRECT);
PID PID_Mot_5_right(&input_mot_5, &output_mot_5_right, &set_point_mot_5, kp_mot_5, ki_mot_5, kd_mot_5, REVERSE);

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
  

  // Configuração dos PIDs
  PID_Mot_1_open.SetMode(AUTOMATIC);
  PID_Mot_1_close.SetMode(AUTOMATIC);
  PID_Mot_2_up.SetMode(AUTOMATIC);
  PID_Mot_2_down.SetMode(AUTOMATIC);
  PID_Mot_3_up.SetMode(AUTOMATIC);
  PID_Mot_3_down.SetMode(AUTOMATIC);
  PID_Mot_4_up.SetMode(AUTOMATIC);
  PID_Mot_4_down.SetMode(AUTOMATIC);
  PID_Mot_5_left.SetMode(AUTOMATIC);
  PID_Mot_5_right.SetMode(AUTOMATIC);

  PID_Mot_1_open.SetOutputLimits(0, 255);
  PID_Mot_1_close.SetOutputLimits(0, 255);
  PID_Mot_2_up.SetOutputLimits(0, 255);
  PID_Mot_2_down.SetOutputLimits(0, 255);
  PID_Mot_3_up.SetOutputLimits(0, 255);
  PID_Mot_3_down.SetOutputLimits(0, 255);
  PID_Mot_4_up.SetOutputLimits(0, 255);
  PID_Mot_4_down.SetOutputLimits(0, 255);
  PID_Mot_5_left.SetOutputLimits(0, 255);
  PID_Mot_5_right.SetOutputLimits(0, 255);

  // Definir o setpoint inicial
  // set_point_mot_1 = 430; // Defina o valor desejado
  set_point_mot_2 = 512; // Defina o valor desejado
  set_point_mot_3 = 512; // Defina o valor desejado
  set_point_mot_4 = 420; // Defina o valor desejado
  set_point_mot_5 = 512; // Defina o valor desejado

  
}

void loop()
{
  input_mot_3 = analogRead(POT_2_MOT_3);
  PID_Mot_3_up.Compute();
  PID_Mot_3_down.Compute();

  input_mot_4 = analogRead(POT_3_MOT_4);
  PID_Mot_4_up.Compute();
  PID_Mot_4_down.Compute();

  if (input_mot_3 > MOTOR_3_MIN && input_mot_3 < MOTOR_3_MAX)
  {
    if (input_mot_3 < set_point_mot_3)
    {
     Serial.print("if3  input:   ");
     Serial.print(input_mot_3);
     Serial.print("   ||  output:   ");
     Serial.println(output_mot_3_up);
      analogWrite(DRIVER_2_IN_1, output_mot_3_up);
      analogWrite(DRIVER_2_IN_2, 0);
    }
    else if (input_mot_3 > set_point_mot_3)
    {
     Serial.print("else3  input:   ");
     Serial.print(input_mot_3);
     Serial.print("   ||  output:   ");
     Serial.println(output_mot_3_down);
      analogWrite(DRIVER_2_IN_1, 0);
      analogWrite(DRIVER_2_IN_2, output_mot_3_down);
    }
  }
  else
  {
    digitalWrite(DRIVER_2_IN_1, LOW);
    digitalWrite(DRIVER_2_IN_2, LOW);
  }


  if (input_mot_4 > MOTOR_4_MIN && input_mot_4 < MOTOR_4_MAX)
  {
    if (input_mot_4 < set_point_mot_4)
    {
     Serial.print("if4  input:   ");
     Serial.print(input_mot_4);
     Serial.print("   ||  output:   ");
     Serial.println(output_mot_4_up);
      analogWrite(DRIVER_2_IN_3, output_mot_4_up);
      analogWrite(DRIVER_2_IN_4, 0);
    }
    else if (input_mot_4 > set_point_mot_4)
    {
     Serial.print("else4  input:   ");
     Serial.print(input_mot_4);
     Serial.print("   ||  output:   ");
     Serial.println(output_mot_4_down);
      analogWrite(DRIVER_2_IN_3, 0);
      analogWrite(DRIVER_2_IN_4, output_mot_4_down);
    }
  }
  else
  {
    digitalWrite(DRIVER_2_IN_3, LOW);
    digitalWrite(DRIVER_2_IN_4, LOW);
  }

  delay(10); // Para facilitar a leitura do serial
}
