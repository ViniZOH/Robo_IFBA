#include <PID_v1.h>

// Definições para o driver do motor
#define DRIVER_IN_1 2 // Controle da direção 1
#define DRIVER_IN_2 3 // Controle da direção 2

// Definições para o potenciômetro
#define POT_PIN A0 // Leitura da posição do motor

// Variáveis do PID
double input_mot, set_point_mot, output_pid_below, output_pid_above;

// Constantes do PID
double Kp_below = 20, Ki_below = 3, Kd_below = 3; // Constantes para valores abaixo do setpoint
double Kp_above = 25, Ki_above = 4, Kd_above = 5; // Constantes para valores acima do setpoint

// Criação dos objetos PID
PID pidBelow(&input_mot, &output_pid_below, &set_point_mot, Kp_below, Ki_below, Kd_below, DIRECT);
PID pidAbove(&input_mot, &output_pid_above, &set_point_mot, Kp_above, Ki_above, Kd_above, REVERSE);

void setup()
{
  // Inicialização dos pinos
  pinMode(DRIVER_IN_1, OUTPUT);
  pinMode(DRIVER_IN_2, OUTPUT);
  
  // Configuração do serial para depuração
  Serial.begin(9600);

  // Configuração dos PIDs
  pidBelow.SetMode(AUTOMATIC); // PID para valores abaixo do setpoint
  pidAbove.SetMode(AUTOMATIC); // PID para valores acima do setpoint
  pidBelow.SetOutputLimits(0, 255); // Saída limitada ao intervalo do PWM
  pidAbove.SetOutputLimits(0, 255); // Saída limitada ao intervalo do PWM

  // Definir o setpoint inicial
  set_point_mot = 430; // Defina o valor desejado
}

void loop()
{
  // Leitura do potenciômetro
  input_mot = analogRead(POT_PIN);

  // Determinar qual PID deve atuar
  if (input_mot < set_point_mot)
  {
    // PID para valores abaixo do setpoint
    pidBelow.Compute(); // Calcula o PID abaixo
    analogWrite(DRIVER_IN_1, output_pid_below); // Gira o motor para aumentar o valor
    analogWrite(DRIVER_IN_2, 0);
  }
  else if (input_mot > set_point_mot)
  {
    // PID para valores acima do setpoint
    pidAbove.Compute(); // Calcula o PID acima
    analogWrite(DRIVER_IN_1, 0);
    analogWrite(DRIVER_IN_2, output_pid_above); // Gira o motor para diminuir o valor
  }
  else
  {
    // Quando o valor está no setpoint, desliga o motor
    digitalWrite(DRIVER_IN_1, LOW);
    digitalWrite(DRIVER_IN_2, LOW);
  }

  // Depuração
  Serial.print("Input: ");
  Serial.println(input_mot);
  Serial.print("Setpoint: ");
  Serial.println(set_point_mot);
  Serial.print("Output Below: ");
  Serial.println(output_pid_below);
  Serial.print("Output Above: ");
  Serial.println(output_pid_above);
  delay(100); // Para facilitar a leitura do serial
}
