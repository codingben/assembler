/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_MIN_LINE_LENGTH 60
#define LINKED_LIST_MIN_LINE_LENGTH 60

// NOTE: Shouldn't be used by buffer and linked list implementations. Only by buffer.
size_t buffer_line_length = BUFFER_MIN_LINE_LENGTH;

typedef struct node
{
    char *data;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
} LinkedList;

/* Creates a new node. */
Node *createNode()
{
    char *data = calloc(LINKED_LIST_MIN_LINE_LENGTH, sizeof(char));
    if (data == NULL)
    {
        return NULL;
    }

    Node *new_node = calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/* Creates a new list of nodes. */
LinkedList *createList()
{
    Node *new_node = createNode();
    if (new_node == NULL)
    {
        return NULL;
    }

    LinkedList *list = calloc(1, sizeof(LinkedList));
    if (list == NULL)
    {
        return NULL;
    }

    list->head = new_node;
    return list;
}

/* Free all the linked list. */
void freeList(LinkedList *list)
{
    if (list != NULL)
    {
        Node *current_node = list->head;
        Node *next_node = current_node;

        while (current_node != NULL)
        {
            next_node = current_node->next;

            free(current_node);

            current_node = next_node;
        }

        free(list);
    }
}

/* Reads all the text and add it to the linked list. */
int readTextLinkedList(LinkedList *list)
{
    char character;
    int index = 0;

    if (list == NULL)
    {
        return 1;
    }

    Node *current_node = list->head;

    while (1)
    {
        /* Checks if the current node is reached the line limit. */
        if (index == LINKED_LIST_MIN_LINE_LENGTH)
        {
            index = 0;

            Node *new_node = createNode();
            if (new_node == NULL)
            {
                return 1;
            }

            /* Add new node to the last one */
            current_node->next = new_node;
            current_node = new_node;
        }

        if (scanf("%c", &character) != EOF)
        {
            int is_new_line = character == '\n'; /* Check if the character is new line */
            if (is_new_line)
            {
                continue;
            }

            current_node->data[index++] = character;
        }
        else
        {
            break;
        }
    }

    return 0;
}

/* Reads all the text and add it to the buffer. */
int readTextBuffer(char *data)
{
    char character;
    int index = 0;

    if (data == NULL)
    {
        return 1;
    }

    while (1)
    {
        /* Checks if need to allocate more space. */
        if (index == buffer_line_length)
        {
            buffer_line_length += BUFFER_MIN_LINE_LENGTH;

            char *temp = realloc(data, buffer_line_length * sizeof(char));
            if (temp == NULL)
            {
                return 1;
            }

            data = temp;
        }

        if (scanf("%c", &character) != EOF)
        {
            int is_new_line = character == '\n'; /* Check if the character is new line */
            if (is_new_line)
            {
                continue;
            }

            data[index++] = character;
        }
        else
        {
            break;
        }
    }

    return 0;
}

/* Prints all the text from the given linked list. */
int printTextLinkedList(LinkedList *list)
{
    if (list == NULL)
    {
        return 1;
    }

    Node *current_node = list->head;

    for (; current_node != NULL; current_node = current_node->next)
    {
        int i = 0;

        for (i = 0; i < LINKED_LIST_MIN_LINE_LENGTH; ++i)
        {
            printf("%c", current_node->data[i]);
        }
    }

    return 0;
}

/* Prints all the text from the given buffer. */
int printTextBuffer(char *data)
{
    if (data == NULL)
    {
        return 1;
    }

    int i = 0;

    for (i = 0; i < buffer_line_length; ++i)
    {
        printf("%c", data[i]);
    }

    return 0;
}

/*
 * The program will get input of text, save it in the data structure and output the saved text.
 */
int main()
{
    printf("Please type memory option:\n");
    printf("0 = Memory Buffer\n");
    printf("1 = Linked List\n");

    int option = getchar();
    if (option != EOF)
    {
        if (option == '0')
        {
            printf("Chosen Buffer.\n");

            char *data = calloc(BUFFER_MIN_LINE_LENGTH, sizeof(char));
            if (data == NULL)
            {
                printf("\nAn error occurred during allocating the memory.");
            }
            else
            {
                if (readTextBuffer(data) == 0)
                {
                    if (printTextBuffer(data) == 0)
                    {
                        printf("\nExited successfully.");
                    }
                    else
                    {
                        printf("\nAn error occurred during printing the text.");
                    }
                }
                else
                {
                    printf("\nAn error occurred during reading the text.");
                }

                free(data);
            }
        }
        else if (option == '1')
        {
            printf("Chosen Linked List.\n");

            LinkedList *list = createList();
            if (list == NULL)
            {
                printf("\nAn error occurred during allocating the memory.");
            }
            else
            {
                if (readTextLinkedList(list) == 0)
                {
                    if (printTextLinkedList(list) == 0)
                    {
                        printf("\nExited successfully.");
                    }
                    else
                    {
                        printf("\nAn error occurred during printing the text.");
                    }
                }
                else
                {
                    printf("\nAn error occurred during reading the text.");
                }
            }

            freeList(list);
        }
        else
        {
            printf("Unknown Option.\n");
        }
    }

    return 0;
}