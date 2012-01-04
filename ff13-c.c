/*
 ============================================================================
 Name        : ff13-c.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdlib.h>
#include<stdio.h>

#define N 7
struct tree_el {
   struct tree_el * parent;
   int index;
   int val;
   struct tree_el * right, * left;
};

typedef struct tree_el node;

int level_temp;
node * all_node_ptr[12];


void print_true_path(node * tree){

	printf("p= %d, ",tree->index);
	if(tree->parent == NULL)
		return;
	else
		print_true_path(tree->parent);

}

int check_parent(node * tree, int new_idx){
	level_temp++;
	int rt;
	//printf("chk p %d,%d \n",tree->index,new_idx);
	if(tree->parent == NULL)
		if(level_temp == N-1)
		  rt = 2;
		else
		  rt = 1;
	else if(tree->parent->index == new_idx)
    	rt = 0;
    else
    	rt = check_parent(tree->parent, new_idx);
	//printf("rt %d , level %d \n",rt,level_temp);
	return rt;
}
void insert(node * tree) {
	int left_idx, right_idx;
	int left_valid, right_valid;
	left_valid = right_valid = 0;

	//find left child
    left_idx = (tree->index+ tree->val) % N ;

	//find right child
    if(tree->index >= tree->val)
    	right_idx = tree->index - tree->val;
    else
    	right_idx = N + tree->index - tree->val;
    printf("ins %d,%d,%d \n",tree->index,left_idx,right_idx);
    //insert child
      level_temp =0;
	  left_valid = check_parent(tree, all_node_ptr[left_idx]->index);
	  level_temp =0;
	  right_valid = check_parent(tree, all_node_ptr[right_idx]->index);
	  printf("left_valid = %d, right_valid = %d \n",left_valid,right_valid);




    	  if(left_valid>0) {
    	    tree->left = all_node_ptr[left_idx];
    	    tree->left->parent = tree;
    	    insert(tree->left);
    	  }
    	  if(left_idx!=right_idx && right_valid>0) {
            tree->right = all_node_ptr[right_idx];
            tree->right->parent = tree;
            insert(tree->right);
    	  }

	//if leaf return

	  if(left_valid==2) {
		  print_true_path(tree->left);
		  printf("\n");
	  }
	  if(right_valid==2) {
		  print_true_path(tree->right);
	      printf("\n");
      }
	  //printf("ins done \n");

}


void main() {
   node * root;

   int i;
   int input_data[12] = {2,2,2,2,2,2,2,1,1,1,1,1};

   root = NULL;
   level_temp = 0;
   printf(" start ");
   for(i=0;i<N;i++) {

/*
      curr = (node *)malloc(sizeof(node));
      curr->left = curr->right = NULL;
      curr->index = 0;
      curr->val = input_data[0];
*/
	   all_node_ptr[i] = (node *)malloc(sizeof(node));
	   all_node_ptr[i]->left = all_node_ptr[i]->right = NULL;
	   all_node_ptr[i]->parent = NULL;
	   all_node_ptr[i]->index = i;
	   all_node_ptr[i]->val = input_data[i];
	   printf(" %d , ",i);
   }
   printf("\n");
   //first node, start from index0
   root = all_node_ptr[0];
   root->parent = NULL;
      insert(root);

printf("finish");

}
