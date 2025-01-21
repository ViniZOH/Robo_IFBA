# Principais Modificações

## 21/01/2025 -- Aplicadas no ultimo codigo

-------------------------------------------------------
Principais Problemas
-------------------------------------------------------

1- Desativação do motor fora do range de segurança: Quando o input_mot está fora dos limites de segurança, os motores são desligados, mas o setpoint do PID não é atualizado ou monitorado ativamente.
2- Inconsistência na direção do controle: O controle parece atuar apenas em um sentido (subindo até o setpoint), mas não reativa para corrigir valores que excedam o setpoint.
3- Falta de condições dinâmicas no PID: O PID precisa calcular continuamente e ajustar o motor, independentemente do valor atual de input_mot.
-------------------------------------------------------
Sugestões de Correções
-------------------------------------------------------
1. Atualizar o cálculo do PID continuamente:
O PID deve ser acionado mesmo quando input_mot está fora do intervalo de segurança, garantindo que o sistema tente corrigir para o setpoint.
2. Adicionar lógica para ativar o motor corretamente:
A direção do motor deve ser determinada pela diferença entre input_mot (valor lido no  potenciometro) e set_point_mot (valor alvo do PID).
Lógica Sugerida:
1- Se input_mot < set_point_mot, o motor deve girar em uma direção (para aproximar-se do alvo).
2- Se input_mot > set_point_mot, o motor deve girar na direção oposta (para aproximar-se do alvo).
3- Se input_mot estiver próximo o suficiente do set_point_mot (dentro de uma margem de tolerância), o motor deve parar.
