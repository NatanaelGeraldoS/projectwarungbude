#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>

void delay() {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

unsigned long djb2(char *str, int total) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
      hash = ((hash << 5) + hash) + c;
  return hash % total;
}