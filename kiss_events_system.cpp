#include "kiss_events_system.h"
#include "kiss_sdl.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include<vector>
kiss_events_system::kiss_events_system()
{
    //ctor
}

void kiss_events_system::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
{
	qsort(textbox->array->data, textbox->array->length, sizeof(void *),
		kiss_string_compare);
	vscrollbar->step = 0.;
	if (textbox->array->length - textbox->maxlines > 0)
		vscrollbar->step = 1. / (textbox->array->length -
			textbox->maxlines);
	textbox->firstline = 0;
	textbox->highlightline = -1;
	vscrollbar->fraction = 0.;
}

float kiss_events_system::hscrollbar_event_spec(kiss_hscrollbar *hscrollbar, kiss_label *label1, SDL_Event *e,int *draw)
{
	if (kiss_hscrollbar_event(hscrollbar, e, draw))
        {

            std::string str1 = std::to_string(hscrollbar->fraction*100);
            char cstr[500];
            //std::cout<<hscrollbar->fraction*100<<std::endl;
            strncpy(cstr, str1.c_str(),sizeof(cstr));
            cstr[sizeof(cstr) - 1] = 0;
            memcpy(label1->text, cstr, sizeof(label1->text));
            delete[] cstr;
            return hscrollbar->fraction*100;
        }
}

float kiss_events_system::hscrollbar_event_diff(kiss_hscrollbar *hscrollbar, kiss_label *label1, SDL_Event *e,int *draw)
{
	if (kiss_hscrollbar_event(hscrollbar, e, draw))
        {

            std::string str1 = std::to_string(hscrollbar->fraction*100);
            char cstr[500];
            strncpy(cstr, str1.c_str(),sizeof(cstr));
            cstr[sizeof(cstr) - 1] = 0;
            memcpy(label1->text, cstr, sizeof(label1->text));
            delete[] cstr;
            return hscrollbar->fraction*100;
        }
}

float kiss_events_system::hscrollbar_event_amb(kiss_hscrollbar *hscrollbar, kiss_label *label1, SDL_Event *e,int *draw)
{
	if (kiss_hscrollbar_event(hscrollbar, e, draw))
        {

            std::string str1 = std::to_string(hscrollbar->fraction*100);
            char cstr[500];
            strncpy(cstr, str1.c_str(),sizeof(cstr));
            cstr[sizeof(cstr) - 1] = 0;
            memcpy(label1->text, cstr, sizeof(label1->text));
            delete[] cstr;
            return hscrollbar->fraction*100;
        }
}

/* Read directory entries into the textboxes */
void kiss_events_system::dirent_read(kiss_textbox *textbox1, kiss_vscrollbar *vscrollbar1,
	kiss_textbox *textbox2,	kiss_vscrollbar *vscrollbar2,
	kiss_label *label_sel)
{
	kiss_dirent *ent;
	kiss_stat s;
	kiss_dir *dir;
	char buf[KISS_MAX_LENGTH], ending[2];

	kiss_array_free(textbox1->array);
	kiss_array_free(textbox2->array);
	kiss_array_new(textbox1->array);
	kiss_array_new(textbox2->array);
	kiss_getcwd(buf, KISS_MAX_LENGTH);
	strcpy(ending, "/");
	if (buf[0] == 'C') strcpy(ending, "\\");
	if (!strcmp(buf, "/") || !strcmp(buf, "C:\\")) strcpy(ending, "");
	kiss_string_copy(label_sel->text, (2 * textbox1->rect.w +
		2 * kiss_up.w) / kiss_textfont.advance, buf, ending);
#ifdef _MSC_VER
	dir = kiss_opendir("*");
#else
	dir = kiss_opendir(".");
#endif
	while ((ent = kiss_readdir(dir))) {
		if (!ent->d_name) continue;
		kiss_getstat(ent->d_name, &s);
		if (kiss_isdir(s))
			kiss_array_appendstring(textbox1->array, 0,
				ent->d_name, "/");
		else if (kiss_isreg(s))
			kiss_array_appendstring(textbox2->array, 0,
				ent->d_name, NULL);
	}
	kiss_closedir(dir);
	text_reset(textbox1, vscrollbar1);
	text_reset(textbox2, vscrollbar2);
}

