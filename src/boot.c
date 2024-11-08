extern void setup_uart();
extern void write_uart(char* s);

char* rvos = "  _______      ______   _____ \n |  __ \\ \\    / / __ \\ / ____|\n | |__) \\ \\  / / |  | | (___  \n |  _  / \\ \\/ /| |  | |\\___ \\ \n | | \\ \\  \\  / | |__| |____) |\n |_|  \\_\\  \\/   \\____/|_____/ \n\n\x00";

void boot() {
  setup_uart();
  write_uart(rvos);

  return;
}