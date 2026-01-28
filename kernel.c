#include "osdev_vga.h"
#include "out.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* The part about the stupid compiler checks has been removed
   because if you're not using i686-elf-gcc that's your issue. */

// Converts an integer 'value' to a string in 'str' using the given 'base'.
// Supports base 2..16. Caller must provide a buffer large enough.

#define MAX_BUSSES 256
#define MAX_DEVICES 32
#define MAX_FUNCTIONS 8

#define WHITE 7
#define BLUE 1

void fill_screen() {
  // 2000 spaces for 80x25 screen
  static char spaces[2001];
  for (int i = 0; i < 2000; i++)
    spaces[i] = ' ';
  spaces[2000] = '\0';
  terminal_writestring(spaces);
}

// Wait until a key is pressed
void wait_for_keypress() {
  uint8_t scancode;
  // Keyboard controller status port: 0x64
  // Data port: 0x60
  do {
    // Poll until output buffer full (bit 0 of status)
    while ((inb(0x64) & 0x01) == 0) {
      // busy wait
    }
    scancode = inb(0x60);
  } while (scancode & 0x80); // ignore key
  // releases (high bit set)
}
void kernel_main(void) {
  terminal_initialize();

  /* Newline support is left as an exercise. - completed*/
  settermcol(0);
  /* splash screen, 25 cols */
  terminal_setcolor(0x17);
  fill_screen();

  terminal_writestring(
      "Splash Screen\n\n\n\n\n\n\n                      Bad apple, but for "
      "PC-AT x86 systems\n                                    Made by:\n\n "
      "    "
      "           Random Cool Stuff I Guess (YT "
      "@WompWomp1234-j6c)\n\n\n\n\n\n\n\n\n\n\nGitHub: "
      "potato-master369\n\nPress any key to continue..."
      "\nCopyright (C) potato-master369/Random Cool Stuff ig 2026\n");
  wait_for_keypress();
  terminal_setcolor(0x07);
  dobadapple();
  fill_screen();
  terminal_writestring("Demo complete! Power your computer off.");
  while (1) {
    __asm__("cli\n\t" // Disable interrupts
            "hlt");   // Halt
  }
}
