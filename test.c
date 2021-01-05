// Example Goes In Here

int* p = (int*)0x500000;
int x = 1;

int main(void) {
  p = p + (x++);
  return 0;
}
