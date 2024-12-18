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


#define IN_3 5
#define IN_4 6

// Definições para os potenciômetros e o fim de curso
#define POT_1_MOT_2 A0
#define POT_2_MOT_3 A1
#define POT_3_MOT_4 A2
#define POT_4_MOT_5 A3
#define FIM_DE_CURSO 42

#define MOTOR_1_MAX 837  // Definir se esse máximo indica subida, descida, direita, esquerda
#define MOTOR_1_MIN 125
#define MOTOR_2_MAX 837
#define MOTOR_2_MIN 125
#define MOTOR_3_MAX 837
#define MOTOR_3_MIN 125
#define MOTOR_4_MAX 837
#define MOTOR_4_MIN 125
#define MOTOR_5_MAX 837
#define MOTOR_5_MIN 125

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

double set_point_mot_1, set_point_mot_2, set_point_mot_3, set_point_mot_4, set_point_mot_5;
double input_garra, input_mot_1, input_mot_2, input_mot_3, input_mot_4;
double output_mot_1, output_mot_2, output_mot_3, output_mot_4;

// Criando objetos PID e linkando as variáveis
double Kp=2, Ki=5, Kd=0;
PID1 myPID(&input_garra, &output_mot_1, &set_point_mot_1, Kp, Ki, Kd, DIRECT);
PID2 myPID(&input_mot_1, &output_mot_2, &set_point_mot_2, Kp, Ki, Kd, DIRECT);
PID3 myPID(&input_mot_2, &output_mot_3, &set_point_mot_3, Kp, Ki, Kd, DIRECT);
PID4 myPID(&input_mot_3, &output_mot_4, &set_point_mot_4, Kp, Ki, Kd, DIRECT);
PID5 myPID(&input_mot_4, &output_mot_5, &set_point_mot_5, Kp, Ki, Kd, DIRECT);

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

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
  input_mot_1 = analogRead(POT_1_MOT_2);
  set_point_mot_2 = 512;
  input_mot_2 = analogRead(POT_1_MOT_2);
  set_point_mot_3 = 512;
  input_mot_3 = analogRead(POT_1_MOT_2);
  set_point_mot_4 = 512;
  input_mot_4 = analogRead(POT_1_MOT_2);
  set_point_mot_5 = 512;
  input_mot_1 = analogRead(POT_1_MOT_2);
  set_point_mot_2 = 512;

  // Ligando o PID
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = analogRead(PIN_INPUT);
  myPID.Compute();

  if (Input > MOTOR_3_MIN && Input < MOTOR_3_MAX)
  {
    if (Input > Setpoint)
    {
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    }
    else
    {
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
    }
  }
  else
  {
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
  }
  // Serial.print("Pot 2: ");
  // Serial.println(Input);
  Serial.print("Output: ");
  Serial.println(Output);
}


