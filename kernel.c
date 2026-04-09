unsigned short *vga_buffer = (unsigned short *)0xB8000;
int l = 79;
int y = 0;
int x = 0;
__attribute__((section(".rodata")));
char *logo =
"||   ||  (_)\n"
"||___||  | |\n"
"||   ||  |_|\n";
                                               
void print_char(char c, unsigned char color) {
   const int width = 80;
   if (c == '\n') {
       x = 0;
       y++;
   } else {
       vga_buffer[y * width + x] = (color << 8) | c;
       if (x >= l) {
           y++;
           x = 0;
       } else {
           x++;
       }
   }
}
void print_string(char *str, unsigned char color) {
   for (int i = 0; str[i] != '\0'; i++) {
       print_char(str[i], color);
   }
}
void kernel_main() {
//   print_char('H', 0x9F);
//   print_char('i', 0x9F);
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (0x0F << 8) | ' '; // Black background, white space
    }

   y = 0;
   x = 0;
   print_string(logo, 0x9F);
}
