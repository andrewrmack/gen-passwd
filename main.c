#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "alphabets.h"
#include "args.h"

int main(int argc, char* argv[])
{
    char space = 1, alpha = 1;
    int length = get_args(argc, argv, &space, &alpha);

    if(length == -1)
        return EXIT_FAILURE;

    char* passwd = (char *) malloc(sizeof(char) * (length + 1));
    memset(passwd, 0, length + 1);

    FILE* frand = fopen("/dev/urandom", "r");
    int i;
    int num;

    for(i = 0; i < length; i++) {
        fread(&num, sizeof(char), 1, frand);
        if(ferror(frand)) {
            fprintf(stderr, "%s: failed to open /dev/urandom/: %s\n",
                    argv[0], strerror(errno));
            free(passwd);
            fclose(frand);
            return EXIT_FAILURE;
        }
        if(alpha == 0)
            passwd[i] = alphanum[num % 62];
        else if (space == 0)
            passwd[i] = nospace[num % 94];
        else
            passwd[i] = printable[num % 95];

    }
    fclose(frand);

    printf("%s\n", passwd);
    free(passwd);
    return 0;
}
