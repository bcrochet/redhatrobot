#include <mbed.h>

Serial pc(USBTX, USBRX);

int main() {

  // put your setup code here, to run once:
  pc.printf("Hello world!\n\r");

  while(1) {
    // put your main code here, to run repeatedly:
    pc.putc(pc.getc() + 1);
  }
}