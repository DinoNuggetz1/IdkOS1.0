unsigned short *vga_buffer = (unsigned short *)0xB8000;
int l = 79;
int y = 0;
int x = 0;
char files[13] = "read.me";
char cmd[32]; 
int cmd_idx = 0;
int none = 0;
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
void write(char *filename ){
    #define FLASH_START 0x90000000
}





void draw_rect(int x, int y, int width, int height, char *color){
        unsigned char *location = (unsigned char*)0xA0000 + (y * 320) + x;
        *location = color;
        for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            location[(y + i) * 320 + (x + j)] = color;
        }
    }
}
void panic(void){
    print_string("\nCrash Trigger Accepted approx~ 0.5 Secs to crash\nExit Code 0", 0xC0);
        for(volatile int i = 0; i < 800000000; i++);
    volatile int *p = (int *)0;
    *p = 0xDEADBEEF; 
        struct {
            unsigned short limit;
            unsigned int base;
        } __attribute__((packed)) idtr = {0, 0};
        
        __asm__ __volatile__ ("lidt %0" : : "m"(idtr));

        volatile int zero = 0;
        volatile int trigger = 10 / zero;

        __asm__ __volatile__ ("cli; hlt");
}
void print_int(unsigned int n, unsigned char color) {
    char buf[11];
    int i = 10;
    buf[i] = '\0';
    if (n == 0) buf[--i] = '0';
    while (n > 0 && i > 0) {
        buf[--i] = (n % 10) + '0';
        n /= 10;
    }
    print_string(&buf[i], color);
}
int cmp(char *s1, char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void shell(unsigned char scancode) {

    if (scancode < sizeof(scancode_to_ascii)) {
        char c = scancode_to_ascii[scancode];
        if (c == 0) return;

        if (c == '\n') {
            none = 0;
            if (cmd[0] == 'c' && cmd[1] == 'r' && cmd[2] == 'e' && cmd[3] == 'd') {
                print_string("\nBuild 0.2 Beta Type: (x86) GNU 3 License, \nThis software is distributed as is and has no warranty of any kind use at your \nown risk", 0x04);
            none = 1;
            } 
            else if (cmd[0] == 'i' && cmd[1] == 'n' && cmd[2] == 't' && cmd[3] == '0') {
                print_string("\nAttempting to crash shell\nTriggering Kernel Panic", 0x0E);
                panic();
                print_string("\nCrash Failed", 0x04);
            none = 1;
            }
            else if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p') {
                print_string("\nCommands:  \nhelp>>Displays a list of commands\ncred>> lists credits and license\nint0>> attempts to crash shell\nclrs>> Clears screen", 0x0E);
            none = 1;
            }
            else if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 'r' && cmd[3] == 's') {
                    for (int i = 0; i < 80 * 25; i++) {
                        vga_buffer[i] = (0x0F << 8) | ' '; 
                    }
                    
                    y = 0; x = 0;
                    print_string(*logo, 0x0F);
            none = 1;
                }
            else if (cmd[0] == 'g' && cmd[1] == 'u' && cmd[2] == 'i'){
                draw_rect(30, 30, 30, 30, 0x0E);
            none = 1;
            }

            else if (cmd[0] == 'l' && cmd[1] == 'o' && cmd[2] == 'g' && cmd[3] == 'o'){
                print_string("\n", 0x0F);
                print_string(logo, 0x9f);
            none = 1;
            }
            else if (cmd[0] =='c' && cmd[1] == 'h' && cmd[2] == 'k' && cmd[3] == 's' && cmd[4] == 'm'){
                unsigned char* mem = (unsigned char*)0x100000;
                unsigned int actual_mem_val = 0;
                for(int i = 0; i < 1024; i++) {
                    actual_mem_val += mem[i];
                }
                unsigned int res0 = actual_mem_val*144;
                unsigned int chksm = res0/12;
                print_string("\n", 0x0e);
                print_int(chksm, 0x0A);
                if(chksm != 1372344){
                    print_string("Memory Corrupted? Chksm should be 1364040 but is " ,0x04);
                    print_int(chksm, 0x04);
                }
            
                
                none = 1;
            }    
                //char chksm[] = "DCA0771A2646805C92DA7169ACA621A83AF97129EFB6FE8269F56980FC73C07E";
            else if (cmp(cmd, "test") == 0){
                print_string("test complete", 0x0A);
                none = 1;
            }
            
            else if (c == '\n' && cmd[0] == '\0'){
                none = 1;
            }
            if (none == 0) {
            print_string("\nUnknown Command", 0x50);
        }
            print_string("\nShell>> ", 0x0F);
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
            if (cmd_idx < 31) {
                cmd[cmd_idx] = c;
                cmd_idx++;
                cmd[cmd_idx] = '\0';
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
    print_string("\nWelcome To the Shell type ""help"" for a list of commands\nVersion 0.2 GNU 3 (x86)", 0x05);
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
