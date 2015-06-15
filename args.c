#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "args.h"

#define VERSION "1.0"

size_t get_args(int argc, char *argv[], char* space, char* alpha)
{
    char* program_name = argv[0];

    size_t length = 20; /* default to 20 if no length given */

    while(1) {
        int c;
        static struct option long_options[] =
            {
                {"version",       no_argument,       0, 'v'},
                {"help"   ,       no_argument,       0, 'h'},
                {"length" ,       required_argument, 0, 'l'},
                {"no-spaces",     no_argument,       0, 's'},
                {"alphanum-only", no_argument,       0, 'a'},
                {0, 0, 0, 0}
            };

        int option_index = 0;

        c = getopt_long(argc, argv, "vhl:sa", long_options, &option_index);

        if(c == -1)
            break;

        switch(c) {
            case 'v':
                print_version(program_name);
                exit(EXIT_SUCCESS);
            case 'h':
                print_help(program_name);
                exit(EXIT_SUCCESS);
                break;
            case 'l':
                if(sscanf(optarg, "%10zu", &length) == EOF) {
                    fprintf(stderr,
                            "Error parsing length argument: %s\n", optarg);
                    length = 0;
                }
                break;
            case 's':
                *space = 0;
                break;
            case 'a':
                *alpha = 0;
                break;
            default:
                fprintf(stderr, "Error: unrecognized argument\n");
                return 0;
        }
    }
    return length;
}

void print_help(char* program_name)
{
    printf("%s: generate a password from /dev/urandom\n"
           "\t-l num, --length=num\n"
           "\t\tSet the length of the password (default is 20)\n"
           "\t-a, --alphanum-only\n"
           "\t\tUse only alphanumeric characters [a-zA-Z0-9]\n"
           "\t-s, --no-spaces\n"
           "\t\tDon't include space characters in password\n"
           "\t-h, --help\n"
           "\t\tShow this help message\n"
           "\t-v, --version\n"
           "\t\tDisplay version information\n",
            program_name);
}

void print_version(char* program_name)
{
    printf("%s %s\n"
           "License GPLv2+: GNU GPL version 2 or later\n"
           "This is free software: you are free to change and"
              "redistribute it\n"
           "There is NO WARRANTY, to the extent permitted by the law.\n\n"
           "Written by Andrew Mack\n",
            program_name, VERSION);
}
