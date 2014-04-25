#ifndef _MAGIC3_H_
#define _MAGIC3_H_
/******************************************************************************/

// Example program:
//int main(int argc, char const* argv[])
//{
	//printf("Enter three positive integers separated by space: ");
	//int base[3];
	//scanf("%d %d %d",base,base+1,base+2);
	//printf("Enter the number of terms to print: ");
	//int num;
	//scanf("%d",&num);

	//struct magic3_t *m = magic3_create(base);
	//for (int i = 0; i < num; i++)
		//printf("%d\n",magic3_next(m));

	////for (int i = 0; i < 3; i++)
		////printf("queue[%d]->size = %d\n",i,m->queue[i]->size);

	//return 0;
//}

struct magic3_t {
	int prev;
	int base[3];
	struct queue_t *queue[3];
};

struct magic3_t *magic3_create(const int base[3]);

void magic3_destroy(struct magic3_t *m);

int magic3_next(struct magic3_t *m);



/******************************************************************************/
#endif /* end of include guard */
