#include<stdio.h>

        /* Our structure */
        unsigned short n;
        struct FileRecord // не является корректным определением структуры на C!
        {
            double data[10];
            unsigned short n;
        };

        int main()
        {
                FILE *ptr_myfile;
//                 struct FileRecord my_record;

                ptr_myfile=fopen("001.dat","rb");
                if (!ptr_myfile)
                {
                        printf("Unable to open file!");
                        return 1;
                }
                fseek(ptr_myfile, -sizeof(n), SEEK_END);
                fread(&n,sizeof(n),1,ptr_myfile);
                printf("%hu\n", n);
                fclose(ptr_myfile);
                return 0;
        }