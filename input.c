#include <stdio.h>

#define MAX 100

// Single line comment

/* Multi line comment
   checking block comment */

int main()
{
    int a = 10;
    int b = 20;
    float value = 2.5;
    char ch = 'A';

    // Keywords and identifiers
    int count123;
    int _value;

    // Arithmetic operators
    a + b;
    a - b;
    a * b;
    a / b;
    a % b;

    // Increment and decrement
    a++;
    b--;

    // Relational operators
    a == b;
    a != b;
    a > b;
    a < b;
    a >= b;
    a <= b;

    // Logical operators
    a && b;
    a || b;
    !a;

    // Bitwise operators
    a & b;
    a | b;
    a ^ b;
    ~a;
    a << 2;
    a >> 2;

    // Assignment operators
    a = 5;
    a += 10;
    a -= 5;
    a *= 2;
    a /= 2;
    a %= 2;

    // Bitwise assignment operators
    a &= b;
    a |= b;
    a ^= b;

    // Pointer to structure operator
    ptr->value;

    // String
    printf("Hello World");

    // Escape sequences
    printf("Hello\n");
    printf("Value: %d\n", a);

    // Character
    char x = 'a';

    // Numbers
    int number = 123;
    float decimal = 12.34;

    return 0;
}