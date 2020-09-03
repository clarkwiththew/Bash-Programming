#include <stdio.h>
#include "point.h"

size_t save_point_array(const char *pathname, size_t n, const point *a)
{
    FILE *fp;
    fp=fopen(pathname,"w");
  if (fp==NULL)
  {return 0;} // placeholder. replace.
  else {
      size_t tempo0=fwrite(a,sizeof(a[0]),n,fp);
      fclose(fp);
      return tempo0;
  }
}

size_t load_point_array(const char *pathname, size_t n, point *a)
{    FILE *fp;
    fp=fopen(pathname,"r");
  if (fp==NULL)
  {return 0;}
    else {
        size_t tempo1=fread(a,sizeof(a[0]),n,fp);
        fclose(fp);
        return tempo1;
            }
}
