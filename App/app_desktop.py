from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.popup import Popup
import serial
import time


class ArduinoApp(BoxLayout):
    def __init__(self, **kwargs):
        super().__init__(orientation="vertical", **kwargs)

        self.setpoints = []
        self.inputs = []

        self.add_widget(Label(text="Enter COM port (e.g., COM8):"))
        self.port_input = TextInput(multiline=False, hint_text="COM Port")
        self.add_widget(self.port_input)

        self.add_widget(Label(text="Enter motor setpoints (0-1023):"))

        for i in range(5):
            box = BoxLayout(orientation="horizontal")
            label = Label(text=f"Motor {i + 1}:")
            input_field = TextInput(
                multiline=False, input_filter="int", hint_text="0-1023"
            )
            box.add_widget(label)
            box.add_widget(input_field)
            self.inputs.append(input_field)
            self.add_widget(box)

        send_button = Button(text="Send to Arduino", size_hint=(1, 0.2))
        send_button.bind(on_press=self.validate_and_send)
        self.add_widget(send_button)

    def validate_and_send(self, instance):
        try:
            self.setpoints = [int(input_field.text) for input_field in self.inputs]

            if not all(0 <= sp <= 1023 for sp in self.setpoints):
                raise ValueError("One or more setpoints are out of range (0-1023).")

            port = self.port_input.text.strip()
            if not port:
                raise ValueError("COM port is required.")

            print("Sending to arduino")
            # self.send_to_arduino(port, 9600, self.setpoints)
            self.show_popup("Success", f"Setpoints sent: {self.setpoints}")

        except ValueError as e:
            self.show_popup("Error", str(e))

    def send_to_arduino(self, port, baudrate, setpoints):
        try:
            with serial.Serial(port, baudrate, timeout=2) as ser:
                time.sleep(2)  # Wait for Arduino initialization
                message = ",".join(map(str, setpoints)) + "\n"
                ser.write(message.encode())
        except serial.SerialException as e:
            self.show_popup("Error", f"Serial communication error: {e}")

    def show_popup(self, title, message):
        popup = Popup(title=title, content=Label(text=message), size_hint=(0.8, 0.5))
        popup.open()


class ArduinoAppGUI(App):
    def build(self):
        return ArduinoApp()


if __name__ == "__main__":
    ArduinoAppGUI().run()
