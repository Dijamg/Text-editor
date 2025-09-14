#include "editor.h"
#include "terminal.h"

struct editorConfig E;

void init(){
  E.cx = 0;
  E.cy = 0;
  if (get_terminal_window_size(&E.screenrows, &E.screencols) == -1) die("get_terminal_window_size");
}

int main(){
  enable_raw_mode();
  init();

  while(1){
    editor_refresh_screen();
    editor_process_keypress();
  }
}