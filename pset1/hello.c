// https://lab.cs50.io/cs50/labs/2020/x/hello/
// Hello, %name%! (04.04.20)

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Enter your name: ");
    printf("Hello, %s\n", name);
}
