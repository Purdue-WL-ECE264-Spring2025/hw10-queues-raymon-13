#include "queue.h"
#include "tile_game.h"

static int is_solved(struct game_state state) {
  int expected = 1; 
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++) {
      if (i== 3 && j==3){
        if (state.tiles[i][j] != 0)
          return 0; 
      } else {
          if (state.tiles[i][j] != expected)
            return 0; 
          expected++;
      }
    }
  }
  return 1; 
}

static int is_visited(struct linked_list *visited, size_t state_serial){
  struct list_node *cur = visited->head; 
  while (cur != NULL){
    if (cur->value == state_serial)
      return 1; 
    cur = cur->next; 
  }
  return 0; 
}

void enqueue(struct queue *q, struct game_state state) {
  size_t serial = serialize(state); 
  insert_at_tail(&q->data, serial); 
}

struct game_state dequeue(struct queue *q) { 
  if (q->data.head == NULL) return (struct game_state){0}; 
  size_t serial = remove_from_head(&q->data); 
  return deserialize(serial); 
}

int number_of_moves(struct game_state start) {
  if (is_solved(start)){
    return start.num_steps; 
  }
  struct queue q; 
  q.data.head = NULL; 
  struct linked_list visited; 
  visited.head = NULL; 

  size_t start_serial = serialize(start); 
  insert_at_tail(&visited, start_serial); 
  enqueue(&q, start); 

  while(q.data.head != NULL) {
    struct game_state current = dequeue(&q); 
    if (is_solved(current)){
      free_list(q.data); 
      free_list(visited); 
      return current.num_steps; 
    }

    uint8_t er = current.empty_row; 
    uint8_t ec = current.empty_col; 
    struct game_state neighbor; 

    if(er != 3){
      neighbor = current; 
      move_up(&neighbor); 
      size_t serial = serialize(neighbor); 
      if (!is_visited(&visited, serial)) {
        insert_at_tail(&visited, serial); 
        enqueue(&q, neighbor); 
      }
    }
    if(ec != 0) {
      neighbor = current; 
      move_right(&neighbor); 
      size_t serial = serialize(neighbor); 
      if (!is_visited(&visited, serial)){
        insert_at_tail(&visited, serial); 
        enqueue(&q, neighbor); 
      }
    }
  }
  free_list(visited); 
  return 0; 
}
