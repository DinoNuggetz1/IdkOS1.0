unsigned short *vga_buffer = (unsigned short *)0xB8000;
int l = 79;
int y = 0;
int x = 0;
char cmd[5]; 
int cmd_idx = 0;
__attribute__((section(".rodata")));
char *logo =
"||   ||  (_)\n"
"||___||  | |\n"
"||   ||  |_|\n";
                            
const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};
static inline unsigned char inportb (unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

unsigned char get_input_key() {
    unsigned char scancode = 0;
    
    while (!(inportb(0x64) & 1));
    
    scancode = inportb(0x60);
    
    return scancode;
}


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


void shell(unsigned char scancode) {

    if (scancode < sizeof(scancode_to_ascii)) {
        char c = scancode_to_ascii[scancode];
        if (c == 0) return;

        if (c == '\n') {
            if (cmd[0] == 'c' && cmd[1] == 'r' && cmd[2] == 'e' && cmd[3] == 'd') {
                print_string("\nBuild 0.1 Beta GNU 3 License, \nThis software is distributed as is and has no warranty of any kind use at your own risk", 0x04);
            } 
            else if (cmd[0] == 'i' && cmd[1] == 'n' && cmd[2] == 't' && cmd[3] == '0') {
                print_string("\nAttempting to crash shell", 0x0E);
                print_string("\nCrash Failed", 0x04);
            }
            
            print_string("\nShell> ", 0x0F);
            cmd_idx = 0; 
            cmd[0] = '\0';
            cmd[1] = '\0';
            cmd[2] = '\0';
            cmd[3] = '\0';
            
        } 
        else if (c == '\b') {
            if (cmd_idx > 0) {
                cmd_idx--;
                x--;
                vga_buffer[y * 80 + x] = (0x0F << 8) | ' ';
            }
        } 
        else {
            if (cmd_idx < 4) {
                cmd[cmd_idx] = c;
                cmd_idx++;
            }
            print_char(c, 0x0F);
        
        }
    }
}

void kernel_main() {
    // Clear screen
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (0x0F << 8) | ' '; 
    }
    
    y = 0; x = 0;
    print_string(logo, 0x9F);
    print_string("\nWelcome To the Shell \nVersion 0.2 GNU 3", 0x05);
    print_string("\nShell> ", 0x0F);
    cmd[0] = '\0';
    cmd[1] = '\0';
    cmd[2] = '\0';
    cmd[3] = '\0';
    while(1) {
        unsigned char scancode = get_input_key();
        
        if (!(scancode & 0x80)) {
            shell(scancode);
        }
    }
}
