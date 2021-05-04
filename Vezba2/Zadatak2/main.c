#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char fi = 0;  //faktor ispune u pocetnom trenutku
volatile unsigned long pr = 0;  //povecava se svaki put kad se pojavi prekid (posle 781 se uvecava fi)
volatile unsigned char smer = 0;//0 za rast, 1 za opadanje

ISR(TIMER0_COMPA_vect)
{
	pr++;

	if (pr == 781)
	{
		pr = 0;
		switch (smer){
			case 0:
				fi++;
				if (fi == 255)
					smer = 1;
				break;
			case 1:
				fi--;
				if (fi == 0)
					smer = 0;
				break;
		}

	}

	if (pr == 0){
		PORTB |= 1 << 5;    //LED ON
	}
	if (pr == fi)
	{
		PORTB &= ~(1 << 5); //LED OFF
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

