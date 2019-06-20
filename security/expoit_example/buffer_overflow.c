// Compile example: gcc -fno-stack-protector -ggdb buffer_overflow.c
#include <stdio.h>

void Authenticate(char* key)
{
  // strcopy will override authenticated. The program flow is changed.
  int authenticated = 0;
  char buffer[4];
  strcpy(buffer, key);
  if(authenticated)
  {
    printf("buffer overflow");
  }
}


int main()
{
  char* key = "AuthMe";
  Authenticate(key);
  return 0;
}

/* 
 * Buffer overflows can be used to execute injected code, modify data, reveal secret data
 * 1. Inject machine code (e. g. via a input file)
 * 2. Trigger an overflow and override the return address saved on the stack. The new value points to the injected code.
 * --> Injected code is executed --> e. g. shell can be opened and the attacker has access to the system.
 *
 * It is difficult to know the exact location of the injected code and therefore to override the return pointer with the right value. 
 * Especially if you don't know the source code. 
 * Injecting a lot of nop at the beginning of the code and with the assumtion that only a small part of the stack is used, a trial and error approach can be used. 
 *
 * Heap overflow is a variation
 * This is also possible in C++ e. g. overrriding the vtable of an object (inheritance hirachy), because of an overflow in an member variable.
 *
 * Integer overflow
 * Can lead to buffer overflow
 */

