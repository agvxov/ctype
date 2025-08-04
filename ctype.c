// @BAKE gcc $@ -o $* -std=c23 -Wall -Wpedantic
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int (*cfun_t)(int);

struct {
    const char * const name;
    cfun_t function;
} objects[] = {
    {
        .name     = "alnum",
        .function = isalnum,
    },
    {
        .name     = "alpha",
        .function = isalpha,
    },
    {
        .name     = "cntrl",
        .function = iscntrl,
    },
    {
        .name     = "digit",
        .function = isdigit,
    },
    {
        .name     = "graph",
        .function = isgraph,
    },
    {
        .name     = "lower",
        .function = islower,
    },
    {
        .name     = "print",
        .function = isprint,
    },
    {
        .name     = "punct",
        .function = ispunct,
    },
    {
        .name     = "space",
        .function = isspace,
    },
    {
        .name     = "upper",
        .function = isupper,
    },
    {
        .name     = "ascii",
        .function = isascii,
    },
    {
        .name     = "blank",
        .function = isblank,
    },
    {
        .name     = "xdigit",
        .function = isxdigit,
    },
    {
        .name     = NULL,
        .function = NULL,
    }
};

static inline
void print_matching(cfun_t f) {
    for (int i = 0; i < 256; i++) {
        if (f(i)) {
            putchar(i);
        }
    }
}

static inline
void usage(void) {
    puts(
        "ctype - cli utility for character types as defined by POSIX\n"
        "\n"
        "  Usage:\n"
        "    ctype <type>          - print all characters belonging to <type>\n"
        "    ctype is<type> <char> - return whether <char> belongs to <type>\n"
        "\n"
        "  Types:\n"
        "    alnum\n"
        "    alpha\n"
        "    cntrl\n"
        "    digit\n"
        "    graph\n"
        "    lower\n"
        "    print\n"
        "    punct\n"
        "    space\n"
        "    upper\n"
        "    ascii\n"
        "    blank\n"
        "    xdigit\n"
    );
}

signed main(const int argc, const char * const * const argv) {
    if (argc < 2) {
        usage();
        exit(1);
    }

    const char * verb    = argv[1];
    const char * subject = argv[2];

    bool is_verb_found = false;

    if (!strcmp(verb, "-h") || !strcmp(verb, "--help")) {
        usage();
        exit(0);
    }

    { // ctype is<type> <char>
        if (verb[0] == 'i'
        &&  verb[1] == 's') {
            if (argc < 3) {
                puts("Question without subject.");
                exit(3);
            }

            verb = verb + 2;

            if (strlen(subject) > 1) {
                puts("Subject too long.");
                exit(4);
            }

            for (auto o = objects; o->name != NULL; o++) {
                if (!strcmp(verb, o->name)) {
                    // NOTE:
                    //  ctype functions are not guaranteed to return 0-1;
                    //  this may or may not be a problem, idk;
                    //  bash shares the definition of truthly, so it should be fine;
                    //    return o->function(subject[0]) ? 1 : 0;
                    return o->function(subject[0]);
                }
            }

            goto end;
        }
    } // --
    
    { // ctype <type>
        for (auto o = objects; o->name != NULL; o++) {
            if (!strcmp(verb, o->name)) {
                print_matching(o->function);
                is_verb_found = true;
                goto end;
            }
        }
    } // --

  end:

    if (!is_verb_found) {
        printf("'%s' is not a type.", verb);
        return 1;
    }

    return 0;
}
