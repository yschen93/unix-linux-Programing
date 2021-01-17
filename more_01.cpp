#include <stdio.h>
#include <string.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE*);
int see_more(FILE*);

int main(int argc, char* argv[])
{
    if (argc == 1)
        do_more(stdin);
    while (--argc) {
        FILE* fp = fopen(*++argv, "r");
        if (!fp) {
            perror("read file error");
            return -1;
        }
        do_more(fp);
    }
}

void do_more(FILE* fp)
{
    char str[LINELEN];
    int res, num_of_lines = 0;
    while (fgets(str, LINELEN, fp)) {
        if (num_of_lines == PAGELEN) {
            FILE* ano = fopen("/dev/tty", "r");
            if (!ano)
            {
                perror("open tty error");
                return;
            }
            res = see_more(ano);
            if (res == 0)
                break;
            else
                num_of_lines -= res;
        }
        if (fputs(str, stdout) == EOF) {
            perror("fputs error");
            return;
        }
        num_of_lines++;
    }
}

int see_more(FILE* fp)
{
    char c;
    if ((c = getc(fp)) != EOF)
    {
        switch(c){
            case 'q': return 0;
            case '\n': return 1;
            case ' ': return PAGELEN;
            default: break;
        }
    }
    return 0;
}
