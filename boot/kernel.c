unsigned short *vga_buffer = (unsigned short *)0xB8000;
int l = 79;
int y = 0;
int x = 0;
char *logo =
   "  _    _      _ _         __          __        _     _ \n"
   " | |  | |    | | |        \ \        / /       | |   | |\n"
   " | |__| | ___| | | ___     \ \  /\  / /__  _ __| | __| |\n"
   " |  __  |/ _ \ | |/ _ \     \ \/  \/ / _ \| '__| |/ _` |\n"
   " | |  | |  __/ | | (_) |     \  /\ /  (_) | |  | | (_| |\n"
   " |_|  |_|\___|_|_|\___( )     \/  \/ \___/|_|  |_|\__,_|\n"
   "                      |/                                \n";
                                                     
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
   print_char('H', 0x9F);
   print_char('i', 0x9F);
 
   print_string(logo, 0x9F);
}