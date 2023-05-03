#!/bin/bash

stty -F /dev/ttyUSB0 speed 2400 # establecer la velocidad de la conexión serial
buffer=""
while read -n 1 tecla; do
    buffer="${buffer}${tecla}"
    if [ "$tecla" == "a" ]; then
        is_pressed_a=true
        xdotool keydown "a"
    elif [ "$tecla" == "b" ]; then
        is_pressed_b=true   
        xdotool keydown "b"
    elif [ "$tecla" == "c" ]; then
        is_pressed_c=true  
        xdotool keydown "c"
    elif [[ "$buffer" =~ qa ]]; then
        is_pressed_a=false   
        xdotool keyup "a"
        buffer=""
    elif [[ "$buffer" =~ qb ]]; then
        is_pressed_b=false   
        xdotool keyup "b"
        buffer=""
    elif [[ "$buffer" =~ qc ]]; then
        is_pressed_c=false   
        xdotool keyup "c"
        buffer=""
    fi
#    if [ "$is_pressed_a" == true ]; then
#        window=$(xdotool getwindowfocus) # obtener la identificación de la ventana activa
#        xdotool windowfocus $window # cambiar el foco a la ventana activa
#        xdotool keydown "a" # enviar la entrada simulada a la ventana activa
#    fi

#    if [ "$is_pressed_b" == true ]; then
#        window=$(xdotool getwindowfocus) # obtener la identificación de la ventana activa
#        xdotool windowfocus $window # cambiar el foco a la ventana activa
#        xdotool keydown "b" # enviar la entrada simulada a la ventana activa
#    fi

#    if [ "$is_pressed_c" == true ]; then
#        window=$(xdotool getwindowfocus) # obtener la identificación de la ventana activa
#        xdotool windowfocus $window # cambiar el foco a la ventana activa
#        xdotool keydown "c" # enviar la entrada simulada a la ventana activa
#    fi

done < /dev/ttyUSB0