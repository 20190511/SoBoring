#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef true
#define true 1
#define false 0
#endif

typedef struct node {
   char str[100];
   struct node *next;
}Node;

typedef struct q {
   int total_cnt;
   Node* head;
   Node* tail;
}Queue;


int queue_append(Queue* q, char* str) {
   if (q == NULL || str == NULL) {
      return false;
   }
   Node* newNode = (Node*)malloc(sizeof(Node));
   newNode->next = NULL;
   strcpy(newNode->str, str); 
   
   if (q->total_cnt == 0 || q->head == NULL) {
      q->head = q->tail = newNode;
      q->total_cnt = 1;
   }
   else {
      q->tail->next = newNode;
      q->tail = newNode;
      q->total_cnt++;
   }
   return true;
}

Node* pop_front (Queue* q) {
   Node* returnNode;
   if (q == NULL || q->head == NULL) {
      printf("This Queue is NULL\n");
      return NULL;
   }

   if (q->total_cnt == 1) {
      returnNode = q->head;
      q->head = q->tail = NULL;
      q->total_cnt--;
      return returnNode;
   }
   else {
      returnNode = q->head;
      q->head = q->head->next;
      q->total_cnt--;
      return returnNode;
   }
}

Queue* initQueue() {
   Queue* newQ = (Queue*)malloc(sizeof(Queue));
   newQ->head = newQ->tail = NULL;
   newQ->total_cnt = 0;
   return newQ;
}

void print_queue(Queue* q)
{
   Node* mv;
   setbuf(stdout, NULL);
   for (mv = q->head ; mv != NULL ; mv = mv->next) {
      printf("%s", mv->str); 
      if (mv->next != NULL)
         printf(" -> ");
      else
         printf("\n");
   }
   setvbuf(stdout, NULL, _IOLBF, 0);
}


int redirect (int new_fd, int old_fd, int mode) {
   int saved_fd;

   setbuf(stdout, NULL);
   if (mode == 0)
      saved_fd = dup(old_fd);
   dup2 (new_fd, old_fd);
   if (mode == 0)
      return saved_fd;
   else if (mode == 1) {
      close(new_fd);
      return -1;
   }
   else {
      printf("Wront mode : 0:redirect, 1:ending\n");
      return -2;
   }
}

int main(void)
{

   int new_fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
   if (new_fd < 0) {
      fprintf(stderr, "open error for %s\n", "test.txt");
      exit(1);
   }
   int old_fd = redirect(new_fd, STDOUT_FILENO, 0);
   Queue* queue = initQueue();
   queue_append(queue, "fuck you");
   queue_append(queue, "Strang You!");
   queue_append(queue, "GoodGood");
   queue_append(queue, "BaejunHyoeng10");
   print_queue(queue);

   int count = queue->total_cnt;
   for (int i = 0; i < count; i++)
   {
      Node *data = pop_front(queue);
      printf("Pop front data = %s\n", data->str);
      free(data);
      print_queue(queue);
   }

   redirect(old_fd, STDOUT_FILENO, 1);
   close(new_fd);
   printf("redirect sucess\n");
   exit(0);
}