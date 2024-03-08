#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/sys/stm32_peps.h"
#include "../arch/stm32f446re/include/dev/usart.h"

/*
* first argument define the type of string to kprintf and kscanf, 
* %c for charater
* %s for string, 
* %d for integer
* %x hexadecimal
* %f for floating point number
*/

/* Integer to String */
void itoa(int val, int base, uint8_t* a) {
    if (val == 0) {
        *a = '0';
        *(a + 1) = 0;
        return;
    }
    uint8_t buf[33];
    buf[32] = 0;
    uint8_t neg = 0, i = 31, j = 0;
    if (val < 0) {
        neg = 1;
        val *= -1;
    }
    for (; val && i; --i, val /= base) {
        buf[i] = "0123456789abcdef"[val % base];
    }
    if (neg) {
        buf[i] = '-';
        i--;
    }
    while (buf[i + j + 1] != 0) {
        *a++ = buf[i + j + 1];
        j++;
    }
    *a = 0;
}

/* Float to String */
void ftoa(float f, uint8_t* buf) {
    int val = (int)f;
    uint8_t rstr[33], i = 0;
    itoa(val, 10, rstr);
    while (rstr[i] != '\0') {
        *buf++ = rstr[i];
        i++;
    }
    *buf++ = '.';

    if (f < 0) {
        val = -val;
        f = -f;
    }
    for (int j = 0; j < 6; j++) {
        f -= (float)val;
        f *= 10;
        val = (int)f;
        uint8_t c;
        itoa(val, 10, &c);
        *buf++ = c;
    }
    *buf = 0;
}

/* String to Float */
float atof(uint8_t buff[]) {
    float num = 0;
    uint8_t minus = 0;
    uint8_t i = 0;
    if (buff[0] == '-') {
        minus = 1;
        i++;
    }

    for (; buff[i] != 0; i++) {
        if (buff[i] == '.' || buff[i] == 'e') {
            break;
        }
        num = num * 10 + (buff[i] - '0');
    }
    // printf("Number after decimal part: %f\n", num);

    if (buff[i] == '.') {
        float frac = 0;
        uint32_t len = 1;
        i++;
        for (; buff[i] != 0; i++) {
            if (buff[i] == 'e') {
                break;
            }
            frac = frac * 10 + (buff[i] - '0');
            len *= 10;
        }
        frac /= len;
        num += frac;
    }
    // printf("Number after fraction part: %f\n", num);


    if (buff[i] == 'e') {
        i++;
        uint8_t neg = 0;
        if (buff[i] == '-') {
            neg = 1;
            i++;
        }
        uint8_t exp = 0;
        for (; buff[i] != 0; i++) {
            exp = exp * 10 + (buff[i] - '0');
        }
        if (neg)
            for (uint8_t j = 0; j < exp; j++) {
                num /= 10;
            }
        else
            for (uint8_t j = 0; j < exp; j++) {
                num *= 10;
            }
    }
    // printf("Number after exponent part: %f\n", num);

    if (minus)
        num *= -1;
    return num;
}

void kprintf(uint8_t *format,uint32_t* outvar){
	
	int i;
	uint8_t buff[105];
	/* Checking for % */
	for(i=0; format[i]!='%';i++){}

	/* Cases for what is after % */
	switch(format[i+1]){

		/* If string value */
		case 's':{
			_USART_WRITE(USART2, outvar);
			break;
		}

		/* If character value */
		case 'c':{
			UART_SendChar(USART2, outvar[0]);
			break;
		}

		/* If decimal value */
		case 'd':{
			uint32_t num = *(outvar);
		    int rev = 0;
		    int len = 0;
		    while (num > 0){
		        rev = rev*10 + num%10;
		        num /= 10;
		        len++;
		    }
		    char str[10];
		    for(int i = 0; i < len; i++) {
		        str[i] = rev%10 + '0';
		        rev /= 10;
		    }
		    str[len] = 0;
			_USART_WRITE(USART2, str);
			break;
		}

		/* If hexa-decimal value */
		case 'x': {
	        uint32_t num = *(outvar);
	        char str[10];
	        int i=0;
	        while (num > 0) {
	            int rem = num%16;
	            if (rem < 10)
	                str[i++] = rem + '0';
	            else
	                str[i++] = (rem-10) + 'A';
	            num /= 16;
	        }
	        int len = i;
	        for (int j = 0; j < len/2; j++) {
	            char temp = str[j];
	            str[j] = str[len-1-j];
	            str[len-1-j] = temp;
	        }
	        str[len] = 0;
	        _USART_WRITE(USART2, str);
	        break;
   		}

   		/* If float value */
   		case 'f':{

   			for(int i=0;i<105;i++){
   				buff[i] = 0;
   			}
   			ftoa(*(float*)outvar, (uint8_t*)buff);
   			_USART_WRITE(USART2, buff);
   			break;

   		}

		default:{
			break;
		}
	}

}


void kscanf(uint8_t *format,uint32_t* invar)
{
	int i;
	uint8_t buff[105];

	/* Checking for % */
	for(i=0; format[i]!='%';i++){}

	/* Cases for what is after % */
	switch(format[i+1]){

		/* If string value */
		case 's':{
			_USART_READ(USART2, invar, 60);
			break;
		}

		/* If character value */
		case 'c':{
			invar[0] = UART_GetChar(USART2);
			break;
		}

		/* If decimal value */
	    case 'd': {
	        uint32_t num = 0;
	        char str[50];
	        _USART_READ(USART2, str, 50);
	        int len;
	        for(len = 0; str[len]; len++);
	        for (int j = 0; j < len; j++) {
	            num *= 10;
	            num += (str[j]-'0');
	        }
	        *invar = num;
	        break;
	    }
	    
	    /* If hexa-decimal value */
	    case 'x': {
	        uint32_t num = 0;
	        char str[50];
	        _USART_READ(USART2, str, 50);
	        int len;
	        for(len = 0; str[len]; len++);
	        int prod = 1;
	        for (int j = len-1; j >= 0; j--) {
	            char c = str[j];
	            if (c >= '0' && c <= '9') {
	                num += (c-'0')*prod;
	            }
	            else {
	                num += (c-'A'+10)*prod;
	            }
	            prod *= 16;
	        }
	        *invar = num;
	        break;
	    }

	    /* If float value */
	    case 'f':{

	    	_USART_READ(USART2, buff, 60);
	    	*(float*)invar = atof(buff);
	    	break;

	    }

		default:{
        	break;
		}
	}

}






