#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef struct Node{
    float data;
    struct Node *next;
}ListElement;

ListElement *newNode(float );
ListElement *appendElement(ListElement *, float );
int length(ListElement *);
void removeElement(ListElement *, ListElement *);

#endif // TYPES_H_INCLUDED
