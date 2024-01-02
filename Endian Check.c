#include <stdio.h>

int main() {
    int value = 0x4512;
    char *ptr = (char *)&value;

    if (*ptr == 0x45) {
        printf("Big Endian\n");
    } else if (*ptr == 0x12) {
        printf("Little Endian\n");
    } else {
        printf("Unknown Endian\n");
    }
    printf("Order: ");
    for (int i = 0; i < sizeof(value); i++) {
        printf("%02x ", ptr[i]);
    }

    return 0;
}
