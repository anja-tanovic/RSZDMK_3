#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= 1 << 5;         //PB5 izlaz

	while(1)
	{
		PORTB |= 1 <<5;     //LED ON
		_delay_ms(500);
		PORTB &= ~(1 << 5); //LED OFF
		_delay_ms(500);
	}

}
