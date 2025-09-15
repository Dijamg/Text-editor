#include <string.h>
#include "editor.h"
#include <unistd.h>
#include "terminal.h"
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"


#define ABUF_INIT {NULL, 0}
#define CTRL_KEY(k) ((k) & 0x1f)


void editor_draw_rows(){
    for (int y = 0; y < E.screenrows; y++) {
        char buf[16];
        //store the current y as string in buf
        int len = snprintf(buf, sizeof(buf), "%3d:", y);
        //draw line number
        write(STDOUT_FILENO, buf, len);

        write(STDOUT_FILENO, "\x1b[K", 3);

        //Add line change
        if (y < E.screenrows - 1) {
            write(STDERR_FILENO, "\r\n", 2);
        }
    }
}


void editor_refresh_screen(){
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    editor_draw_rows();
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void editor_move_cursor(int key){
    switch(key){
        case ARROW_LEFT:
            if(E.cx != 0){
                E.cx--;
            }
            break;
        case ARROW_RIGHT:
            if(E.cx != E.screencols -1){
                E.cx++;
            }
            break;
        case ARROW_UP:
            if(E.cy != 0){
                E.cy--;
            }
            break;
        case ARROW_DOWN:
            if(E.cy != E.screenrows - 1){
                E.cy++;
            }
            break;
    }
}

void editor_process_keypress() {
    int c = editor_read_key();
    switch (c) {
        case CTRL_KEY('q'):
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);
        exit(0);
        break;
        case HOME_KEY:
        E.cx = 0;
        break;
        case END_KEY:
        E.cx = E.screencols - 1;
        break;
        case PAGE_UP:
        case PAGE_DOWN:
        {
            int times = E.screenrows;
            while (times--)
            editor_move_cursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
        }
        break;
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
        editor_move_cursor(c);
        break;
    }
}