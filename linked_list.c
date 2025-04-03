#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *node = malloc(sizeof(struct list_node));

  if(node == NULL) return NULL; 
  node->value = value; 
  node->next = NULL; 
  
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *node = new_node(value);
  if (node == NULL) return; 
  node->next = list->head; 
  list->head = node; 
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *node = new_node(value); 
  if(node==NULL) return; 
  if(list->head == NULL){
    list->head = node; 
  } else { 
    struct list_node *current = list->head; 
    while(current->next != NULL){
      current = current->next; 
    }
    current->next = node; 
  }
}


size_t remove_from_head(struct linked_list *list) { 
  if (list->head == NULL) return 0;
  struct list_node *temp = list->head; 
  size_t value = temp->value; 
  list->head = temp->next; 
  //free(temp);
  return value; 
}

size_t remove_from_tail(struct linked_list *list) { 
  if (list->head == NULL) return 0;
  struct list_node *current = list->head; 
  if ( current->next == NULL){
    size_t value = current->value; 
    free(current); 
    list->head = NULL; 
    return value; 
  }
  while (current->next->next != NULL) {
    current = current->next; 
  }
  struct list_node *tail = current->next; 
  size_t value = tail->value; 
  free(tail); 
  current->next = NULL; 
  return value; 
}

void free_list(struct linked_list list) {
  struct list_node *current = list.head;
  while (current != NULL){
    struct list_node *next = current->next; 
    free(current); 
    current = next; 
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
