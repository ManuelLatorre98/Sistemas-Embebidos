stty -F /dev/ttyUSB0 speed 9600 # Establece la velocidad del puerto serial

while true; do
  read -n 1 -r tecla < /dev/ttyUSB0 # Espera por una pulsación del teclado a través del puerto serial y almacena el valor en 'tecla'
  echo $tecla # Muestra la letra de la pulsación en pantalla
  echo $tecla >> /dev/ttyUSB0 # Envía el contenido de 'tecla' al driver del dispositivo serial, quien a su vez lo envía por el hardware al MCU del otro lado
done