/* The widget arguments are widgets that this widget talks with */
void kiss_events_system::textbox1_event(kiss_textbox *textbox, SDL_Event *e,
	kiss_vscrollbar *vscrollbar1, kiss_textbox *textbox2,
	kiss_vscrollbar *vscrollbar2, kiss_label *label_sel, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *) kiss_array_data(textbox->array, index),
			"")) {
			textbox->selectedline = -1;
			kiss_chdir((char *) kiss_array_data(textbox->array,
				index));
			dirent_read(textbox, vscrollbar1, textbox2,
				vscrollbar2, label_sel);
			*draw = 1;
		}
	}
}

void kiss_events_system::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
	kiss_textbox *textbox1, int *draw)
{
	int firstline;
	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox1->array->length - textbox1->maxlines > 0) {
		firstline = (int) ((textbox1->array->length -
			textbox1->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox1->firstline = firstline;
		*draw = 1;
	}
}

void kiss_events_system::textbox2_event(kiss_textbox *textbox, SDL_Event *e,
	kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *) kiss_array_data(textbox->array, index),
			"")) {
			kiss_string_copy(entry->text,
				entry->textwidth / kiss_textfont.advance,
				(char *) kiss_array_data(textbox->array,
				index), NULL);
			*draw = 1;
		}
	}
}
std::vector<float> kiss_events_system::mouse_move_window1_event(SDL_Window*& WINDOW1, SDL_Event *e, int *draw)
{
	if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        std::cout<<"MOUSE BUTTON DOWN!"<<std::endl;
        int x, y;
        SDL_GetMouseState( &x, &y );
        std::vector<float> pos;

        pos.push_back(x);
        pos.push_back(y);
        std::cout<<pos[0]<<","<<pos[1]<<std::endl;
        return pos;
    }
    else
    {
     return std::vector<float>{NULL,NULL};
    }
}
void kiss_events_system::vscrollbar2_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
	kiss_textbox *textbox2, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox2->array->length) {
		firstline = (int) ((textbox2->array->length -
			textbox2->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox2->firstline = firstline;
		*draw = 1;
	}
}

void kiss_events_system::button_ok1_event(kiss_button *button, SDL_Event *e,
	kiss_window *window1, kiss_window *pane1, kiss_label *label_sel,
	kiss_entry *entry, kiss_label *label_res,
	kiss_progressbar *progressbar, int *draw)
{
	char buf[KISS_MAX_LENGTH];

	if (kiss_button_event(button, e, draw)) {
		kiss_string_copy(buf, kiss_maxlength(kiss_textfont,
			pane1->rect.w - 2 * kiss_vslider.w,
			label_sel->text, entry->text),
			label_sel->text, entry->text);
        printf(buf);
		kiss_string_copy(label_res->text, KISS_MAX_LABEL,
			"The following path was selected:\n", buf);
		pane1->visible = 1;
		pane1->focus = 1;
		window1->focus = 0;
		button->prelight = 0;
		progressbar->fraction = 0.;
		progressbar->run = 1;
		*draw = 1;
	}
}

void kiss_events_system::button_cancel_event(kiss_button *button, SDL_Event *e,
	int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw)) *quit = 1;
}

void kiss_events_system::button_ok2_event(kiss_button *button, SDL_Event *e,
	kiss_window *window1, kiss_window *pane1,
	kiss_progressbar *progressbar, int *draw)
{
	if (kiss_button_event(button, e, draw)) {
		pane1->visible = 0;
		window1->focus = 1;
		button->prelight = 0;
		progressbar->fraction = 0.;
		progressbar->run = 0;
		*draw = 1;
	}
}
