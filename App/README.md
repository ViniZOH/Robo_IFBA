# Arduino Setpoints GUI Application

This application provides a graphical interface for sending motor setpoints to an Arduino Mega via a serial connection (e.g., COM port). The interface allows users to enter values for five motors and validate the inputs before sending them to the Arduino.

## Features
- User-friendly graphical interface built with Kivy.
- Validation of motor setpoints (values must be integers between 0 and 1023).
- Configurable serial communication port.
- Error handling for invalid inputs and serial communication issues.
- Popup messages for success and error notifications.

## Prerequisites
1. **Python 3.7 or later** installed on your system.
2. **Required Python packages:**

   Install them using the `requirements.txt` file:
   ```bash
   pip install -r requirements.txt
   ```
3. An Arduino Mega connected to your computer and configured to receive serial data.

## How to Use
1. Clone or download this repository.
2. Open a terminal and navigate to the folder containing the script.
3. Run the script:
   ```bash
   python <script_name>.py
   ```
4. In the application window:
   - Enter the COM port of your Arduino (e.g., `COM8`).
   - Enter the setpoint values for the five motors (values between 0 and 1023).
   - Click the "Send to Arduino" button to validate the inputs and send them to the Arduino.
5. Check for success or error messages displayed in popup windows.

## Notes
- Ensure the Arduino is connected to the correct COM port.
- The Arduino must be programmed to handle the incoming data in the format sent by the application (comma-separated values).

## Example Output
If all inputs are valid and the Arduino is connected properly, the application will display:
```
Setpoints sent: [value1, value2, value3, value4, value5]
```

## Troubleshooting
- **Invalid Input:** Ensure all motor setpoints are integers within the range of 0 to 1023.
- **Serial Port Error:** Verify the COM port is correct and not in use by another application.
- **Kivy Errors:** Ensure the Kivy package is correctly installed.

## License
This project is open-source and available under the [MIT License](LICENSE).

---
Feel free to modify or expand this script to suit your specific needs!