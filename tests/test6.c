#include <string.h>
#include "internal.h"

void print(char *s) 
{ 
  write(1, s, strlen(s)); 
} 

int main() 
{ 
  char *addr; 

  addr = malloc(16); 
  if (realloc((void *)addr, -1) == NULL) 
    print("Bonjours\n"); 
} 
