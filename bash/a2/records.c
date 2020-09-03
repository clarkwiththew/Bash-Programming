// Add necessary #include's.
#include <stdio.h>
#include "records.h"
#include <string.h>

int get_yob(FILE *f, const char *name, short *pyob)
{
    int found =0;
    record buffer;
    size_t count=0;
    fseek(f,0,SEEK_SET);
    while(fread(&buffer, sizeof(record), 1 , f)>=1){
        fseek(f,count,SEEK_SET);//with a loop
        fread(&buffer, sizeof(record), 1 , f);

        if (strncmp(buffer.name,name,buffer.name_len)==0){
                found=1;

            *pyob=buffer.yob;
                return 1;
            }
        count+=sizeof(record);
}
    return 0;

}
void set_yob(FILE *f, const char *name, short yob)
{
            int found =0;
            record buffer;
            size_t count=0;
            fseek(f,0,SEEK_SET);
            while(fread(&buffer, sizeof(record), 1 , f)>0 && found==0){
                fseek(f,count,SEEK_SET);
                fread(&buffer, sizeof(record), 1 , f);
                if (strncmp(buffer.name,name,buffer.name_len)==0){
                        found=1;
                    fseek(f,-2,SEEK_CUR);
                  fwrite(&yob , sizeof(short), 1, f);
                    }
                count+=sizeof(record);
        }
    record toinsert;
    if(found==0){
        strncpy(toinsert.name,name,strlen(name));
        toinsert.yob=yob;
        toinsert.name_len=strlen(name);
        fseek(f,0,SEEK_END);
        fwrite(&toinsert , sizeof(toinsert), 1, f);
    }
}
