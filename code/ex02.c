#include <unistd.h>
int main() {
const char *msg = "Hello, World!\n";
write(1, msg, 13); // 13 is the length of the string
return 0;
}

/*
output
Hello, World!
*/
