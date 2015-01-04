#include "int.h" 
#include "qemu.h" 


extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

extern unsigned int bss_start;
extern unsigned int bss_end;
extern unsigned int data_rom_start;
extern unsigned int data_start;
extern unsigned int data_end;

unsigned int x;
unsigned int y=2;
unsigned int z=7;

int notmain ( unsigned int earlypc )
{
    unsigned int ra;
    unsigned int rb;
    pl011_uart_write_string("Hello");
    pl011_uart_write_hex(0x12345678);
    pl011_uart_write_hex(bss_start);
    pl011_uart_write_hex(data_rom_start);
    pl011_uart_write_hex(data_start);
    pl011_uart_write_hex(x);
    pl011_uart_write_hex(y);
    pl011_uart_write_hex(z);
    for(ra=bss_start;ra<bss_end;ra+=4) PUT32(ra,0);
    pl011_uart_write_string("Init data\n");
    for(ra=data_start,rb=data_rom_start;ra<data_end;ra+=4,rb+=4){
        pl011_uart_write_hex(ra);
        pl011_uart_write_hex(rb);
        pl011_uart_write_hex(GET32(rb));
        PUT32(ra,GET32(rb));
        pl011_uart_write_string("\n");
    }
    pl011_uart_write_string("Done\n");
    pl011_uart_write_hex(x);
    pl011_uart_write_hex(y);
    pl011_uart_write_hex(z);
    pl011_uart_write_string("\n");
    pl011_uart_write_hex((uint32_t)&x);
    pl011_uart_write_hex((uint32_t)&y);
    pl011_uart_write_hex((uint32_t)&z);
    return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
