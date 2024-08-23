
# CONEXIÓN

## STICKS
- **GND:** GND 
- **+5V:**: VCC 

### IZQUIERDO
- **VRX:** A0 (adc 0)
- **VRY:** A1 (adc 1)
- **SW (cierre de garra):** PIN2 (pd2)

### DERECHO
- **VRX:** A2 (adc 2)
- **VRY:** A3 (adc 3)
- **SW (apertura de garra):** PIN3 (pd3)


## SERVOS
- **GND (CABLE NEGRO/MARRON):** GND 
- **VCC (CABLE ROJO):** VCC 
- **PWM/SEÑAL SALIDA (Servo0):** PIN8 Pb0
- **PWM/SEÑAL SALIDA (Servo1):** PIN9 Pb1
- **PWM/SEÑAL SALIDA (Servo2):** PIN10 Pb2
- **PWM/SEÑAL SALIDA (Servo3):** PIN11 Pb3
- **PWM/SEÑAL SALIDA (Servo4):** PIN12 Pb4

# TESTING
- Con screen /dev/ttyUSB0 9600 (2400 en arduino chino) se puede observar el array con los ticks/grados de los servos. - Estos van de 90 a 270 (osea 180°). 
- 90 ticks = 1ms, 270 ticks= 2ms. 

# CALIBRACION BRAZO
- Arrancar el brazo
- Mover todos los servos para que este inicializado el array de angulos
- Mover cada servo hacia un limite y ubicar correctamente la pieza