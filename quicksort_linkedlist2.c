

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/////////////////////////////////////////////
struct DNODE {
  int val;
  struct DNODE *prev, *next;
};

/////////////////////////////////////////////
void freelist(struct DNODE *head)
{
  struct DNODE *next;
  while ( head ) {
    next = head->next;
    free(head);
    head = next;
  }
}

/////////////////////////////////////////////
void printlist(struct DNODE *head)
{
  while ( head ) {
    fprintf(stdout, "%d\n", head->val);
    head = head->next;
  }
}

void swap(struct DNODE *left,struct DNODE *right)
{
int tmp;
	tmp=left->val;
	left->val=right->val;
	right->val=tmp;
}

int count_list(struct DNODE *head,struct DNODE *tail){
	int i;
	for (i=1;head && (head != tail);i++){
	head=head->next;}
	
	if (head != tail) return 0;
	return i;
}


void quicksort_list(struct DNODE *left, struct DNODE *right)
{ 
if(left == NULL)
  	return;
if(right != NULL)
{
	struct DNODE *pivot, * left_node, * right_node;
	int nleft = 1, nright, count;
	count = count_list(left, right);
	nright = count  ;

	if(nright <= 0) return;

	pivot = left;
	left_node = left;
	right_node = right;

	while(1)
	{
	while(left_node->val < pivot->val)
	{	
		left_node = left_node->next;
		nleft++;
	}
	while(right_node->val > pivot->val)
	{
		if(nright <= 1 || right_node->prev == NULL)
		break;
		right_node = right_node->prev;
		nright--;
	}

	if(nleft >= nright) break;

	swap(left_node, right_node);
	left_node = left_node->next;
	nleft++;
	right_node = right_node->prev;
	nright--;	
	}
	swap(pivot, right_node);	
	quicksort_list(left, right_node->prev);	
	quicksort_list(right_node->next, right);
}	
}

/////////////////////////////////////////////

int main()
{
  int i, N;
  int val;
  struct DNODE *head, *tail, *cur;

  fprintf(stderr, "How many numbers? ");
  fscanf(stdin, "%d", &N);

  head = tail = NULL;
  for (i=0; i<N; i++) {
    if ( fscanf(stdin, "%d", &val) != 1 ) {
      fprintf(stderr, "cannot read integer from standard input.\n");
      freelist(head);
      exit(0);
    }
    else {
      cur = (struct DNODE*) malloc(sizeof(struct DNODE));
      cur->val = val;
      cur->next = NULL;
      if ( !head ) {
	cur->prev = NULL;
	head = tail = cur;
      }
      else {
	tail->next = cur; cur->prev = tail;
	tail = cur;
      }
    }
  }
  quicksort_list(head,tail);

  printlist(head);

  // free memory
  freelist(head);

  return 0;
}
