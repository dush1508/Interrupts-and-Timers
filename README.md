# Interrupts-and-Timers

Make a system which is connected to your laptop via UART and uses a pushbutton, a keypad, and an LED. The system should cause the LED to blink each second using a timer-based interrupt. The system should continually detect buttons pressed on the keypad and display the corresponding characters on the screen of your laptop. When the pushbutton is pressed, your system should use a GPIO-based interrupt to display a '$' character on your laptop. Assume that only one button on the keypad can be pressed at a time.
