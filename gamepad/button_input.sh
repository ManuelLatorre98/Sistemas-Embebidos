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
    elif [[ "$buffer" =~ aq ]]; then
        is_pressed_a=false   
        xdotool keyup "a"
        buffer=""
    elif [[ "$buffer" =~ bq ]]; then
        is_pressed_b=false   
        xdotool keyup "b"
        buffer=""
    elif [[ "$buffer" =~ cq ]]; then
        is_pressed_c=false   
        xdotool keyup "c"
        buffer=""
    fi
done < /dev/ttyUSB0