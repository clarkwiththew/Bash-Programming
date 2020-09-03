union node {
  enum { LEAF, INTERNAL } tag;
  int x, y, width;
   union node *child[4];  // used when tag==INTERNAL only
  unsigned char rgb[3];   // used when tag==LEAF only
} node;

unsigned char max_red(const union node *v)
{
  if (v->tag==LEAF)
  {return  v->rgb[0];}
  else
  {return  max_red(v->child);}

 return 0;

}
