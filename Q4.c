#include <stdio.h>
#include <string.h>
typedef struct {
  int key;
  long left, right;  // file positions (absolute) or -1
} node;
int find(struct node* node,int num)
{
     if (node == -1)
        return 0;
  
     // first recur on left subtree
     find(node->left);
  
     // then recur on right subtree
     find(node->right);
  
     // now deal with the node
    if (node->key==num){
        return 1;
    }
    return 0;
    
}
int is_present(FILE *f, int needle)
{
    node tree;
    int found =0;

    size_t count=0;
    fseek(f,0,SEEK_SET);
        while(fread(&tree, sizeof(node), 1 , f)>=1){
            fseek(f,count,SEEK_SET);//with a loop
            fread(&tree, sizeof(node), 1 , f);

            if (find(&tree,needle )==1){
                    found=1;

                if( found==1)
                {return 1;}
                }
            count+=sizeof(node);
    }
        return 0;
}

