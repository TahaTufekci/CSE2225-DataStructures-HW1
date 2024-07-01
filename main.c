#include <stdio.h>
#include <stdlib.h>

// Taha Tüfekçi 150119050
struct Node {
    int val;
    struct Node *next;
};
typedef struct Node Node;

void reverse(Node** head);
void printList( Node** head,FILE* output_file);
void multiplication( Node** multiplicand, Node** multiplier,FILE *output_file);
Node * get_multiplicand(char* line, FILE * input_file,FILE *output_file);
Node * get_multiplier(char* line, FILE * input_file,FILE  *output_file);

int main() {
    FILE *input_file, *output_file;
    input_file = fopen("C:\\Users\\TAHA\\Desktop\\input.txt", "r");
    output_file = fopen("C:\\Users\\TAHA\\Desktop\\output.txt", "w");
    if (input_file == NULL || output_file == NULL) {
        printf("Error!");
        exit(1);
    }
    char line[150];
    Node *list1, *list2;
    list1 = get_multiplicand(line, input_file, output_file);
    list2 = get_multiplier(line, input_file, output_file);
    multiplication(&list1, &list2, output_file);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
void multiplication(Node **multiplicand, Node **multiplier, FILE *output_file) {
    Node *ptr1 = (*multiplier);
    Node *ptr2 = (*multiplicand);
    Node *result, *tempPtr, *curr, *ex_node, *tempPtr2, *ex_node2;
    int digit_count = 0;
    while (ptr1 != NULL) {
        int carry = 0, carry2 = 0;
        for (int j = 0; j < digit_count; ++j) {
            tempPtr2 = tempPtr2->next;
        }
        for (int i = 0; ptr2 != NULL; i++) {
            if (digit_count != 0) {
                int sum = ptr2->val * ptr1->val;
                tempPtr2->val += sum;
                tempPtr2->val += carry2;
                carry2 = tempPtr2->val / 10;
                tempPtr2->val = tempPtr2->val % 10;

                if (ptr2->next == NULL && carry2 != 0) {
                    ex_node2 = (Node *) malloc(sizeof(Node));
                    tempPtr2->next = ex_node2;
                    tempPtr2 = tempPtr2->next;
                    ex_node2->val = carry2;
                    ex_node2->next = NULL;
                } else {
                    tempPtr2 = tempPtr2->next;
                }
            } else {
                curr = (Node *) malloc(sizeof(Node));
                int sum = ptr2->val * ptr1->val;
                sum += carry;
                carry = sum / 10;
                sum = sum % 10;
                if (i == 0) {
                    result = curr;
                    tempPtr = result;
                    tempPtr2 = result;
                } else {
                    tempPtr->next = curr;
                    tempPtr = curr;
                }
                if (ptr2->next == NULL) {
                    curr->val = sum;
                    if (carry != 0) {
                        ex_node = (Node *) malloc(sizeof(Node));
                        tempPtr->next = ex_node;
                        tempPtr = ex_node;
                        ex_node->val = carry;
                        ex_node->next = NULL;
                    } else {
                        curr->next = NULL;
                    }


                } else {
                    curr->val = sum;
                }

            }
            ptr2 = ptr2->next;
        }
        digit_count++;
        ptr1 = ptr1->next;
        ptr2 = (*multiplicand);
        tempPtr2 = result;
    }
    reverse(&result);
    printList(&result, output_file);
}
void reverse(Node **head) {//This function reverses our linked list
    struct Node *previous = NULL;
    struct Node *current = *head;

    while (current != NULL) {
        struct Node *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *head = previous;
}
Node *get_multiplicand(char *line, FILE *input_file,FILE *output_file) {// This function takes our multiplicand and puts in a linked list
    fgets(line, 100, input_file);
    Node *head, *temp, *curr;
    for (int i = 0; sizeof(line); i++) {
        if (line[i] == '\n') {
            break;
        } else {
            curr = (Node *) malloc(sizeof(Node));
            curr->val = line[i] - '0';
            fprintf(output_file, "%d", curr->val);
            if (i == 0) {
                head = temp = curr;
            } else {
                temp->next = curr;
                temp = curr;
            }
        }

    }
    temp->next = NULL;
    fprintf(output_file, "\n");// To skip to the bottom line in the output file
    reverse(&head);
    return head;

}
Node *get_multiplier(char *line, FILE *input_file,FILE *output_file) {// This function takes our multiplier and puts in a linked list
    fgets(line, 100, input_file);
    Node *head, *temp, *curr;
    for (int i = 0; sizeof(line); i++) {
        if (line[i] == '\0') {
            break;
        } else {
            curr = (Node *) malloc(sizeof(Node));
            curr->val = line[i] - '0';
            fprintf(output_file, "%d", curr->val);
            if (i == 0) {
                head = temp = curr;
            } else {
                temp->next = curr;
                temp = curr;
            }
        }

    }
    temp->next = NULL;
    fprintf(output_file, "\n");// To skip to the bottom line in the output file
    reverse(&head);
    return head;

}
void printList(struct Node **head, FILE *output_file) {//This function prints our result linked list to output file
    struct Node *temp = (*head);
    while (temp != NULL) {
        fprintf(output_file, "%d", temp->val);
        temp = temp->next;
    }
}
