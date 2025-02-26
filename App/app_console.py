import serial
import time

# Definição dos limites de ângulo para cada motor
ANGLE_LIMITS = {
    1: (0, 360),  # Motor 1 é livre
    2: (36, 316),  # Motor 2 tem limites de 36° a 316°
    3: (44, 336),  # Motor 3 tem limites de 44° a 336°
    4: (131, 228),  # Motor 4 tem limites de 131° a 228°
    5: (34, 323),  # Motor 5 tem limites de 34° a 323°
}


def angle_to_value(angle):
    """Converte um ângulo (0° a 360°) para um valor entre 0 e 1023."""
    return int((angle / 360) * 1023)


def get_motor_setpoints():
    """Solicita ao usuário os ângulos para os 5 motores e verifica se estão na faixa permitida."""
    setpoints = []
    for i in range(1, 6):
        min_angle, max_angle = ANGLE_LIMITS[i]  # Obtém os limites do motor
        while True:
            try:
                angle = float(
                    input(
                        f"Enter the setpoint angle for motor {i} ({min_angle}° to {max_angle}°): "
                    )
                )
                if min_angle <= angle <= max_angle:
                    value = angle_to_value(angle)  # Converte para o intervalo 0-1023
                    setpoints.append(value)
                    break
                else:
                    print(
                        f"Invalid angle! Motor {i} accepts angles between {min_angle}° and {max_angle}°. Try again."
                    )
            except ValueError:
                print("Invalid input! Please enter a valid number.")
    return setpoints


def conectar_arduino(port, baudrate, tentativas=5):
    """Tenta conectar ao Arduino e retorna a instância Serial"""
    for _ in range(tentativas):
        try:
            ser = serial.Serial(port, baudrate, timeout=2)
            time.sleep(2)  # Aguarda inicialização do Arduino
            print("Conectado ao Arduino!")
            return ser
        except serial.SerialException:
            print("Tentando reconectar...")
            time.sleep(2)
    print("Falha ao conectar ao Arduino.")
    return None


def send_to_arduino(ser, setpoints):
    """Envia os setpoints para o Arduino via porta serial e aguarda resposta."""
    if ser is None or not ser.is_open:
        print("Erro: Porta serial não está aberta.")
        return False

    try:
        message = ",".join(map(str, setpoints)) + "\n"
        print(f"Sending: {repr(message)}")
        ser.write(message.encode())
        time.sleep(0.1)

        # Aguarda resposta do Arduino
        response = ser.readline().decode().strip()
        if response:
            print(f"Arduino response: {response}")
            return True
        else:
            print(
                "No response from Arduino. Check the connection and the Arduino code."
            )
            return False
    except serial.SerialException as e:
        print(f"Erro na comunicação serial: {e}")
        return False


def main():
    print("Welcome to the setpoints sending program for Arduino Mega!")
    port = input("Enter the COM port for communication (e.g., COM8): ")
    baudrate = 9600  # Taxa de transmissão padrão
    ser = conectar_arduino(port, baudrate)

    while True:
        setpoints = get_motor_setpoints()
        confirm = input(
            f"The setpoints are {setpoints} (converted values). Do you want to send them? (y/n): "
        ).lower()
        if confirm == "y":
            sucesso = send_to_arduino(ser, setpoints)
            if not sucesso:
                print("Tentando reconectar ao Arduino...")
                ser = conectar_arduino(port, baudrate)  # Tenta reconectar
        else:
            print("Restarting setpoints entry.")

        repeat = input("Do you want to send new setpoints? (y/n): ").lower()
        if repeat != "y":
            print("Exiting the program.")
            if ser and ser.is_open:
                ser.close()
            break


if __name__ == "__main__":
    main()
