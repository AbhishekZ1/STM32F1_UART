# UART Driver for STM32F103

This project implements a basic UART driver for STM32F103 microcontrollers. It includes initialization, data transmission and reception, and an interrupt-based handler with message buffer management.

---

## 📁 Files Included

- `uart.c` – Source file containing UART implementation.
- `uart.h` – Header file with function declarations and macros.
- `gpio_driver.h` – Used for configuring UART GPIO pins.
- `systick_timer.h` – Optional, can be used for timeout logic.

---

## 📌 Function Documentation

### 1. `void Enable_UART(unsigned short USART, unsigned long Boud_Rate)`

**Description:**  
Initializes the specified USART (1, 2, or 3) with the given baud rate.

**Details:**
- Enables the respective USART peripheral clock.
- Configures the associated Tx and Rx GPIO pins:
  - Tx → Alternate Function Push-Pull
  - Rx → Input Floating
- Sets the Baud Rate Register (BRR) using `USART_BRR()`.
- Enables the USART receiver and transmitter.
- Enables the receive-not-empty interrupt (RXNEIE).
- Enables the USART peripheral.

**Parameters:**
- `USART` – The USART number (1, 2, or 3).
- `Boud_Rate` – Desired baud rate (e.g., 9600, 115200).

---

### 2. `unsigned long USART_BRR(unsigned short Urt, unsigned long BR)`

**Description:**  
Calculates the BRR (Baud Rate Register) value required for the desired baud rate based on the peripheral clock.

**Details:**
- For USART1, uses APB2 clock = 108 MHz.
- For USART2/3, uses APB1 clock = 54 MHz.
- Splits BRR into mantissa and fraction:
  - Mantissa = Integer part of (PCLK / (16 × Baud Rate))
  - Fraction = ((Decimal part × 16) rounded)
- Returns the combined BRR value.

**Parameters:**
- `Urt` – USART number.
- `BR` – Desired baud rate.

**Returns:**  
- Calculated BRR register value.

---

### 3. `char usart_rx(unsigned short urt)`

**Description:**  
Waits for a character to be received and returns it.

**Details:**
- Polls the RXNE (Receive Not Empty) bit.
- When set, reads the received character from the Data Register (DR).

**Parameters:**
- `urt` – USART number.

**Returns:**  
- Received character.

---

### 4. `void usart_tx(unsigned urt, char c)`

**Description:**  
Transmits a single character via UART.

**Details:**
- Polls the TXE (Transmit Data Register Empty) bit.
- When ready, writes the character to the DR register.

**Parameters:**
- `urt` – USART number.
- `c` – Character to send.

---

### 5. `void usart_SendMsg(unsigned urt, char str[])`

**Description:**  
Sends a null-terminated string over UART.

**Details:**
- Iterates through each character in the string.
- Uses `usart_tx()` to send each character.

**Parameters:**
- `urt` – USART number.
- `str[]` – Null-terminated string to send.

---

### 6. `void UART_ISR(unsigned short urt, unsigned short urt_mgr[], char Str[])`

**Description:**  
Custom interrupt service routine (ISR) handler for receiving UART data into a buffer.

**Details:**
- Reads the received character from the Data Register.
- If `urt_mgr[3]` (terminator enable) is set:
  - Adds characters to buffer until `urt_mgr[4]` (terminator char) is received.
  - Sets `urt_mgr[1]` (signal) to 1 when message is complete.
- If terminator is not used:
  - Increments a time counter (`urt_mgr[6]`) to detect end of message based on timeout logic.
- `urt_mgr[0]` keeps track of the number of received bytes.
- `urt_mgr[2]` is a bridge flag: if set to 1, reception is disabled.

**Parameters:**
- `urt` – USART number.
- `urt_mgr[]` – Manager array to control reception state.
- `Str[]` – Character buffer to store incoming message.

**UART Manager Array (`urt_mgr[]`) Index Guide:**
| Index | Purpose                    |
|-------|-----------------------------|
| 0     | Byte count                  |
| 1     | Signal (1 when message done)|
| 2     | Bridge (1 to disable Rx)    |
| 3     | Terminator enable (1 = yes) |
| 4     | Terminator character (e.g. '\n') |
| 5     | Timeout constant (not used here)|
| 6     | Time counter (for timeout-based ends)|

---

## ✅ Usage Steps

1. Include `uart.h` and `gpio_driver.h` in your main file.
2. Call `Enable_UART()` to initialize the USART.
3. Use `usart_tx()` or `usart_SendMsg()` to transmit data.
4. Use `usart_rx()` or enable interrupts to receive data.
5. Inside `USARTx_IRQHandler`, call `UART_ISR()` with correct parameters.
6. Use `urt_mgr[1]` flag to check when a message has been received completely.

---

