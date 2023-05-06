sudo cat /dev/ttyUSB0 | while read -n 1 num; do
brightnessctl s $(($num))
done