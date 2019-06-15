#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ERRPRINTF(...) fprintf(stderr, __VA_ARGS__) , exit(EXIT_FAILURE)

typedef enum {
    SUBSYS_DEFAULT = 2
} subsys_t;

short getshort(FILE * p)
{
    short sh = 0;
    for (int i = 0; i < 2; i++)
        sh = (sh << 8) + fgetc(p);
    return sh;
}

int getint(FILE * p)
{
    int n = 0;
    for (int i = 0; i < 4; i++)
        n = (n << 8) + fgetc(p);
    return n;
}

size_t getstring(char * s, FILE * p)
{
    size_t val, len = getshort(p);
    val = fread((void *)s, sizeof(char), len, p);
    s[len] = '\0';
    return val;
};

int gettime(FILE * p)
{
    time_t time = getint(p);
    printf ("Time of packaging: %s\n", ctime(&time));
    return time;
};

int printsubsys(size_t len, const char * s, FILE * p, FILE * op)
{
    int i, j, one, two;
    char sbuffer[1024];   
    
    for (i = 0; i < len; i++)
    {
        printf("%s", s);
        for (j = 0; j < 3; j++)
        {
            getstring(sbuffer, p);
            printf("%s ",sbuffer);
            fputs(sbuffer, op);
        }
        one = getint(p);
        two = getint(p);
        printf("%d %d\n", one, two);
    }
    return one;
};

void parsespec(const char * filename)
{
    FILE * fp, * op;
    char sbuffer[1024];
    char * output = "file.spec";
    const char magicstring[] = "pd001V";
    const char magicbytes[8] = {0x00, 0x07, 0xc4, 0x00, 0x01, 0x07, 0xc3, 0x00 };
    int i, j, k, m, version, order;
    size_t type, numread, len, numstr, nprereq, nincompat, nunknown;

    if ((fp = fopen(filename,"r")) == NULL)
        ERRPRINTF("cannot open file %s for reading\n", filename);

    numread = fread((void *)sbuffer, sizeof(char), 20, fp);

    if (numread != 20)
        ERRPRINTF("EOF encountered at %zd\n",numread);

    if ((strncmp(magicstring, sbuffer, strlen(magicstring)) &
             memcmp(magicbytes,  sbuffer + 12, sizeof(magicbytes)))!=0)
        ERRPRINTF("file %s is not an inst spec file\n", filename);

    if ((op = fopen(output,"w")) == NULL)
        ERRPRINTF("cannot open file %s for writing\n", output);

    fseek(fp, 20, SEEK_SET);

    type = fgetc(fp);

    /* product name */
    getstring(sbuffer, fp);
    printf("product %s\n",sbuffer);
    fputs(sbuffer, op);

    /* id */
    getstring(sbuffer, fp);
    printf("id \"%s\"\n",sbuffer);
    fputs(sbuffer, op);

    /* time of packaging */
    fgetc(fp);
    fgetc(fp);
    gettime(fp);

    /* determine number of images */
    getshort(fp);
    len = getshort(fp);
    if (len == 0) {
        /* print extra strings */
        j = getshort(fp);
        for (i = 0; i < j; i++)
        {
            getstring(sbuffer, fp);
            printf("%s\n",sbuffer);
        }
        len = getshort(fp);
    }
    printf("%zd images\n", len);

    /* loop over images */
    for (i = 0; i < len; i++)
    {
        k = getshort(fp);
        /* this is for /IRIX/DIST/65/6528A/eoe_6528m */
        if (k == 0) getshort(fp);

        /* image name */
        getstring(sbuffer, fp);
        printf("  image %s\n",sbuffer);
        fputs(sbuffer, op);

        /* image id */
        getstring(sbuffer, fp);
        printf("  id \"%s\"\n",sbuffer);
        fputs(sbuffer, op);

        /* counter */
        version = getshort(fp);
        printf("  counter %d \n", version);

        /* order */
        order = getshort(fp);
        printf("  order %d \n", order);

        /* version */
        int one = getint(fp);
        int two = getint(fp);
        printf("  version %d %d\n",one,two);
        
        int nsub = getint(fp);
        if (nsub == 0)
            nsub = getint(fp);

        printf("  %d subsystems\n", nsub);

        /* loop over subsystems */
        for (j = 0; j < nsub; j++)
        {
            m = getshort(fp);
            /* this is for /IRIX/DIST/65/6528A/eoe_6528m */
            if (m == 0)
               m = getshort(fp);
            printf("    %x\n",m);

            /* subsys name */
            getstring(sbuffer, fp);
            printf("    subsys %s ",sbuffer);
            if (m & SUBSYS_DEFAULT) printf("default");
            printf("\n");
            fputs(sbuffer, op);

            /* subsys id */
            getstring(sbuffer, fp);
            printf("    id \"%s\"\n",sbuffer);
            fputs(sbuffer, op);

            /* */
            getstring(sbuffer, fp);
            printf("    %s\n",sbuffer);
            fputs(sbuffer, op);

            getint(fp);
            numstr = getshort(fp);
            printsubsys(numstr,"      replace ",fp,op);

            getshort(fp);
            nprereq = getshort(fp);
            if (nprereq) {
                printsubsys(nprereq,"      prereq ",fp,op);
                getshort(fp);
            }
            if (type > 7) {
                nincompat = getshort(fp);
                if (nincompat) {
                    printsubsys(nincompat,"      incompat ",fp,op);
                }
                getshort(fp);
                numstr = getshort(fp);
                for (k = 0; k < numstr; k++)
                {
                    getstring(sbuffer, fp);
                    printf("      %s\n",sbuffer);
                }
            }
            if (type > 8) {
                nunknown = getshort(fp);
                if (nunknown) {
                    printsubsys(nunknown,"      unknown ",fp,op);
                }
            }
        }
    }
    fclose(fp);
    fclose(op);

    return;
};

int main (int argc, char * argv[])
{
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
