#ifndef _RECORDS_H
#define _RECORDS_H

#include <stdio.h>

typedef struct record {
  unsigned char name_len;  // length of name
  char name[29];           // name; NOT nul-terminated! use name_len above
  short yob;               // year of birth, negative for BC/BCE
} record;
// record size conspires to be 32 bytes on x86-64 :)

int get_yob(FILE *f, const char *name, short *pyob);
// In the file, get the year-of-birth of the record that has the given name.
//
// If found, store the answer at the pyob address, and return 1 (C true). The
// new file position should be right after the found record.
//
// If not found, don't touch the space at pyob. Return 0 (C false). The new file
// position should be end of file.
//
// File position before this may be anywhere. Do your own "seek to the
// beginning" before you search.
//
// If multiple records have the same name, just use the 1st one.

void set_yob(FILE *f, const char *name, short yob);
// In the file, change (overwrite) the year-of-birth of the record that has the
// given name. (You may either rewrite the whole record (easier) or just the
// 2-byte yob field (smarter, but harder).)
//
// File position before this may be anywhere. Do your own "seek to the
// beginning" before you search.
//
// If multiple records have the same name, just change the 1st one.
//
// If no record has the name, add a new record at the end.
//
// In all cases, the new file position after this should be right after
// the updated/new record.

#endif  // #ifndef _RECORDS_H
