#include <stdbool.h>
#include <stdio.h>

int bitsDiff(int a, int b) {
  int xor = a ^ b;
  int count = 0;
  while (xor > 0) {
    count += xor&1;
    xor >>= 1;
  }
  return count;
}

int main() {
  int num1, num2;
  num1 = 0b100;
  num2 = 0b011;
  // scanf("%d", &num1);
  // scanf("%d", &num2);
  int result = bitsDiff(num1, num2);
  printf("%d\n", result);
  printf("Hello World");
  return 0;
}
