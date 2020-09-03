// Add necessary #include's.
#include <stdio.h>
#include "records.h"
#include <string.h>

// You may add helper functions. Actually there is a reason you should!
//helpter to find record
//sizeof(record);
//need to do strcmp but one is not null terminated
//const char name is null termianate
//fread(some_record, sizeof(record), 1 , f)
//use fseek
//know at end by the fact that we have come to fread ==0
int get_yob(FILE *f, const char *name, short *pyob)
{
//1941
    //char str3[40];
    //seek set only moves cursor to the beginning of the current line
    char nameholder[40];
    int found =0;
    record buffer[100];
    size_t count=0;
    fseek(f,0,SEEK_SET);
    while(fread(buffer, sizeof(record), 1 , f)>=1){
        fseek(f,count,SEEK_SET);//with a loop
        //find name in file f
        fread(buffer, sizeof(record), 1 , f);
        //record.name_len;
        //  fread(pyob, sizeof(char), 1, f);
        if (strncmp(buffer->name,name,buffer->name_len)==0){
                found=1;
                //strcpy(nameholder,buffer->name);
            //name=nameholder;
            *pyob=buffer->yob;
                return 1;
            }
        count+=sizeof(record);
}
    //printf("%d",found):
    return 0;
//    if (found) {
//        *pyob=buffer->yob;
//        return 1;
//
//    }// placeholder, delete if you have your solution
//    else{return 0;}

}
//buffer->yob=yob;//do you need to fwrite?
void set_yob(FILE *f, const char *name, short yob)
{
    //fseek go back two bytesm
            int found =0;
            record buffer[40];
            size_t count=0;
            fseek(f,0,SEEK_SET);
            while(fread(buffer, sizeof(record), 1 , f)>0 && found==0){
                fseek(f,count,SEEK_SET);
                fread(buffer, sizeof(record), 1 , f);
                if (strncmp(buffer->name,name,buffer->name_len)==0){
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
//length of *name, this field not null terminated
 //with a loop
 //each 32 bytes is a a record
 //why did 2 names appear?
 //how do you use fwrite to overwrite?
 //why is there junks?
 //how to gcc?
  //printf("%s",toinsert->name);
// make a new record struct with name and fwrite into it
// In the file, change (overwrite) the year-of-birth of the record that has the
// given name. (You may either rewrite the whole record (easier) or just the
// 2-byte yob field (smarter, but harder).)
//
// File position before this may be anywhere. Do your own "seek to the
// beginning" before you search.
//
// If multiple records have the same name, just change the 1st one.
//
// ***If no record has the name, add a new record at the end.***
//
// In all cases, the new file position after this should be right after
// the updated/new record.
//00000000  0e 44 65 6e 6e 69 73 20  52 69 74 63 68 69 65 78  |.Dennis Ritchiex|
//00000010  78 78 78 78 78 78 78 78  78 78 78 78 78 78 95 07  |xxxxxxxxxxxxxx..|
//00000020  0a 41 72 63 68 69 6d 65  64 65 73 78 78 78 78 78  |.Archimedesxxxxx|
//00000030  78 78 78 78 78 78 78 78  78 78 78 78 78 78 e0 fe  |xxxxxxxxxxxxxx..|
//00000040  0b 41 6c 61 6e 20 54 75  72 69 6e 67 78 78 78 78  |.Alan Turingxxxx|
//00000050  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 07  |xxxxxxxxxxxxxxx.|
//00000060  1d 43 68 61 72 6c 65 73  20 41 6e 74 68 6f 6e 79  |.Charles Anthony|
//00000070  20 52 69 63 68 61 72 64  20 48 6f 61 72 65 8e 07  | Richard Hoare..|
//00000080
