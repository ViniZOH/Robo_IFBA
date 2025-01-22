import serial
import time


def get_motor_setpoints():
    """Prompts the user for setpoints for 5 motors."""
    setpoints = []
    for i in range(1, 6):
        while True:
            try:
                value = int(
                    input(
                        f"Enter the setpoint value for motor {i} (between 0 and 1023): "
                    )
                )
                if 0 <= value <= 1023:
                    setpoints.append(value)
                    break
                else:
                    print("Value out of allowed range. Please try again.")
            except ValueError:
                print("Invalid input! Please enter an integer.")
    return setpoints


def send_to_arduino(port, baudrate, setpoints):
    """Sends the setpoints to the Arduino via serial port."""
    try:
        with serial.Serial(port, baudrate, timeout=2) as ser:
            time.sleep(2)  # Wait for Arduino initialization
            message = ",".join(map(str, setpoints)) + "\n"
            ser.write(message.encode())
            print(f"Setpoints sent: {message.strip()}")
    except serial.SerialException as e:
        print(f"Error communicating with the serial port: {e}")


def main():
    print("Welcome to the setpoints sending program for Arduino Mega!")
    port = input("Enter the COM port for communication (e.g., COM8): ")
    baudrate = 9600  # Default baud rate

    while True:
        setpoints = get_motor_setpoints()
        confirm = input(
            f"The setpoints are {setpoints}. Do you want to send them? (y/n): "
        ).lower()
        if confirm == "y":
            print("Sending info...")
            # send_to_arduino(port, baudrate, setpoints)
        else:
            print("Restarting setpoints entry.")

        repeat = input("Do you want to send new setpoints? (y/n): ").lower()
        if repeat != "y":
            print("Exiting the program.")
            break


if __name__ == "__main__":
    main()
