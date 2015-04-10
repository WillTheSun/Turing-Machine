/************************************************/
/* William Sun									*/
/* February 24, 2015							*/
/* Given turing machine commands, turing.c will */
/* simulate running a turing machine and count 	*/
/* the number of steps until completion.		*/								
/************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define evalC(expr) (fputs(#expr, stdout), (printf(" = %c\n", expr)))
#define evalD(expr) (fputs(#expr, stdout), (printf(" = %d\n", expr)))

typedef struct node {
    struct node *next;
    struct node *prev;
    int s;
} node;

node* createNode(){
	node *c = malloc(sizeof(node));
	c->next = 0;
	c->prev = 0;
	c->s = 'a';
	return c;
}

//Destroy frees every node
int destroy(node *c){
	assert(c);
	node *n = c->next;
	while (n){
		if (n->next)
			assert(n->next->prev == n);
		node *temp = n;
		n = n->next;
		free(temp);
	}
	node *p = c->prev;
	while (p){
		if (p->prev)
			assert(p->prev->next == p);
		node *temp = p;
		p = p->prev;
		free(temp);
	}
	free(c);
	return 1;
}

//Runs to the beginning, then prints the symbols in order
void print(node *a){
	while (a->prev)
		a = a->prev;
	while (a){
		evalC(a->s);
		a = a->next;
	}
}

//Verifies that the input arguments are correct
void checkArguments(int argc, char **argv){
	for (int i=1; i<argc; i++){
		int l = strlen(argv[i]);
		//Checks that length is multiple of 3
		assert(l%3 == 0);
		//Checks that symbol is a lower case letter
		for (int j=0; j<l; j+=3)
			assert(islower(argv[i][j]));
		//Checks that direction is '-' or '='
		for (int j=1; j<l; j+=3)
			assert(argv[i][j] == '-' || argv[i][j] == '+');
		//Checks that state is a digit
		for (int j=2; j<l; j+=3)
			assert(isdigit(argv[i][j]));
	}
}

int main(int argc, char **argv){
	checkArguments(argc, argv);

	node *a = createNode();
	int state = 1;
	int i = 0;

	while (state){
		int symbol = a->s;

		int indexPlace = (symbol - 'a')*3;
		assert(state < argc);
		assert(indexPlace < strlen(argv[state])-2);

		//Look up instructions and update symbol, state
		a->s = argv[state][indexPlace];
		int move = argv[state][indexPlace+1];
		state = argv[state][indexPlace+2] - '0';

		//Move
		if (move == '+'){
			if (a->next)
				a = a->next;
			else{
				node *b = createNode();
				assert(!a->next && !b->prev && !b->next);
				a->next = b;
				b->prev = a;
				a = b;
			}
		}
		else{
			if (a->prev)
				a = a->prev;
			else{
				node *b = createNode();
				assert(!a->prev && !b->next && !b->prev);
				a->prev = b;
				b->next = a;
				a = b;
			}
		} 
		i++;
	}
	destroy(a);
	printf("%d\n",i);
	return 0;
}
