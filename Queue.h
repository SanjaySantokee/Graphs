struct Node{
	int data;
	Node * next;
};

struct Queue {
	Node * top;
	Node * last;
};

Queue * initQueue ();
bool isEmptyQueue (Queue * q);
int sizeQueue (Queue * q);
void enqueue (Queue * q, int data);
int dequeue (Queue * q);
