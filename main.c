#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//volatile uint16_t overflow=0;
void initADC()
{
    ADMUX=(1<<REFS0);
    ADCSRA=(1<<ADEN)|(7<<ADPS0);
}
    uint16_t ReadADC(uint8_t ch)    //making a func readADC which is 16 bit
    {
        //select ADC channel ch must be from 0 to 7
        ADMUX&=0xf8;             //logic
        ch=ch&0b00000111;
        ADMUX|=ch;
        //start single conversion
        ADCSRA|=(1<<ADSC);
        while(!( (ADCSRA)&(1<<ADIF)));
        //FIRST CONVERSION IS DONE MOVE TO THE NEXT VALUE
        ADCSRA|=(1<<ADIF);
        return(ADC);
    }
int main(void)
{
    TCCR1A|=((1<<COM1A1)|(1<<WGM11)|(1<<WGM10));
    TCCR1B|=((1<WGM12)|(1<<CS01)|(1<<CS00));
    TCNT1 = 0x00;
    DDRB|=(1<<PB1);
    DDRC&=~(1<<PC0);
    initADC();
    uint16_t x;
    while(1)
    {

      x=ReadADC(0);
      OCR1A=x;
      _delay_ms(200);
    }
    return 0;
}
