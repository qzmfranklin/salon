#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "magic3.h"
/******************************************************************************/
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
/******************************************************************************/
static const int QUEUE_SIZE=500;

static struct queue_t {
	int data[QUEUE_SIZE];
	int start;
	int end;
	int size;
};

static struct queue_t *queue_create(void)
{
	struct queue_t *q;
	q=(struct queue_t *)malloc(sizeof(struct queue_t));
	assert(q);
	memset(q,0,sizeof(struct queue_t));
	return q;
}

static void queue_destroy(struct queue_t *q)
{
	free(q);
}

static void queue_push(struct queue_t *q, int val)
{
	assert(q->size<QUEUE_SIZE);
	q->data[q->end]=val;
	q->end = (q->end+1) % QUEUE_SIZE;
	q->size++;
}

static void queue_pop(struct queue_t *q)
{
	assert(q->size);
	q->start = (q->start+1) % QUEUE_SIZE;
	q->size--;
} 

static int queue_top(struct queue_t *q)
{
	assert(q->size);
	return q->data[q->start];
} 

// moved into magic3.h
//struct magic3_t {
	//int prev;
	//int base[3];
	//struct queue_t *queue[3];
//};

struct magic3_t *magic3_create(const int base[3])
{
	struct magic3_t *m;
	m=(struct magic3_t*)malloc(sizeof(struct magic3_t));
	assert(m);
	m->prev = 1;
	for (int i = 0; i < 3; i++) {
		m->base[i] = base[i];
		m->queue[i]= queue_create();
	}
	return m;
}

void magic3_destroy(struct magic3_t *m)
{
	for (int i = 0; i < 3; i++)
		queue_destroy(m->queue[i]);
	free(m);
}

static int reap3(struct queue_t *q[3])
{
	int a[3];
	for (int i = 0; i < 3; i++)
		a[i] = queue_top(q[i]);
	if (a[0]==a[1]) {
		if (a[0]==a[2]) {
			queue_pop(q[0]);
			queue_pop(q[1]);
			queue_pop(q[2]);
			return a[0];
		} else if (a[0]<a[2]) {
			queue_pop(q[0]);
			queue_pop(q[1]);
			return a[0];
		} else { 
			queue_pop(q[2]);
			return a[2];
		}
	} else if (a[0]<a[1]) {
		if (a[0]<a[2]) {
			queue_pop(q[0]);
			return a[0];
		} else { 
			if (a[0]==a[2])
				queue_pop(q[0]);
			queue_pop(q[2]);
			return a[2];
		}
	} else {
		if (a[1]<a[2]) {
			queue_pop(q[1]);
			return a[1];
		} else {
			if (a[1]==a[2])
				queue_pop(q[1]);
			queue_pop(q[2]);
			return a[2];
		}
	}
}

int magic3_next(struct magic3_t *m)
{
	for (int i = 0; i < 3; i++)
		queue_push(m->queue[i], m->prev * m->base[i]);
	m->prev = reap3(m->queue);
	return m->prev;
}


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
