#include <avr/io.h>
#include "../timer0/timer0.h"
#include "../pin_driver/pin.h"

int main()
{
	pinInit(PORT_B, 5, OUTPUT);
	timer0InteruptInit();

	while(1)
	{
		pinSetValue(PORT_B, 5, HIGH);
		timer0DelayMs(1000);

		pinSetValue(PORT_B, 5, LOW);
		timer0DelayMs(1000);

		pinSetValue(PORT_B, 5, HIGH);
		timer0DelayMs(3000);

		pinSetValue(PORT_B, 5, LOW);
		timer0DelayMs(3000);

	}

	return 0;
}
