#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  size_t serial = serialize(state); 
  insert_at_tail(&q->date, serial); 
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
