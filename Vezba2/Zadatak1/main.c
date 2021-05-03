#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long ms = 0;

void my_delay(unsigned long milliseconds)
{
	while(ms - milliseconds < 500);
}

ISR(TIMER0_COMPA_vect)
{
	ms++;
}

int main()
{
	DDRB |= 1 << 5;         //PB5 izlaz
	PORTB |= 1 << 5;          //setovanje diode na 1 (led ON)

	//inicijalizacija tajmera 0:
	TCCR0A = 0x02; //tajmer 0: CTC mod
	TCCR0B = 0x03; //tajmer 0: fclk = fosc/64
	OCR0A = 249; //perioda tajmera 0: 250 Tclk (OCR0A + 1 = 250)
	TIMSK0 = 0x02; //dozvola prekida tajmera 0
	        	   //usled dostizanja vrednosti registra OCR0A

	sei();        //globalna dozvola prekida

	while(1)
	{
		my_delay(ms);
		PORTB ^= 1 << 5;
	}

}
