# Interrupts-and-Timers

This is a system that requires connection to ya laptop via UART and uses a pushbutton, a keypad, and an LED. The system causes the LED to blink each second using a timer-based interrupt. The system also continously detects buttons pressed on the keypad and display the corresponding characters on the screen of your laptop. When the pushbutton is pressed, the system uses a GPIO-based interrupt to display a '$' character on your laptop. This systems assumes that only one button on the keypad can be pressed at a time.
