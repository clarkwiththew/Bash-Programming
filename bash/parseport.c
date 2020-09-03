#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <ctype.h>

#include <stdlib.h>

// add necessary #include's

int main(int argc, char *argv[])
{
    
    // We expect the 1st command line argument to be a port number in decimal.
    // Parse it into a suitable number type (many valid choices), convert it to
    // network byte order, store the result in "answer", so that the code below
    // can print out its two bytes in hexadecimal.
    
    // Example: Suppose argv[1] = "5935"
    // 5935 = hexadecimal 172f, so the printf will print:
    // 17 2f
    // If you get 2f 17, that's host byte order, not network byte order.
    
    // If there is no command line argument, or the argument cannot be parsed as a
    // decimal integer, or it is outside the range 1-65535 (inclusive), don't
    // output anything to stdout, exit with exit code 1. (If you like some error
    // message for yourself, use stderr.)
    
    
    uint16_t answer;
    
    int numflag=1;
    
    for (int i=0; argv[1][i]!= '\0'; i++)
    {
        
        //       // check for decimal digits
        if (isdigit(argv[1][i]) == 0)
        {numflag=0;}
    }
    
    if(numflag==0){
        exit(1);
    }
    
    if(argc<2){
        exit(1);
    }
    
    if(argc<2){
        exit(1);
    }
    int x = atoi(argv[1]);
    
    if(x<1 || x> 65535){
        exit(1);
    }
    
    answer=htons(x);
    
    unsigned char *p = (unsigned char *)&answer;
    printf("%02x %02x\n", p[0], p[1]);
    
    return 0;
}
//./a.out "5935"
