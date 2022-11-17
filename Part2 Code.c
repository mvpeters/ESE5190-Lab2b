#include "pico/stdlib.h"
#include <stdio.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "registers.h"
#define QTPY_BOOT_PIN 21

//sio base 0xd0000000
//offset 0x00000004

typedef struct {
    uint32_t Register_addy;
    uint32_t Register_val;
} Register_status; 

void render_to_console(Register_status status) {
    // adjust console window height to match 'frame size'
    for (uint8_t i=0; i<10; i++) { 
        printf("\n");
    }
    printf("Address:  0x%08x\n",   status.Register_addy);
    printf("Value:        0x%08x\n",   status.Register_val);
}  

int main() {

    ADDRESS address;
    VALUE register_value;

    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();

    Register_status status;
    status.Register_addy =  0x00000000;
    status.Register_val = 0x00000000;

    int readwrite;
    uint32_t read_register;
    uint32_t write_register;
    volatile uint32_t * boot_pin_adress;
    uint32_t full_gpio_register_value;
    uint32_t pin21_selection_mask;
    uint32_t selected_pin_state;
    uint32_t shifted_pin_21_state;

    while (true) {
        sleep_ms(5000); //so i have time to open serial console before it prints
        printf("enter register to view: "); //
        scanf("%x", &read_register); //
        sleep_ms(1000);
        address = (volatile uint32_t *) read_register;
        status.Register_addy = read_register;
        status.Register_val = *address;
        render_to_console(status); //to read value in register
        sleep_ms(1000);

        printf("To write to this address enter 1: \n");
        readwrite = getchar();

        if(readwrite == '1'){
            printf("Enter the value for this register: \n");
            scanf("%x", &write_register);
            *address = write_register;   // put the user input 8-bit value to this address
            status.Register_val = *address;
            render_to_console(status);
            sleep_ms(10); 
    }
    return 0;
    }  
}