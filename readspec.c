#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ERRPRINTF(...) fprintf(stderr, __VA_ARGS__) , exit(EXIT_FAILURE)

float checkmagic(const char * buf, const size_t buflen)
{
    int version = 0;
    char strversion[32];
    const char magicstring[] = "pd001V";
    const char magicbytes[8] = {0x00, 0x07, 0xc4, 0x00, 0x01, 0x07, 0xc3, 0x00 };

    if (buflen < 20)
        ERRPRINTF("file is too short for an inst spec file\n");

    if ((memcmp(magicstring, buf, strlen(magicstring))!=0 &
        memcmp(magicbytes,  buf + 12, sizeof(magicbytes)))!=0) {
        ERRPRINTF("file is not an inst spec file\n");
    } else {
        strncpy(strversion, buf + 6, 6);
        printf(" inst version %s\n",strversion);
        if (strversion[3] == 'P') {
            strversion[3] ='.';
            version = strtod(strversion, NULL);
        }
    }
    return version;
}

void display(const char * buf, const size_t buflen)
{
    size_t i;
    printf("buffer size = %zd\n", buflen);
    for (i = 0; i < buflen; i++)
    {
        if ((buf[i] >= 32) && (buf[i] <= 127))
            putchar(buf[i]);
    }
    return;
}

size_t readfile(const char * filename, char ** buf)
{
    FILE * fp;
    size_t i, buflen = 0;

    /* open file */
    if ((fp = fopen(filename,"r")) == NULL)
        ERRPRINTF("cannot open file %s for reading\n", filename);
    /* count bytes */
    while (fgetc(fp) != EOF)
        buflen++;
    /* allocate buffer */
    *buf = (char *) malloc(buflen * sizeof(char));
    /* seek back */
    fseek(fp, 0, SEEK_SET);
    /* read file in buffer */
    for (i = 0; i < buflen; i++)
        (*buf)[i] = fgetc(fp);
    fclose(fp);
    return buflen;
}

void parsespec(const char * filename)
{
    char * buf = NULL;
    size_t n;
    float version;

    n = readfile(filename, &buf);
    version = checkmagic(buf, n);
    printf("version %f\n",version);
    display(buf, n);
    free(buf);
}

int main (int argc, char * argv[])
{
    char * filename;
    switch(argc)
    {
        case 2 :
            parsespec(argv[1]);
            break;
        default :
            fprintf(stderr,"Usage: %s [inst spec file]\n", argv[0]);
            break;
    }
    return EXIT_SUCCESS;
}
