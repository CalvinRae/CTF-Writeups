/*
 * Pwn-E3  "Small Talk"  -- NCFA Freshers CTF
 * Concept: user input used directly as the template argument of printf().
 * printf(user) lets the user add their own conversion specifiers, which read
 * values out of memory the program left lying around nearby -- where the
 * secret happens to be sitting.
 *
 * Flag read from flag.txt at runtime; not baked into the binary.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    char secret[64];
    memset(secret, 0, sizeof secret);
    FILE *f = fopen("flag.txt", "r");
    if (f) { if (fgets(secret, sizeof secret, f)) {} fclose(f); }
    secret[strcspn(secret, "\r\n")] = 0;   /* keep it as a local */

    char input[128];
    puts("Small-talk service. Say something and I'll say it back.");
    printf("> ");
    if (!fgets(input, sizeof input, stdin)) return 0;

    printf(input);                         /* BUG: uncontrolled template */
    printf("\n");

    /* touch secret so the compiler keeps the local around */
    if (secret[0] == 1) puts(secret);
    return 0;
}
