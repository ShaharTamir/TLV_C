#include <stdio.h>  /* printf, scanf */

#define QUEUE_SIZE 30

/* queue API functions */
int enqueue(int* queue, int size, int new_number);
int dequeuer(int* queue, int size, int* member);
int is_empty(int queue[], int size);
int is_full(int queue[], int size);
int peek(int queue[], int size);

/* service functions */
char menu();
void handle_enqueue(int queue[], int size);
void handle_dequeue(int queue[], int size);
void handle_peek(int queue[], int size);
void handle_status(int queue[], int size);
int last_var_index(int queue[], int size);


int main(void)
{
    int queue[QUEUE_SIZE] = {0};
    char user_action = 0;

    while(user_action != 'q')
    {
        user_action = menu();

        switch(user_action)
        {
        case 'e':
            handle_enqueue(queue, QUEUE_SIZE);
            break;
        case 'd':
            handle_dequeue(queue, QUEUE_SIZE);
            break;
        case 'p':
            handle_peek(queue, QUEUE_SIZE);
            break;
        case 's':
            handle_status(queue, QUEUE_SIZE);
            break;
        case 'q':
            printf("\ngoodbye!\n");
            break;
        default:
            printf("not a valid action!\n");
            break;
        }
    }

    return 0;
}

int enqueue(int* queue, int size, int new_number)
{
    int last_index = 0;
    
    if(!new_number)
    {
        printf("\n0 is not a valid number\n");
        return 0;
    }

    if(is_full(queue, size))
    {
        printf("\nqueue is full!\n");
        return 0;
    }

    last_index = last_var_index(queue, size);
    
    /* shift the queue right to receive new_number into index 0 */
    while(last_index >= 0)
    {
        queue[last_index + 1] = queue[last_index];
        --last_index;
    }

    queue[0] = new_number;

    return 1;
}

int dequeuer(int* queue, int size, int* member)
{
    int last_index = 0;

    if(is_empty(queue, size))
    {
        printf("\nqueue is empty!\n");
        return 0;
    }

    last_index = last_var_index(queue, size);
    *member = queue[last_index];
    queue[last_index] = 0;

    return 1;
}

int is_empty(int queue[], int size)
{
    /* assuming the queue is initiated with 0 when defined */
    return !queue[0];   /* !0 = 1, !any_number = 0 */
}

int is_full(int queue[], int size)
{
    /* !!any_number = 1, !!0 = 0 
    size - 1 is the last valid position in queue, assuming size is valid (size>0)
    and assuming that the queue is initiated with 0 when defined */
    return !!queue[size - 1]; 
}

int peek(int queue[], int size)
{
    int last_index = 0;

    if(is_empty(queue, size))
    {
        printf("\nqueue is empty!\n");
        return 0;
    }

    last_index = last_var_index(queue, size);
    
    return queue[last_index];
}

char menu()
{
    char user_input;

    printf("\nenter your action:\n");
    printf("(e)nqueue\n(d)equeue\n(p)eek\n(s)tatus\n(q)uit\n");

    do
    {
        user_input = getchar();
    } while (user_input == '\n');

    return user_input;
}

void handle_enqueue(int queue[], int size)
{
    int user_input_enqueue = 0;

    printf("\nenter new member: ");
    scanf("%d", &user_input_enqueue);

    enqueue(queue, QUEUE_SIZE, user_input_enqueue);
}

void handle_dequeue(int queue[], int size)
{
    int deq_val = 0;

    if(dequeuer(queue, size, &deq_val))
        printf("\nthe number is: %d\n", deq_val);    
}

void handle_peek(int queue[], int size)
{
    int peek_val = 0;

    peek_val = peek(queue, size);

    if(peek_val)
        printf("\ncurrent first number in queue is: %d\n", peek_val);
}

void handle_status(int queue[], int size)
{
    if(is_empty(queue, size))
        printf("\nqueue is empty!\n");
    else if(is_full(queue, size))
        printf("\nqueue is full!\n");
    else
        printf("\nqueue is nor empty nor full!\n");
}

int last_var_index(int queue[], int size)
{
    int i = 0;

    if(is_empty(queue, size))
        return 0;

    /* while cells contain value that is not 0 and in queue boundaries */
    while(i < size && queue[i]) 
        ++i;

    return i - 1; /* -1 because the last i value exited the while loop */
}