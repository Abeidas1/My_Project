#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "node.h"
#define nullptr ((void*)0)

/*
Adding zero causes problems
*/

struct tree_node root;
struct tree_node fourth_digit[10];
struct tree_node third_digit[10][10];
struct tree_node second_digit[10][10][10];
struct tree_node first_digit[10][10][10][10];
struct list_node *head;

void insert(int);
void initialize_tree();
struct list_node* getNewNode(int);
void insert_new_node(struct list_node *previous, struct list_node *node);
void initialize_arrays(struct tree_node **, int *, int);
void loop_lower_branches_and_add(struct tree_node *, struct list_node *, int, int);
void update_node_and_parents(struct tree_node **, struct list_node *, int);

int main()
{
    initialize_tree();
    int i;
    for (i = 0; i < 50000; i++) {
        int random_number = (rand() % 9999) + 1;
//        printf("%d\n", random_number);
        insert(random_number);
    }
    struct list_node *current = head;
    int boolean = 0;
    for(int j = 0; j <= i; j++) {
//        printf("%d. %4d ((%d times))\n", j + 1, current->data, current->occurrences);
        if (current->data > current->next->data && current->next != head) {
            printf("-----*****>error\n");
            boolean = 1;
        }
        current = current->next;
    }
    if (boolean == 0){
        printf("List is sorted\n");
    }
    return 0;
}

void initialize_tree() {
    root.children = fourth_digit;
    for(int i = 0; i < 10; i++) {
        root.children[i].children = &third_digit[i][0];
        for(int j = 0; j < 10; j++) {
            root.children[i].children[j].children = &second_digit[i][j][0];
            for (int k = 0; k < 10; k++) {
                root.children[i].children[j].children[k].children = &first_digit[i][j][k][0];
            }
        }
    }
}

void insert(int n)
{
    struct tree_node **digit_array = (struct tree_node **)malloc(6 * sizeof(struct tree_node *));
    int *arr = (int *)malloc(5 * sizeof(int));
    initialize_arrays(digit_array, arr, n);
    if (digit_array[1]->least_present_number != 0) {
        digit_array[1]->least_element->occurrences += 1;
    } else {
        struct list_node *new_element = getNewNode(n);
        for (int i = 2; i < 6; i++) {
            if (digit_array[i]->least_present_number != 0) {
                if (n < digit_array[i]->least_present_number) {
                    insert_new_node(digit_array[i]->least_element->previous, new_element);
                    update_node_and_parents(digit_array, new_element, n);
                    return;
                } else if (n > digit_array[i]->greatest_present_number) {
                    insert_new_node(digit_array[i]->greatest_element, new_element);
                    update_node_and_parents(digit_array, new_element, n);
                    return;
                } else if(n > digit_array[i]->least_present_number) {
                    loop_lower_branches_and_add(digit_array[i], new_element, n, arr[i - 1]);
                    update_node_and_parents(digit_array, new_element, n);
                    return;
                }
            }
        }
        insert_new_node(head, new_element);
        update_node_and_parents(digit_array, new_element, n);
    }
}

void loop_lower_branches_and_add(struct tree_node *parent, struct list_node *new_element, int n, int digit)      //here, it is certain that the node will be found
{                                                                                 //because parent.least_present_number != 0
    int i;
    for (i = digit - 1; i >= 0; i--) {
        if (parent->children[i].greatest_present_number != 0) {
            insert_new_node(parent->children[i].greatest_element, new_element);
        return;
        }
    }
}
void update_node_and_parents(struct tree_node **digit_array, struct list_node *element, int n)
{
    element->occurrences = 1;
    digit_array[1]->least_present_number = n;
    digit_array[1]->greatest_present_number = n;
    digit_array[1]->least_element = element;
    digit_array[1]->greatest_element = element;
    for(int i = 2; i < 6; i++) {
        if (digit_array[i]->least_present_number > n || digit_array[i]->least_present_number == 0) {
            digit_array[i]->least_present_number = n;
            digit_array[i]->least_element = element;
        }
        if (digit_array[i]->greatest_present_number < n) {
            digit_array[i]->greatest_present_number = n;
            digit_array[i]->greatest_element = element;
        }
    }
}

void initialize_arrays(struct tree_node **digit_array, int *arr, int n)
{
    arr[1] = n % 10;
    n /= 10;
    arr[2] = n % 10;
    n /= 10;
    arr[3] = n % 10;
    arr[4] = n / 10;
    digit_array[5] = &root;
    digit_array[4] = &root.children[arr[4]];//fourth digit
    digit_array[3] = &digit_array[4]->children[arr[3]];//third digit
    digit_array[2] = &digit_array[3]->children[arr[2]];//second digit
    digit_array[1] = &digit_array[2]->children[arr[1]];//first digitdigit_array[0] = &root;
}

struct list_node* getNewNode(int n)
{
    struct list_node *new_node = (struct list_node*) malloc(sizeof(struct list_node));
    new_node->data = n;
    return new_node;
}

void insert_new_node(struct list_node *previous, struct list_node *node)
{
    if(head == nullptr) {
        head = node;
        node->next = head;
        node->previous = head;
    } else {
        struct list_node *next = previous->next;
        while(previous->data == previous->next->data && previous !=previous->next) {//this can be avoided if the greatest element points to the last identical number
            next = next->next;
            previous = previous->next;
        }
        node->previous = previous;
        node->next = next;
        previous->next = node;
        next->previous = node;
        if (previous->data > node->data) {
            head = node;
        }
    }
}

