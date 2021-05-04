#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long fi = 0; //faktor ispune

ISR(TIMER0_COMPA_vect)
{
	fi++;

	if (fi == 256)
	{
		fi = 0;

	}
}

int main()
{
	//inicijalizacija tajmera 0:
	TCCR0A = 0x02; //tajmer 0: CTC mod
	TCCR0B = 0x01; //tajmer 0: No prescaling
	OCR0A = 159; //perioda tajmera 0:  (OCR0A + 1 = 160)
	TIMSK0 = 0x02; //dozvola prekida tajmera 0
	//usled dostizanja vrednosti registra OCR0A

	sei();        //globalna dozvola prekida

	//inicijalizacija diode
	DDRB |= 1 << 5;  //PB5 IZLAZ
	PORTB |= 1 << 5; //LED ON

	while(1)
	;

	return 0;
}

