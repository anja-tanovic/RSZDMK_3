/**
 * @file main.c
 * @brief Treperenje diode odredjen broj puta
 * @author Anja Tanovic
 * @date 22-03-2021
 * @version 1.0
 */

#include <avr/io.h>
#include <avr/interrupt.h>

/// Makro za podesavanje visoke vrednosti signala na pinu
#define HIGH 				1
/// Makro za podesavanje niske vrednosti signala na pinu
#define LOW 				0

/// Makro za podesavanje izlaznog smera pina
#define OUTPUT 				1
/// Makro za podesavanje ulaznog smera pina
#define INPUT 				0

/// Makro za selektovanje porta B
#define PORT_B 				0
/// Makro za selektovanje porta C
#define PORT_C 				1
/// Makro za selektovanje porta D
#define PORT_D 				2

/// Makro za selektovanje pina na koji je povezana dioda
#define DIODE_PIN 			5

/// Makro za period sporog treperenja
#define SLOW 				1000
/// Makro za period brzog treperenja
#define FAST 				300

/// Makro za broj sporih treptaja
#define SLOW_REPETITIONS	3
/// Makro za broj brzih treptaja
#define FAST_REPETITIONS	10

/// Promenljiva koja skladisti broj milisekundi proteklih od pokretanja aplikacije
volatile unsigned long ms = 0;

/**
 * pinPulsing - Funkcija koja implementira visestruko pulsiranje pina
 * @param port - ulaz tipa unsigned char - port na kojem se implementira funkcionalnost
 * @param pin - ulaz tipa unsigned char - pin na kojem se implementira funkcionalnost
 * @param period - ulaz tipa unsigned long - duzina periode jednog treptaja
 * @param num_of_repetitions - ulaz tipa unsigned char - broj treptaja koje treba napraviti
 * @return Nema povratnu vrednost
 */
void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions);

/**
 * pinPulse - Funkcija koja implementiran podizanje i spustanje vrednosti na pinu
 * odgovarajucom brzinom
 * @param port - ulaz tipa unsigned char - Port na kojem je potrebno implementirati funkcionalost
 * @param pin - ulaz tipa unsigned char - Pin na kojem je potrebno implementirati funkcionalnost
 * @param period - ulaz tipa unsigned long - Perioda promene vrednosti na pinu
 * @return Nema povratnu vrednost
 */
void pinPulse(unsigned char port, unsigned char pin, unsigned long period);

/**
 * pinSetValue - Funkcija koja postavlja vrednost na pinu
 * @param port - ulaz tipa unsigned char - Port na kojem je pin ciju vrednost potrebno postaviti
 * @param pin - ulaz tipa unsigned char - Pin ciju je vrednost potrebno postaviti
 * @param value - ulaz tipa unsigned char - Vrednost koju je potrebno postaviti na pin
 * @return Nema povratnu vrednost
 */
void pinSetValue(unsigned char port, unsigned char pin, unsigned char value);

/**
 * pinInit - Funkcija koja implementiran inicijalizaciju pina
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @param direction - ulaz tipa unsigned char - Smer prema kojem je potrebno inicijalizovati pin
 * @return Nema povratnu vrednost
 */
void pinInit(unsigned char port, unsigned char pin, unsigned char direction);

/**
 * timer0DelayMs - Funkcija koja implementira pauzu u broju milisekundi koji je prosledjen
 * kao parametar
 * @param delay_length - ulaz tipa unsigned long - Duzina pauze u milisekundama
 * @return Povratna vrednost je tipa unsigned long i ima vrednost broja milisekundi
 * proteklih od pocetka aplikacije do trenutka izlaska iz funkcije
 */
unsigned long timer0DelayMs(unsigned long delay_length);

/**
 * timer0InteruptInit - Funkcija koja inicijalizuje timer 0 tako da pravi prekide
 * svake milisekunde
 * @return Nema povratnu vrednost
 */
void timer0InteruptInit();

/**
 * calculateHalfPeriod - Funkcija koja racuna polovinu periode
 * @param period - ulaz tipa unsigned long - Perioda
 * @return Povratna vrednost je tipa unsigned long i predstavlja polovnu periode
 */
unsigned long calculateHalfPeriod(unsigned long period);

/**
 * main - funkcija koja implementiran glavni deo aplikacije
 * @return Nema povratnu vrednost
 */
int main()
{
	// Inicijalizacija
	pinInit(PORT_B, DIODE_PIN, OUTPUT);
	timer0InteruptInit();

	// Glavna petlja
	while (1)
	{
		// Brzo treptanje
		pinPulsing(PORT_B, DIODE_PIN, FAST, FAST_REPETITIONS);
		// Sporo treptanje
		pinPulsing(PORT_B, DIODE_PIN, SLOW, SLOW_REPETITIONS);

	}
	return 0;
}

/******************************************************************************************/

void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions)
{
	unsigned char i;

	// Implementacija num_of_repetitions perioda
	for (i = 0; i < num_of_repetitions; i++)
		pinPulse(port, pin, period);
}

/******************************************************************************************/

void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
	// Poluperioda u kojoj pin ima visoku vrednost
	pinSetValue(port, pin, HIGH);
	timer0DelayMs(calculateHalfPeriod(period));

	// Poluperioda u kojoj pin ima nisku vrednost
	pinSetValue(port, pin, LOW);
	timer0DelayMs(calculateHalfPeriod(period));
}

/******************************************************************************************/

void pinSetValue(unsigned char port, unsigned char pin, unsigned char value)
{
	// Postavljanje vrednosti pina
	switch (port)
	{
		case PORT_B:
			if (value == HIGH)
				PORTB |= 1 << pin;
			else
				PORTB &= ~(1 << pin);
			break;
		case PORT_C:
			if (value == HIGH)
				PORTC |= 1 << pin;
			else
				PORTC &= ~(1 << pin);
			break;
		case PORT_D:
			if (value == HIGH)
				PORTD |= 1 << pin;
			else
				PORTD &= ~(1 << pin);
			break;
		default:
			break;
	}
}

/******************************************************************************************/

void pinInit(unsigned char port, unsigned char pin, unsigned char direction)
{
	// Inicijalizacija smera pina
	switch (port)
	{
	case PORT_B:
		if (direction == OUTPUT)
			DDRB |= 1 << pin;
		else
			DDRB &= ~(1 << pin);
		break;
	case PORT_C:
		if (direction == OUTPUT)
			DDRC |= 1 << pin;
		else
			DDRC &= ~(1 << pin);
		break;
	case PORT_D:
		if (direction == OUTPUT)
			DDRD |= 1 << pin;
		else
			DDRD &= ~(1 << pin);
		break;
	default:
		break;
	}
}

/******************************************************************************************/

unsigned long timer0DelayMs(unsigned long delay_length)
{
	unsigned long t0; // Trenutak pocevsi od kog se racuna pauza

	// Implementacija pauze
	t0 = ms;
	while ((ms - t0) < delay_length)
		; // Pauza delay_length milisekundi

	return ms;
}

/******************************************************************************************/

void timer0InteruptInit()
{
	// Inicijalizacija tajmera 0 tako da perioda prekida bude 1ms
	TCCR0A = 0x02;
	TCCR0B = 0x03;
	OCR0A = 249;
	TIMSK0 = 0x02;

	// Podesavanje globalne dozvole prekida
	sei();
}

/******************************************************************************************/

ISR(TIMER0_COMPA_vect)
{
	// Inkrementovanje broja milisekundi koje su prosle od pokretanja aplikacije
	ms++;
}

unsigned long calculateHalfPeriod(unsigned long period)
{
	return (period / 2);
}
