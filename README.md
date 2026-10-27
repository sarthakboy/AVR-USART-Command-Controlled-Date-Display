# AVR USART Command-Controlled Date Display

**A bare-metal Embedded C project combining USART communication, command parsing, Timer0 interrupts, and multiplexed seven-segment display control.**

![Language](https://img.shields.io/badge/Language-Embedded%20C-blue)
![MCU](https://img.shields.io/badge/MCU-ATmega16-orange)
![Communication](https://img.shields.io/badge/Communication-USART-green)
![Simulation](https://img.shields.io/badge/Simulation-Proteus-purple)

## Overview

This project demonstrates how a computer can control display modes on an AVR microcontroller through serial commands. The firmware receives commands over USART, processes them using a character buffer and string comparison, and switches between predefined date/display values.

A Timer0 overflow interrupt continuously refreshes an eight-digit, multiplexed seven-segment display, allowing the display to remain visible while the main program handles serial communication.

## Features

- **USART command interface:** Receives text commands from a serial terminal.
- **Command parsing:** Uses a null-terminated character buffer and `strcmp()` to identify commands.
- **Display mode selection:** Switches between predefined display values through serial commands.
- **Timer0 overflow interrupt:** Periodically refreshes the display.
- **Eight-digit multiplexing:** Controls individual digits using GPIO outputs.
- **Bare-metal programming:** Configures AVR registers directly without relying on a high-level display or communication library.
- **Interrupt-driven display refresh:** Separates display scanning from command-processing logic.

## Hardware and Tools

| Component | Purpose |
|---|---|
| ATmega16 | Main microcontroller |
| Eight-digit seven-segment display | Displays the selected date value |
| USB-to-serial adapter or simulator UART | Serial communication with a computer |
| Proteus | Circuit simulation |
| AVR-GCC / Microchip Studio | Embedded C development |

*Confirm that your actual circuit and project configuration match these components before publishing.*

## System Architecture

```text
        Computer / Serial Terminal
                    |
                    | USART Commands
                    v
           AVR USART Receiver
                    |
                    v
          Character Input Buffer
                    |
                    v
             Command Parser
                    |
                    v
          Display Mode Selection
                    |
                    v
          Timer0 Overflow ISR
                    |
                    v
       Eight-Digit Multiplexing
                    |
                    v
         Seven-Segment Display
```

The main loop receives and processes commands, while the Timer0 interrupt handles periodic display scanning.

## Serial Commands

Open the serial terminal with the baud rate configured in the firmware and send a command followed by Enter.

| Command | Action |
|---|---|
| `TIME` | Selects the predefined value assigned to time mode |
| `CLOCK` | Selects the alternate display mode, if configured in the firmware |

Commands are case-sensitive in the current implementation. The exact displayed values depend on the constants configured in the source code.

> **Note:** This project selects between predefined display values. It does not currently implement a continuously advancing real-time clock.

## Technical Implementation

### 1. USART Communication

The USART peripheral is configured through AVR registers. The firmware receives incoming characters using polling and assembles them into a command buffer.

### 2. Command Buffer and Parsing

Characters are stored sequentially until a line-ending character (`\r` or `\n`) is received. The buffer is then terminated with `\0` and compared against supported commands using `strcmp()`.

### 3. Timer0 Overflow Interrupt

Timer0 is configured with a prescaler and preload value. Its overflow interrupt periodically invokes the display-refresh routine.

### 4. Seven-Segment Multiplexing

The firmware activates one digit at a time and outputs the corresponding segment pattern. Rapid repetition refreshes all eight digits, creating the appearance of a continuously illuminated display.

## Skills Demonstrated

- Embedded C programming
- AVR register-level peripheral configuration
- USART serial communication
- Character buffering and string parsing
- Timer configuration and interrupt handling
- Seven-segment display multiplexing
- Bitwise operations and GPIO control
- Debugging interactions between interrupts and the main loop

## Getting Started

1. Clone or download this repository.
2. Open the project in Microchip Studio or your configured AVR development environment.
3. Build the firmware for the target AVR microcontroller.
4. Load the generated HEX file into Proteus or flash it onto compatible hardware.
5. Connect a serial terminal using the configured baud rate.
6. Send a supported command followed by Enter and observe the display-mode change.

## Future Improvements

- Implement a continuously advancing clock using timer-based timekeeping.
- Add validation for unknown commands and oversized input.
- Improve serial reception with a USART receive interrupt.
- Add a cleaner command-dispatch structure.
- Display additional formats, such as `DD-MM-YY` and `HH-MM-SS`.

## Author

**Sarthak Pandey**

Embedded Systems | Embedded C | AVR | STM32

[Linkedln Profile](www.linkedin.com/in/sarthak-pandey-981551428)
