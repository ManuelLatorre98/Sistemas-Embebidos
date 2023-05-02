#!/bin/bash

stty -F /dev/ttyUSB0 speed 2400 # establecer la velocidad de la conexión serial
buffer=""
while read -n 1 tecla; do
    buffer="${buffer}${tecla}"
    if [ "$tecla" == "a" ]; then
        is_pressed=true
        xdotool keydown "a"
    elif [[ "$buffer" =~ qa ]]; then
        is_pressed=false   
        xdotool keyup "a"
        buffer=""
    fi

    if [ "$is_pressed" == true ]; then
        window=$(xdotool getwindowfocus) # obtener la identificación de la ventana activa
        xdotool windowfocus $window # cambiar el foco a la ventana activa
        xdotool keydown "a" # enviar la entrada simulada a la ventana activa
    fi
done < /dev/ttyUSB0