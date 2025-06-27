int s1 = 10;
unsigned int s2 = 20;

char c1 = -128;// char = 8bit, 符号位1bit, 数据位7bit, 2^7 = 128, -128 to 127
unsigned char c2 = 255; 

#include "stdio.h"

const char str1[] = "hello world";

int main()
{
  c1 = c2;//这里其实做了隐式类型转换, 从 unsigned char >> char
  c1 = (char)c2; // 显式类型转换, 从 unsigned char >> char

  float f1 = 3.94f;
  int s1 = (int)f1;
  printf("s1 = %d\n", s1); // 输出 s1 = 3
}