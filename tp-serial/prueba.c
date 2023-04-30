volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
void prender(void)
{
  (*DDR_B)=0b00010000;
}

void apagar(void)
{
  (*DDR_B)=0b00000000;
}