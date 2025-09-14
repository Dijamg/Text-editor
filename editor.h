#ifndef EDITOR_H
#define EDITOR_H

struct editorConfig {
  int cx, cy;
  int screenrows;
  int screencols;
};

extern struct editorConfig E;

void editor_refresh_screen();
void editor_process_keypress();


#endif