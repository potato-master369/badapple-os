#ifndef OSDEV_VGA_H
#define OSDEV_VGA_H
#include <stddef.h>
#include <stdint.h>
void terminal_writestring(const char *data);
char *itoa(int value, char *str, int base);
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void settermcol(size_t col);
#endif