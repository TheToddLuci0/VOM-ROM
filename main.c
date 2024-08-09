#include <gb/crash_handler.h>

#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <gbdk/console.h>



#define DAT0    0xFF7D
#define DAT1    0xFF7E
#define CTL     0xFF7F
#define IDR     0xFF7F

#define mio8(x)    (*(volatile uint8_t *)(x))

void led_clear(){
        mio8(DAT0) = 0;
        mio8(CTL) = 0x00;
        mio8(CTL) = 0x10;
        mio8(CTL) = 0x30;
        mio8(CTL) = 0x40;
        mio8(CTL) = 0x50;
        mio8(CTL) = 0x60;
        mio8(CTL) = 0x70;
        mio8(CTL) = 0x80;

        mio8(DAT0) = 0;
        mio8(CTL) = 0x01;
        mio8(CTL) = 0x11;
        mio8(CTL) = 0x31;
        mio8(CTL) = 0x41;
        mio8(CTL) = 0x51;
        mio8(CTL) = 0x61;
        mio8(CTL) = 0x71;
        mio8(CTL) = 0x81;

        mio8(DAT0) = 0;
        mio8(CTL) = 0x02;
        mio8(CTL) = 0x12;
        mio8(CTL) = 0x32;
        mio8(CTL) = 0x42;
        mio8(CTL) = 0x52;
        mio8(CTL) = 0x62;
        mio8(CTL) = 0x72;
        mio8(CTL) = 0x82;

        //flush
        mio8(CTL) = 0x90;
}

void test(uint8_t val){
    puts("Testing green");
        mio8(DAT0) = val;
        mio8(CTL) = 0x00;
        mio8(CTL) = 0x10;
        mio8(CTL) = 0x30;
        mio8(CTL) = 0x40;
        mio8(CTL) = 0x50;
        mio8(CTL) = 0x60;
        mio8(CTL) = 0x70;
        mio8(CTL) = 0x80;
        mio8(CTL) = 0x90;
        puts("Flushed");
        delay(500);

        mio8(DAT0) = 0x00;
        mio8(CTL) = 0x00;
        mio8(CTL) = 0x10;
        mio8(CTL) = 0x30;
        mio8(CTL) = 0x40;
        mio8(CTL) = 0x50;
        mio8(CTL) = 0x60;
        mio8(CTL) = 0x70;
        mio8(CTL) = 0x80;
        mio8(CTL) = 0x90;
        puts("Flushed");
        delay(500);


    puts("Testing red");
        mio8(DAT0) = val;
        mio8(CTL) = 0x01;
        mio8(CTL) = 0x11;
        mio8(CTL) = 0x31;
        mio8(CTL) = 0x41;
        mio8(CTL) = 0x51;
        mio8(CTL) = 0x61;
        mio8(CTL) = 0x71;
        mio8(CTL) = 0x81;
        mio8(CTL) = 0x91;
        puts("Flushed");
        delay(500);
        
        mio8(DAT0) = 0x00;
        mio8(CTL) = 0x01;
        mio8(CTL) = 0x11;
        mio8(CTL) = 0x31;
        mio8(CTL) = 0x41;
        mio8(CTL) = 0x51;
        mio8(CTL) = 0x61;
        mio8(CTL) = 0x71;
        mio8(CTL) = 0x81;
        mio8(CTL) = 0x91;
        puts("Flushed");
        delay(500);


    puts("Testing blue");
        mio8(DAT0) = val;
        mio8(CTL) = 0x02;
        mio8(CTL) = 0x12;
        mio8(CTL) = 0x32;
        mio8(CTL) = 0x42;
        mio8(CTL) = 0x52;
        mio8(CTL) = 0x62;
        mio8(CTL) = 0x72;
        mio8(CTL) = 0x82;
        mio8(CTL) = 0x92;
        puts("Flushed");
        delay(500);

        mio8(DAT0) = 0x00;
        mio8(CTL) = 0x02;
        mio8(CTL) = 0x12;
        mio8(CTL) = 0x32;
        mio8(CTL) = 0x42;
        mio8(CTL) = 0x52;
        mio8(CTL) = 0x62;
        mio8(CTL) = 0x72;
        mio8(CTL) = 0x82;
        mio8(CTL) = 0x92;
        puts("Flushed");
        delay(500);


        //flush
        mio8(CTL) = 0x90;
}



void main(void)
{
    printf("Welcome to hell\n");


    // Make sure we're on a badge
    // TODO
    
    int safe = 1;
    puts("Checking IDR....");
    if (mio8(IDR) != 0x21){
        printf("Expected 0x21, got %x", mio8(IDR));
        safe = 0;
    }
    puts("Write one...");
    mio8(CTL) = 0xF3;
    if ((mio8(DAT1) != 0x44) || (mio8(DAT0) != 0x6d)){
        printf("DAT1: %x\n", mio8(DAT1));
        printf("DAT0: %x\n", mio8(DAT0));
        safe = 0;
    }
    puts("Write two...");
    mio8(CTL) = 0xF4;
    if ((mio8(DAT1) != 0x69) || (mio8(DAT0) != 0x74)){
        printf("DAT1: %x\n", mio8(DAT1));
        printf("DAT0: %x\n", mio8(DAT0));
        safe = 0;
    }
    puts("Write three...");
    mio8(CTL) = 0xF5;
    if (mio8(DAT1) != 0x72 || mio8(DAT0) != 0x79){
        printf("DAT1: %x\n", mio8(DAT1));
        printf("DAT0: %x\n", mio8(DAT0));
        safe = 0;
    }
    if (safe == 0){
        puts("Something is wrong!");
        delay(10000);
    } else {
        puts("Passed!");
        delay(1000);
    }
    // END TODO

    test(0x0F);
    test(0x60);
    test(0xFF);

    // Loop forever
    uint8_t r = 0x10;
    uint8_t g = 0x10;
    uint8_t b = 0x10;

    uint8_t r_inc = 1;
    uint8_t g_inc = 3;
    uint8_t b_inc = 7;
    while(1) {
        cls();
        printf("R: %u\n", r);
        printf("G: %u\n", g);
        printf("B: %u\n", b);
        printf("IDR: 0x%x\n", mio8(IDR));
        printf("DAT1: 0x%x\n", mio8(DAT1));
        printf("DAT0: 0x%x\n", mio8(DAT0));

        mio8(DAT0) = g;
        mio8(CTL) = 0x00;
        mio8(CTL) = 0x10;
        mio8(CTL) = 0x30;
        mio8(CTL) = 0x40;
        mio8(CTL) = 0x50;
        mio8(CTL) = 0x60;
        mio8(CTL) = 0x70;
        mio8(CTL) = 0x80;

        mio8(DAT0) = r;
        mio8(CTL) = 0x01;
        mio8(CTL) = 0x11;
        mio8(CTL) = 0x31;
        mio8(CTL) = 0x41;
        mio8(CTL) = 0x51;
        mio8(CTL) = 0x61;
        mio8(CTL) = 0x71;
        mio8(CTL) = 0x81;

        mio8(DAT0) = b;
        mio8(CTL) = 0x02;
        mio8(CTL) = 0x12;
        mio8(CTL) = 0x32;
        mio8(CTL) = 0x42;
        mio8(CTL) = 0x52;
        mio8(CTL) = 0x62;
        mio8(CTL) = 0x72;
        mio8(CTL) = 0x82;

        //flush
        mio8(CTL) = 0x90;
        puts("Flushed");

        r = (r + r_inc) % 255;
        g = (g + g_inc) % 255;
        b = (b + b_inc) % 255;

		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        delay(10);
        vsync();
    }
}

