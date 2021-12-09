#ifndef KISS_EVENTS_SYSTEM_H
#define KISS_EVENTS_SYSTEM_H
#include "kiss_sdl.h"
#include <stdio.h>
#include <iostream>
#include<vector>
class kiss_events_system
{
    public:
        kiss_events_system();
        static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

        static float hscrollbar_event(kiss_hscrollbar *hscrollbar, kiss_textbox *textbox2, SDL_Event *e,
                    int *draw);

        static float hscrollbar_event_spec(kiss_hscrollbar *hscrollbar, kiss_label *label1, SDL_Event *e,
                    int *draw);
        static float hscrollbar_event_diff(kiss_hscrollbar *hscrollbar, kiss_label *label1, SDL_Event *e,
                    int *draw);
        static float hscrollbar_event_amb(kiss_hscrollbar *hscrollbar, kiss_label *label1, SDL_Event *e,
                    int *draw);

        static void dirent_read(kiss_textbox *textbox1, kiss_vscrollbar *vscrollbar1,
                    kiss_textbox *textbox2,	kiss_vscrollbar *vscrollbar2,
                    kiss_label *label_sel);

        static void textbox1_event(kiss_textbox *textbox, SDL_Event *e,
                                   kiss_vscrollbar *vscrollbar1, kiss_textbox *textbox2,
                                   kiss_vscrollbar *vscrollbar2, kiss_label *label_sel, int *draw);

        static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
                                      kiss_textbox *textbox1, int *draw);

        static void textbox2_event(kiss_textbox *textbox, SDL_Event *e,
                                   kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw);

        static void vscrollbar2_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
                                        kiss_textbox *textbox2, int *draw);

        static void button_ok1_event(kiss_button *button, SDL_Event *e,
                                     kiss_window *window1, kiss_window *pane1, kiss_label *label_sel,
                                     kiss_entry *entry, kiss_label *label_res,
                                     kiss_progressbar *progressbar, int *draw);

        static void button_cancel_event(kiss_button *button, SDL_Event *e,
                                        int *quit, int *draw);
        static void button_ok2_event(kiss_button *button, SDL_Event *e,
                                     kiss_window *window1, kiss_window *pane1,
                                     kiss_progressbar *progressbar, int *draw);
        std::vector<float> mouse_move_window1_event(SDL_Window*& WINDOW1, SDL_Event *e, int *draw);
};

#endif // KISS_EVENTS_SYSTEM_H
