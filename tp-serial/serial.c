
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
    uint8_t status_control_b; 
    uint8_t status_control_c;    /* ucsr0c USART Control and Status C */
    uint8_t _reserved;           /* espacio sin utilizar */
    uint8_t baud_rate_l;         /* ubrr0l baud rate low */;
    uint8_t baud_rate_h;         /* ubrr0h baud rate high */
    uint8_t data_es;             /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 9600
#define F_CPU 16000000UL
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)


void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_l = (uint8_t)BAUD_PRESCALE;
    puerto_serial->baud_rate_h = (uint8_t)(BAUD_PRESCALE >> 8);

    /* Activar la recepcion y transmicion */
    puerto_serial->status_control_b = (1 << 3) | (1 << 4);
    /*
    (1 << 3) el bit 3(TXEN0) activa la transmision 
    (1 << 4) bit 4 (RXEN0) Actiba la recepcion
    */

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    puerto_serial->status_control_c = (1 << 1) | (1 << 2) | (0 << 3) | (0 << 6);
    /*(1 << 1) establece el bit 1 en 1, que habilita el modo de paridad en el registro de control del USART.

    (1 << 2) establece el bit 2 en 1, que selecciona el modo de paridad impar en el registro de control del USART. (DEBIA SER IMPAR PORQUE LOS BYTES SON DE 7 BITS?)

    (0 << 3) establece el bit 3 en 0, lo que indica que no se utilizará un segundo bit de paridad.

    (0 << 6) establece el bit 6 en 0, lo que indica que se utilizará un solo bit de stop en el marco de datos.*/

	
}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char c)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    // while ( /* completar con E/S programada */ )
    //     ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */

}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;

    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */

}



