#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 16, 2);

void setup()
{
    lcd1.init();
    lcd1.backlight();
    lcd1.setCursor(0, 0);
    lcd1.print("VISITANTES");
    lcd1.setCursor(0, 1);
    lcd1.print("LOCAL");
}

void loop()
{
    _delay_ms(1500);
    /*
    lcd1.setCursor(0,0);
    lcd1.setCursor(5,1);
    lcd1.print(ultra());
    _delay_ms(1500);
    lcd1.clear();
    */
}

int c = 0;
int seg = 0;
int set = 0;

volatile bool abajo = true;
// FUNCIONES
void interrupt_TIMER1_Init()
{
    cli();          // deshabilitar momentáneamente las interrupciones
    TCCR1B = 0b101; // preescalador 1024
    TIMSK1 = 1;     // habilitar interrupcion por desbordamiento
    sei();          // habilitar las interrupciones
    TCNT1 = 49911;  // 1 second // tiempo de la interrupcion
}

ISR(TIMER1_OVF_vect)
{ // INTERRUPCIONES //se hace el desplazamiento
    c++;
    seg = 120 - c;
    TCNT1 = 49911;
    if (seg == 0)
    { // reset
        seg = 120;
        set++;
    }
    while (set > 4)
    {
        seg = 0;
        set = 0;
        c = 0;
        _delay_ms(10000);
    }
}

/*if (!(PINB & (1 << PINB1)))
{
    TCCR1B = 0b0; // stop
}
else
{
    TCCR1B = 0b101; // play
}
*/