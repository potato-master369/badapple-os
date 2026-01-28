from PIL import Image

brightness = [" ",".","`","-","'",",",":","_",";","~","=","^","\\\"","+","/","<",">","(",")","|","\\\\","i","%","l","{","}","!","*","I","[","]","c","r","?","s","x","t","1","7","v","a","f","z","e","n","u","C","J","L","o","j","2","3","T","Y","4","5","F","w","9","P","S","6","V","Z","b","d","k","m","G","h","q","p","A","y","g","0","E","X","&","U","#","D","K","O","$","8","@","H","R","B","W","M","N","Q"]
with open("out.h", "w") as f:
    f.write(
"""
#include <stdint.h>
#include "osdev_vga.h"

// Write a byte to an I/O port
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Read a byte from an I/O port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

volatile uint64_t pit_ticks = 0;

// IRQ0 handler increments the counter
__attribute__((interrupt))
void irq0_handler(void* frame) {
    pit_ticks++;
    outb(0x20, 0x20);       // EOI
}

// Sleep for one PIT tick (~54.9 ms at 18.2 Hz)
void pit_sleep_tick() {
    uint64_t start = pit_ticks;
    while (pit_ticks == start) {
        __asm__ __volatile__("hlt"); // halt until next interrupt
    }
}

void dobadapple() {
"""
    )
    for i in range(1, 4226):
        f.write("\nterminal_writestring(\"")
        with Image.open(f"badapple/src/output_{str(i).zfill(4)}.png", "r") as image:
            pixels = image.convert("L").load()
            w,h = image.size 
            for y in range(h):
                for x in range(w):
                    if pixels[x, y] == 0:
                        f.write(" ")
                    else:
                        idx = int(pixels[x,y] * (len(brightness)-1) / 255)
                        f.write(brightness[idx])


        f.write("\");\npit_sleep_tick();\n")
    f.write("}")