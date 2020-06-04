#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void level_1();
void level_2();
void level_3();
void level_4();
void destroy_all();

ALLEGRO_DISPLAY* display;
ALLEGRO_BITMAP* MainMenu = NULL;
ALLEGRO_BITMAP* Background = NULL;
ALLEGRO_BITMAP* creditsBackground = NULL;
ALLEGRO_BITMAP* next1 = NULL;
ALLEGRO_BITMAP* next2 = NULL;
ALLEGRO_BITMAP* next3 = NULL;
ALLEGRO_BITMAP* gameover = NULL;
ALLEGRO_BITMAP* begd = NULL;
ALLEGRO_BITMAP* begu = NULL;
ALLEGRO_BITMAP* leftup = NULL;
ALLEGRO_BITMAP* downright = NULL;
ALLEGRO_BITMAP* leftdown = NULL;
ALLEGRO_BITMAP* leftandright = NULL;
ALLEGRO_BITMAP* rightup = NULL;
ALLEGRO_BITMAP* upanddown = NULL;
ALLEGRO_BITMAP* upright = NULL;
ALLEGRO_BITMAP* graydr = NULL;
ALLEGRO_BITMAP* redd = NULL;
ALLEGRO_BITMAP* redl = NULL;
ALLEGRO_BITMAP* box = NULL;
ALLEGRO_BITMAP* graylr = NULL;
ALLEGRO_BITMAP* grayud = NULL;
ALLEGRO_SAMPLE* boxsound = NULL;
ALLEGRO_SAMPLE* playquit = NULL;
ALLEGRO_SAMPLE* clap = NULL;
ALLEGRO_SAMPLE_INSTANCE* clap1 = NULL;
ALLEGRO_SAMPLE_INSTANCE* boxsound1 = NULL;
ALLEGRO_SAMPLE_INSTANCE* playquit1 = NULL;
ALLEGRO_SAMPLE* theme = NULL;
ALLEGRO_FONT* font = NULL;
int ongamingsc = 0, nextlevel = 0;
int levelsave = 1;

int main() {

	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT ev;

	al_init_primitives_addon();
	al_init_acodec_addon();
	al_install_audio();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	int checkquit = 1, credits = 0;
	float x, y;

	al_init();
	al_install_mouse();
	al_reserve_samples(1);

	if (!al_init()) {
		return -1;
	}

	display = al_create_display(640, 480);

	if (!display) {
		return -1;
	}

	queue = al_create_event_queue();

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	MainMenu = al_load_bitmap("mainmenu.bmp");
	creditsBackground = al_load_bitmap("credits.bmp");
	playquit = al_load_sample("playquit.ogg");
	playquit1 = al_create_sample_instance(playquit);
	al_attach_sample_instance_to_mixer(playquit1, al_get_default_mixer());
	theme = al_load_sample("theme.ogg");

	al_wait_for_event(queue, &ev);
	al_draw_bitmap(MainMenu, 0, 0, 0);

	while (checkquit) {

		al_wait_for_event(queue, &ev);
		al_play_sample(theme, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
		al_draw_bitmap(MainMenu, 0, 0, 0);


		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			x = ev.mouse.x;
			y = ev.mouse.y;
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.x > 277 && ev.mouse.y > 200 && ev.mouse.x < 361 && ev.mouse.y < 250) {
				al_play_sample_instance(playquit1);
				if (levelsave == 0) {
					levelsave = 1;
				}
				ongamingsc = 1;
			}
			if (ev.mouse.x > 35 && ev.mouse.y > 398 && ev.mouse.x < 156 && ev.mouse.y < 448) {
				al_play_sample_instance(playquit1);
				credits = 1;
			}
			if (ev.mouse.x > 278 && ev.mouse.y > 294 && ev.mouse.x < 362 && ev.mouse.y < 344) {
				al_play_sample_instance(playquit1);
				checkquit = 0;
			}
		}
		while (credits) {
			
			al_wait_for_event(queue, &ev);
			al_draw_bitmap(creditsBackground, 0, 0, 0);
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (ev.mouse.x > 427 && ev.mouse.y > 383 && ev.mouse.x < 583 && ev.mouse.y < 437) {
					al_play_sample_instance(playquit1);
					credits = 0;
				}
			}
			al_flip_display();
		}
		while (ongamingsc) {

			if (levelsave == 1) {
				level_1();
			}
			if (levelsave == 2) {
				level_2();
			}
			if (levelsave == 3) {
				level_3();
			}
			if (levelsave == 4) {
				level_4();
			}
			al_flip_display();
		}
		al_flip_display();
	}
	
	if (!checkquit) {

		destroy_all();

	}
	

	return 42;

}

void level_1() {

	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_EVENT ev;
	
	int board[16][2] = { {80,0} ,  {200,0},   {320,0},   {440,0},
						{80,120}, {200,120}, {320,120}, {440,120},
						{80,240}, {200,240}, {320,240}, {440,240},
						{80,360},	{999},    {320,360}, {440,360} };

	int space[1][2] = { 200,360 };
	int final[4][2] = { {80,120}, {80,240}, {80,360}, {200,360}, };

	int i, x = 0, y = 0, j, onlevel = 1, moves = 0;
	bool boxistaken = 0, drop = 0, fixed = 0;

	float xpos = 140;
	float ypos = 60;

	queue = al_create_event_queue();
	playquit = al_load_sample("playquit.ogg");
	playquit1 = al_create_sample_instance(playquit);
	al_attach_sample_instance_to_mixer(playquit1, al_get_default_mixer());
	boxsound = al_load_sample("boxsound.ogg");
	boxsound1 = al_create_sample_instance(boxsound);
	al_attach_sample_instance_to_mixer(boxsound1, al_get_default_mixer());
	clap = al_load_sample("clap.ogg");
	clap1 = al_create_sample_instance(clap);
	al_attach_sample_instance_to_mixer(clap1, al_get_default_mixer());
	theme = al_load_sample("theme.ogg");
	Background = al_load_bitmap("gamingsc.bmp");
	begd = al_load_bitmap("begd.bmp");
	box = al_load_bitmap("board.bmp");
	upanddown = al_load_bitmap("uddu.bmp");
	upright = al_load_bitmap("upright.bmp");
	leftandright = al_load_bitmap("lrrl.bmp");
	redl = al_load_bitmap("redl.bmp");
	graylr = al_load_bitmap("graylr.bmp");
	font = al_load_font("arial.ttf", 28, 0);
	next1 = al_load_bitmap("next1.bmp");
	next2 = al_load_bitmap("next2.bmp");
	next3 = al_load_bitmap("next3.bmp");
	queue = al_create_event_queue();


	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
		
	while (onlevel && ongamingsc) {


		al_draw_bitmap(Background, 0, 0, 0);
		al_wait_for_event(queue, &ev);
		al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "1");
		al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
		al_draw_filled_rectangle(space[0][0], space[0][1], space[0][0] + 120, board[0][1] + 120, al_map_rgb(17, 17, 17));



		for (i = 1; i <= 12; i++) {
			if (i == 4 || i == 8 || i == 9) {
				continue;
			}
			al_draw_bitmap(box, board[i][0], board[i][1], 0);
		}
		al_draw_bitmap(begd, 80, 0, 0);
		al_draw_bitmap(upanddown, board[4][0], board[4][1], 0);
		al_draw_bitmap(upanddown, board[8][0], board[8][1], 0);
		al_draw_bitmap(leftandright, board[9][0], board[9][1], 0);
		al_draw_bitmap(upright, board[12][0], board[12][1], 0);
		al_draw_bitmap(graylr, board[14][0], board[14][1], 0);
		al_draw_bitmap(redl, board[15][0], board[15][1], 0);

		al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			x = ev.mouse.x;
			y = ev.mouse.y;
		}

		if (!((ev.mouse.x >= board[0][0] && ev.mouse.y >= board[0][1] && ev.mouse.x <= board[0][0] + 120 && ev.mouse.y <= board[0][1] + 120)
			|| (ev.mouse.x >= board[15][0] && ev.mouse.y >= board[15][1] && ev.mouse.x <= board[15][0] + 120 && ev.mouse.y <= board[15][1] + 120)
			|| (ev.mouse.x >= board[14][0] && ev.mouse.y >= board[14][1] && ev.mouse.x <= board[14][0] + 120 && ev.mouse.y <= board[14][1] + 120))) {
			fixed = 1;
		}
		else { fixed = 0; }

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			for (i = 0; i <= 15; i++) {

				if (ev.mouse.x <= board[i][0] + 120 && ev.mouse.y <= board[i][1] + 120 && ev.mouse.x >= board[i][0] && ev.mouse.y >= board[i][1] && fixed) {

					al_draw_filled_rectangle(board[i][0], board[i][1], board[i][0] + 120, board[i][1] + 120, al_map_rgb(17, 17, 17));
					al_draw_filled_rectangle(x - 60, y - 60, x + 60, y + 60, al_map_rgb(184, 115, 51));
					al_play_sample_instance(boxsound1);
					boxistaken = 1;
					j = i;
				}
			}
		}

		if (boxistaken) {

			al_draw_filled_rectangle(board[j][0], board[j][1], board[j][0] + 120, board[j][1] + 120, al_map_rgb(17, 17, 17));
			if (j == 9 || j == 14) {
				al_draw_bitmap(leftandright, x - 60, y - 60, 0);
			}
			if (j == 4 || j == 8) {
				al_draw_bitmap(upanddown, x - 60, y - 60, 0);
			}
			if (j == 12) {
				al_draw_bitmap(upright, x - 60, y - 60, 0);
			}
			if (j == 1 || j == 2 || j == 3 || j == 5 || j == 6 || j == 7 || j == 10 || j == 11) {
				al_draw_bitmap(box, x - 60, y - 60, 0);
			}

			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

				if (ev.mouse.x >= space[0][0] && ev.mouse.x <= space[0][0] + 120
					&& ev.mouse.y >= space[0][1] && ev.mouse.y <= space[0][1] + 120
					&& fixed)
				{
					drop = 1;
				}

				if (ev.mouse.x >= board[j][0] + 120 && ev.mouse.x <= board[j][0] + 240 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

					board[j][0] += 120;
					space[0][0] -= 120;
					moves++;
				}

				if (ev.mouse.x <= board[j][0] && ev.mouse.x >= board[j][0] - 120 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

					board[j][0] -= 120;
					space[0][0] += 120;
					moves++;
				}

				if (ev.mouse.y >= board[j][1] + 120 && ev.mouse.y <= board[j][1] + 240 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

					board[j][1] += 120;
					space[0][1] -= 120;
					moves++;
				}

				if (ev.mouse.y <= board[j][1] && ev.mouse.y >= board[j][1] - 120 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

					board[j][1] -= 120;
					space[0][1] += 120;
					moves++;
				}

				boxistaken = 0;
				drop = 0;
			}
		}

		al_flip_display();

		if (board[4][0] == final[0][0] && board[4][1] == final[0][1]
			&& ((board[8][0] == final[1][0] && board[8][1] == final[1][1]) || (board[8][0] == final[2][0] && board[8][1] == final[2][1]))
			&& ((board[12][0] == final[2][0] && board[12][1] == final[2][1]) || (board[8][0] == final[1][0] && board[8][1] == final[1][1]))
			&& board[9][0] == final[3][0] && board[9][1] == final[3][1]) {

			while (ypos <= 360) {

				al_draw_bitmap(Background, 0, 0, 0);

				for (j = 1; j <= 12; j++) {
					if (j == 4 || j == 8) {
						al_draw_bitmap(upanddown, board[j][0], board[j][1], 0);
					}
					if (j == 12) {
						al_draw_bitmap(upright, board[j][0], board[j][1], 0);
					}
					if (j == 1 || j == 2 || j == 3 || j == 5 || j == 6 || j == 7 || j == 10 || j == 11) {
						al_draw_bitmap(box, board[j][0], board[j][1], 0);
					}
				}
				al_draw_bitmap(leftandright, 200, 360, 0);
				al_draw_bitmap(begd, 80, 0, 0);
				al_draw_bitmap(graylr, board[14][0], board[14][1], 0);
				al_draw_bitmap(redl, board[15][0], board[15][1], 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "1");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos += 0.15;
				al_flip_display();
			}

			while (xpos <= 142 || ypos <= 390) {

				al_draw_bitmap(Background, 0, 0, 0);

				for (j = 1; j <= 12; j++) {
					if (j == 4 || j == 8) {
						al_draw_bitmap(upanddown, board[j][0], board[j][1], 0);
					}
					if (j == 12) {
						al_draw_bitmap(upright, board[j][0], board[j][1], 0);
					}
					if (j == 1 || j == 2 || j == 3 || j == 5 || j == 6 || j == 7 || j == 10 || j == 11) {
						al_draw_bitmap(box, board[j][0], board[j][1], 0);
					}
				}
				al_draw_bitmap(begd, 80, 0, 0);
				al_draw_bitmap(leftandright, 200, 360, 0);
				al_draw_bitmap(graylr, board[14][0], board[14][1], 0);
				al_draw_bitmap(redl, board[15][0], board[15][1], 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "1");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (ypos <= 390)
					ypos += 0.15;
				if (xpos <= 142)
					xpos += 0.15;
				al_flip_display();
			}
			while (xpos <= 214 || ypos <= 420) {

				al_draw_bitmap(Background, 0, 0, 0);

				for (j = 1; j <= 12; j++) {
					if (j == 4 || j == 8) {
						al_draw_bitmap(upanddown, board[j][0], board[j][1], 0);
					}
					if (j == 12) {
						al_draw_bitmap(upright, board[j][0], board[j][1], 0);
					}
					if (j == 1 || j == 2 || j == 3 || j == 5 || j == 6 || j == 7 || j == 10 || j == 11) {
						al_draw_bitmap(box, board[j][0], board[j][1], 0);
					}
				}
				al_draw_bitmap(begd, 80, 0, 0);
				al_draw_bitmap(leftandright, 200, 360, 0);
				al_draw_bitmap(graylr, board[14][0], board[14][1], 0);
				al_draw_bitmap(redl, board[15][0], board[15][1], 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "1");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (ypos <= 420)
					ypos += 0.15;
				if (xpos <= 214)
					xpos += 0.15;
				al_flip_display();
			}
			while (xpos <= 513) {

				al_draw_bitmap(Background, 0, 0, 0);

				for (j = 1; j <= 12; j++) {
					if (j == 4 || j == 8) {
						al_draw_bitmap(upanddown, board[j][0], board[j][1], 0);
					}
					if (j == 12) {
						al_draw_bitmap(upright, board[j][0], board[j][1], 0);
					}
					if (j == 1 || j == 2 || j == 3 || j == 5 || j == 6 || j == 7 || j == 10 || j == 11) {
						al_draw_bitmap(box, board[j][0], board[j][1], 0);
					}
				}
				al_draw_bitmap(begd, 80, 0, 0);
				al_draw_bitmap(leftandright, 200, 360, 0);
				al_draw_bitmap(graylr, board[14][0], board[14][1], 0);
				al_draw_bitmap(redl, board[15][0], board[15][1], 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "1");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				xpos += 0.15;
				nextlevel = 1;
				al_flip_display();
			}
			while (nextlevel) {
				al_wait_for_event(queue, &ev);
				al_play_sample_instance(clap1);
				if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (ev.mouse.x < 475 && ev.mouse.x > 176 && ev.mouse.y < 440 && ev.mouse.y > 370) {
						al_play_sample_instance(playquit1);
						nextlevel = 0;
						levelsave = 2;
						onlevel = 0;
					}
				}
				if (moves == 1) {
					al_draw_bitmap(next3, 0, 0, 0);
				}
				if (moves < 4 && moves>1) {
					al_draw_bitmap(next2, 0, 0, 0);
				}
				if (moves > 4) {
					al_draw_bitmap(next1, 0, 0, 0);
				}

				al_flip_display();
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.x < 621 && ev.mouse.x > 576 && ev.mouse.y < 456 && ev.mouse.y > 413) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_play_sample_instance(playquit1);
				al_draw_bitmap(MainMenu, 0, 0, 0);
				onlevel = 0;
				ongamingsc = 0;
			}
		}
	}
}

void level_2() {

	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_EVENT ev;

	int board[16][2] = { {80,0}, {200,0}, {999},{440,0},
						 {999},   {999},    {320,120}, {440,120},
						{80,240}, {200,240}, {320,240}, {440,240},
						{80,360}, {200,360}, {320,360}, {999} };

	int space[4][2] = { {320,0}, {80,120}, {200,120}, {440,360} };
	int final[7][2] = { {440,120}, {80,240}, {200,240}, {440,240}, {200,360}, {320,360}, {440,360} };

	int i, x = 0, y = 0, j, onlevel = 1, moves = 0;
	bool boxistaken = 0, drop = 0, fixed = 0;
	nextlevel = 1;

	float xpos = 140;
	float ypos = 420;

	queue = al_create_event_queue();
	playquit = al_load_sample("playquit.ogg");
	playquit1 = al_create_sample_instance(playquit);
	al_attach_sample_instance_to_mixer(playquit1, al_get_default_mixer());
	boxsound = al_load_sample("boxsound.ogg");
	boxsound1 = al_create_sample_instance(boxsound);
	al_attach_sample_instance_to_mixer(boxsound1, al_get_default_mixer());
	clap = al_load_sample("clap.ogg");
	clap1 = al_create_sample_instance(clap);
	al_attach_sample_instance_to_mixer(clap1, al_get_default_mixer());
	box = al_load_bitmap("board.bmp");
	begu = al_load_bitmap("begu.bmp");
	redd = al_load_bitmap("redd.bmp");
	downright = al_load_bitmap("downright.bmp");
	leftdown = al_load_bitmap("leftdown.bmp");
	upright = al_load_bitmap("upright.bmp");
	upanddown = al_load_bitmap("uddu.bmp");
	leftandright = al_load_bitmap("lrrl.bmp");
	leftup = al_load_bitmap("leftup.bmp");
	font = al_load_font("arial.ttf", 28, 0);
	Background = al_load_bitmap("gamingsc.bmp");
	next1 = al_load_bitmap("next1.bmp");
	next2 = al_load_bitmap("next2.bmp");
	next3 = al_load_bitmap("next3.bmp");

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_wait_for_event(queue, &ev);
	while (onlevel && ongamingsc) {


		al_wait_for_event(queue, &ev);
		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
		al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);

		//spaces
		for (i = 0; i <= 3; i++) {
			al_draw_filled_rectangle(space[i][0], space[i][1], space[i][0] + 120, space[i][1] + 120, al_map_rgb(17, 17, 17));
		}

		//boxes
		for (i = 0; i <= 1; i++) {
			al_draw_bitmap(box, board[i][0], board[i][1], 0);
		}
		for (i = 10; i <= 11; i++) {
			al_draw_bitmap(upanddown, board[i][0], board[i][1], 0);
		}
		al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
		al_draw_bitmap(downright, board[8][0], board[8][1], 0);
		al_draw_bitmap(downright, board[6][0], board[6][1], 0);
		al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
		al_draw_bitmap(upright, board[13][0], board[13][1], 0);
		al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
		al_draw_bitmap(redd, board[3][0], board[3][1], 0);
		al_draw_bitmap(begu, board[12][0], board[12][1], 0);
		al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			x = ev.mouse.x;
			y = ev.mouse.y;
		}

		if (!((ev.mouse.x >= board[3][0] && ev.mouse.y >= board[3][1] && ev.mouse.x <= board[3][0] + 120 && ev.mouse.y <= board[3][1] + 120)
			|| (ev.mouse.x >= board[12][0] && ev.mouse.y >= board[12][1] && ev.mouse.x <= board[12][0] + 120 && ev.mouse.y <= board[12][1] + 120))) {
			fixed = 1;
		}
		else { fixed = 0; }

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			for (i = 0; i <= 15; i++) {

				if (ev.mouse.x <= board[i][0] + 120 && ev.mouse.y <= board[i][1] + 120 && ev.mouse.x >= board[i][0] && ev.mouse.y >= board[i][1] && fixed) {

					al_draw_filled_rectangle(board[i][0], board[i][1], board[i][0] + 120, board[i][1] + 120, al_map_rgb(17, 17, 17));

					al_draw_filled_rectangle(x - 60, y - 60, x + 60, y + 60, al_map_rgb(184, 115, 51));
					al_play_sample_instance(boxsound1);
					boxistaken = 1;
					j = i;
				}
			}
		}

		if (boxistaken) {

			al_draw_filled_rectangle(board[j][0], board[j][1], board[j][0] + 120, board[j][1] + 120, al_map_rgb(17, 17, 17));
			if (j == 11 || j == 10) {
				al_draw_bitmap(upanddown, x - 60, y - 60, 0);
			}
			if (j == 0 || j == 1) {
				al_draw_bitmap(box, x - 60, y - 60, 0);
			}
			if (j == 6 || j == 8) {
				al_draw_bitmap(downright, x - 60, y - 60, 0);
			}
			if (j == 9) {
				al_draw_bitmap(leftdown, x - 60, y - 60, 0);
			}
			if (j == 7) {
				al_draw_bitmap(leftandright, x - 60, y - 60, 0);
			}
			if (j == 14) {
				al_draw_bitmap(leftup, x - 60, y - 60, 0);
			}
			if (j == 13) {
				al_draw_bitmap(upright, x - 60, y - 60, 0);
			}

			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

				for (i = 0; i <= 3; i++) {

					if (ev.mouse.x >= space[i][0] && ev.mouse.x <= space[i][0] + 120
						&& ev.mouse.y >= space[i][1] && ev.mouse.y <= space[i][1] + 120
						&& fixed)
					{
						drop = 1;
					}

					if (ev.mouse.x >= board[j][0] + 120 && ev.mouse.x <= board[j][0] + 240 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

						board[j][0] += 120;
						space[i][0] -= 120;
						moves++;
					}

					if (ev.mouse.x <= board[j][0] && ev.mouse.x >= board[j][0] - 120 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

						board[j][0] -= 120;
						space[i][0] += 120;
						moves++;
					}

					if (ev.mouse.y >= board[j][1] + 120 && ev.mouse.y <= board[j][1] + 240 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

						board[j][1] += 120;
						space[i][1] -= 120;
						moves++;
					}

					if (ev.mouse.y <= board[j][1] && ev.mouse.y >= board[j][1] - 120 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

						board[j][1] -= 120;
						space[i][1] += 120;
						moves++;
					}
				}
				boxistaken = 0;
				drop = 0;
			}
		}

		al_flip_display();

		if (((board[8][0] == final[1][0] && board[8][1] == final[1][1]) || (board[6][0] == final[1][0] && board[6][1] == final[1][1]))
			&& board[9][0] == final[2][0] && board[9][1] == final[2][1]
			&& board[13][0] == final[4][0] && board[13][1] == final[4][1]
			&& board[7][0] == final[5][0] && board[7][1] == final[5][1]
			&& board[14][0] == final[6][0] && board[14][1] == final[6][1]
			&& ((board[10][0] == final[3][0] && board[10][1] == final[3][1]) || (board[11][0] == final[3][0] && board[11][1] == final[3][1]))
			&& ((board[10][0] == final[0][0] && board[10][1] == final[0][1]) || (board[11][0] == final[0][0] && board[11][1] == final[0][1]))) {

			while (ypos >= 344) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos -= 0.15;
				al_flip_display();
			}

			while (ypos >= 306 || xpos <= 171) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (xpos <= 171) {
					xpos += 0.15;
				}
				if (ypos >= 306) {
					ypos -= 0.15;
				}
				al_flip_display();
			}
			while (xpos <= 225) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (xpos <= 225) {
					xpos += 0.15;
				}

				al_flip_display();
			}
			while (ypos <= 351 || xpos <= 255) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (xpos <= 255) {
					xpos += 0.15;
				}
				if (ypos <= 351) {
					ypos += 0.15;
				}
				al_flip_display();
			}
			while (ypos <= 416 || xpos <= 275) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (xpos <= 275) {
					xpos += 0.15;
				}
				if (ypos <= 416) {
					ypos += 0.15;
				}
				al_flip_display();
			}
			while (xpos <= 473) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (xpos <= 478) {
					xpos += 0.15;
				}

				al_flip_display();
			}
			while (ypos >= 368 || xpos <= 502) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				if (xpos <= 502) {
					xpos += 0.15;
				}
				if (ypos >= 368) {
					ypos -= 0.15;
				}
				al_flip_display();
			}

			while (ypos >= 50) {
				al_clear_to_color(al_map_rgb(17, 17, 17));
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_bitmap(upanddown, board[11][0], board[11][1], 0);
				al_draw_bitmap(upanddown, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[0][0], board[0][1], 0);
				al_draw_bitmap(box, board[1][0], board[1][1], 0);
				al_draw_bitmap(downright, board[6][0], board[6][1], 0);
				al_draw_bitmap(downright, board[8][0], board[8][1], 0);
				al_draw_bitmap(leftdown, board[9][0], board[9][1], 0);
				al_draw_bitmap(leftandright, board[7][0], board[7][1], 0);
				al_draw_bitmap(leftup, board[14][0], board[14][1], 0);
				al_draw_bitmap(upright, board[13][0], board[13][1], 0);
				al_draw_bitmap(begu, 80, 360, 0);
				al_draw_bitmap(redd, 440, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "2");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos -= 0.15;

				al_flip_display();
			}
			while (nextlevel) {
				al_play_sample_instance(clap1);
				al_wait_for_event(queue, &ev);
				if (moves < 10) {
					al_draw_bitmap(next3, 0, 0, 0);
				}
				if (moves < 13 && moves>10) {
					al_draw_bitmap(next2, 0, 0, 0);
				}
				if (moves > 13) {
					al_draw_bitmap(next1, 0, 0, 0);
				}
				if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (ev.mouse.x < 475 && ev.mouse.x > 176 && ev.mouse.y < 440 && ev.mouse.y > 375) {
						nextlevel = 0;
						onlevel = 0;
						levelsave = 3;
					}
				}
				al_flip_display();
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.x < 621 && ev.mouse.x > 576 && ev.mouse.y < 456 && ev.mouse.y > 413) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_play_sample_instance(playquit1);
				al_draw_bitmap(MainMenu, 0, 0, 0);
				onlevel = 0;
				ongamingsc = 0;
			}
		}
	}
}

void level_3() {

	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_EVENT ev;
	int board[16][2] = { {80,0},   {999}, {320,0}, {440,0},
						{80,120},  {999}, {320,120}, {440,120},
						{80,240}, {200,240}, {320,240}, {440,240},
						{80,360},  {999}, {320,360}, {440,360} };

	int space[3][2] = { {200,0}, {200,120}, {200,360} };
	int final[4][2] = { {200,0}, {320,0}, {80,120}, {80,240} };

	int i, x = 0, y = 0, j, onlevel = 1, moves = 0;
	bool boxistaken = 0, drop = 0, fixed = 0;
	nextlevel = 1;
	float xpos = 140;
	float ypos = 420;

	queue = al_create_event_queue();
	playquit = al_load_sample("playquit.ogg");
	playquit1 = al_create_sample_instance(playquit);
	al_attach_sample_instance_to_mixer(playquit1, al_get_default_mixer());
	boxsound = al_load_sample("boxsound.ogg");
	boxsound1 = al_create_sample_instance(boxsound);
	al_attach_sample_instance_to_mixer(boxsound1, al_get_default_mixer());
	clap = al_load_sample("clap.ogg");
	clap1 = al_create_sample_instance(clap);
	al_attach_sample_instance_to_mixer(clap1, al_get_default_mixer());
	font = al_load_font("arial.ttf", 24, 0);
	Background = al_load_bitmap("gamingsc.bmp");
	box = al_load_bitmap("board.bmp");
	redl = al_load_bitmap("redl.bmp");
	graydr = al_load_bitmap("graydr.bmp");
	begu = al_load_bitmap("begu.bmp");
	upanddown = al_load_bitmap("uddu.bmp");
	downright = al_load_bitmap("downright.bmp");
	leftup = al_load_bitmap("leftup.bmp");
	leftandright = al_load_bitmap("lrrl.bmp");
	next1 = al_load_bitmap("next1.bmp");
	next2 = al_load_bitmap("next2.bmp");
	next3 = al_load_bitmap("next3.bmp");

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	while (onlevel && ongamingsc) {


		al_wait_for_event(queue, &ev);
		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "3");
		al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);



		//spaces
		for (i = 0; i <= 2; i++) {
			al_draw_filled_rectangle(space[i][0], space[i][1], space[i][0] + 120, space[i][1] + 120, al_map_rgb(17, 17, 17));
		}

		//boxes
		al_draw_bitmap(graydr, board[0][0], board[0][1], 0);
		al_draw_bitmap(leftandright, board[2][0], board[2][1], 0);
		al_draw_bitmap(redl, board[3][0], board[3][1], 0);
		al_draw_bitmap(leftandright, board[4][0], board[4][1], 0);
		al_draw_bitmap(upanddown, board[6][0], board[6][1], 0);
		al_draw_bitmap(box, board[7][0], board[7][1], 0);
		al_draw_bitmap(box, board[11][0], board[11][1], 0);
		al_draw_bitmap(box, board[15][0], board[15][1], 0);
		al_draw_bitmap(box, board[14][0], board[14][1], 0);
		al_draw_bitmap(upanddown, board[8][0], board[8][1], 0);
		al_draw_bitmap(downright, board[9][0], board[9][1], 0);
		al_draw_bitmap(leftup, board[10][0], board[10][1], 0);
		al_draw_bitmap(begu, board[12][0], board[12][1], 0);
		al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			x = ev.mouse.x;
			y = ev.mouse.y;
		}

		if (!((ev.mouse.x >= board[3][0] && ev.mouse.y >= board[3][1] && ev.mouse.x <= board[3][0] + 120 && ev.mouse.y <= board[3][1] + 120)
			|| (ev.mouse.x >= board[12][0] && ev.mouse.y >= board[12][1] && ev.mouse.x <= board[12][0] + 120 && ev.mouse.y <= board[12][1] + 120)
			|| (ev.mouse.x >= board[0][0] && ev.mouse.y >= board[0][1] && ev.mouse.x <= board[0][0] + 120 && ev.mouse.y <= board[0][1] + 120))) {
			fixed = 1;
		}
		else { fixed = 0; }

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			for (i = 0; i <= 15; i++) {

				if (ev.mouse.x <= board[i][0] + 120 && ev.mouse.y <= board[i][1] + 120 && ev.mouse.x >= board[i][0] && ev.mouse.y >= board[i][1] && fixed) {

					al_draw_filled_rectangle(board[i][0], board[i][1], board[i][0] + 120, board[i][1] + 120, al_map_rgb(17, 17, 17));
					al_draw_filled_rectangle(x - 60, y - 60, x + 60, y + 60, al_map_rgb(184, 115, 51));
					al_play_sample_instance(boxsound1);
					boxistaken = 1;
					j = i;
				}
			}
		}

		if (boxistaken) {
			al_draw_filled_rectangle(board[j][0], board[j][1], board[j][0] + 120, board[j][1] + 120, al_map_rgb(17, 17, 17));
			if (j == 7 || j == 11 || j == 14 || j == 15) {
				al_draw_bitmap(box, x - 60, y - 60, 0);
			}
			if (j == 2 || j == 4) {
				al_draw_bitmap(leftandright, x - 60, y - 60, 0);
			}
			if (j == 8 || j == 6) {
				al_draw_bitmap(upanddown, x - 60, y - 60, 0);
			}
			if (j == 9) {
				al_draw_bitmap(downright, x - 60, y - 60, 0);
			}
			if (j == 10) {
				al_draw_bitmap(leftup, x - 60, y - 60, 0);
			}

			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

				for (i = 0; i <= 2; i++) {

					if (ev.mouse.x >= space[i][0] && ev.mouse.x <= space[i][0] + 120
						&& ev.mouse.y >= space[i][1] && ev.mouse.y <= space[i][1] + 120
						&& fixed)
					{
						drop = 1;
					}

					if (ev.mouse.x >= board[j][0] + 120 && ev.mouse.x <= board[j][0] + 240 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

						board[j][0] += 120;
						space[i][0] -= 120;
						moves++;
					}

					if (ev.mouse.x <= board[j][0] && ev.mouse.x >= board[j][0] - 120 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

						board[j][0] -= 120;
						space[i][0] += 120;
						moves++;
					}

					if (ev.mouse.y >= board[j][1] + 120 && ev.mouse.y <= board[j][1] + 240 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

						board[j][1] += 120;
						space[i][1] -= 120;
						moves++;
					}

					if (ev.mouse.y <= board[j][1] && ev.mouse.y >= board[j][1] - 120 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

						board[j][1] -= 120;
						space[i][1] += 120;
						moves++;
					}
				}
				boxistaken = 0;
				drop = 0;
			}
		}

		al_flip_display();

		if (((board[2][0] == final[0][0] && board[2][1] == final[0][1]) || (board[4][0] == final[0][0] && board[4][1] == final[0][1]))
			&& ((board[2][0] == final[1][0] && board[2][1] == final[1][1]) || (board[4][0] == final[1][0] && board[4][1] == final[1][1]))
			&& ((board[6][0] == final[2][0] && board[6][1] == final[2][1]) || (board[8][0] == final[2][0] && board[8][1] == final[2][1]))
			&& ((board[6][0] == final[3][0] && board[6][1] == final[3][1]) || (board[8][0] == final[3][0] && board[8][1] == final[3][1]))
			) {
				{

					for (int i = 0; i < 3300; i++) {
						al_clear_to_color(al_map_rgb(17, 17, 17));
						al_draw_bitmap(Background, 0, 0, 0);
						al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "3");
						al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
						al_draw_bitmap(graydr, board[0][0], board[0][1], 0);
						al_draw_bitmap(leftandright, board[2][0], board[2][1], 0);
						al_draw_bitmap(redl, board[3][0], board[3][1], 0);
						al_draw_bitmap(leftandright, board[4][0], board[4][1], 0);
						al_draw_bitmap(upanddown, board[6][0], board[6][1], 0);
						al_draw_bitmap(box, board[7][0], board[7][1], 0);
						al_draw_bitmap(box, board[11][0], board[11][1], 0);
						al_draw_bitmap(box, board[15][0], board[15][1], 0);
						al_draw_bitmap(box, board[14][0], board[14][1], 0);
						al_draw_bitmap(upanddown, board[8][0], board[8][1], 0);
						al_draw_bitmap(downright, board[9][0], board[9][1], 0);
						al_draw_bitmap(leftup, board[10][0], board[10][1], 0);
						al_draw_bitmap(begu, board[12][0], board[12][1], 0);
						al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
						ypos -= 0.1;
						al_flip_display();
					}

					for (int i = 0; i < 300; i++) {
						al_clear_to_color(al_map_rgb(17, 17, 17));
						al_draw_bitmap(Background, 0, 0, 0);
						al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "3");
						al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
						al_draw_bitmap(graydr, board[0][0], board[0][1], 0);
						al_draw_bitmap(leftandright, board[2][0], board[2][1], 0);
						al_draw_bitmap(redl, board[3][0], board[3][1], 0);
						al_draw_bitmap(leftandright, board[4][0], board[4][1], 0);
						al_draw_bitmap(upanddown, board[6][0], board[6][1], 0);
						al_draw_bitmap(box, board[7][0], board[7][1], 0);
						al_draw_bitmap(box, board[11][0], board[11][1], 0);
						al_draw_bitmap(box, board[15][0], board[15][1], 0);
						al_draw_bitmap(box, board[14][0], board[14][1], 0);
						al_draw_bitmap(upanddown, board[8][0], board[8][1], 0);
						al_draw_bitmap(downright, board[9][0], board[9][1], 0);
						al_draw_bitmap(leftup, board[10][0], board[10][1], 0);
						al_draw_bitmap(begu, board[12][0], board[12][1], 0);
						al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
						ypos -= 0.1;
						xpos += 0.1;
						al_flip_display();
					}

					for (int i = 0; i < 3300; i++) {
						al_clear_to_color(al_map_rgb(17, 17, 17));
						al_draw_bitmap(Background, 0, 0, 0);
						al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "3");
						al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
						al_draw_bitmap(graydr, board[0][0], board[0][1], 0);
						al_draw_bitmap(leftandright, board[2][0], board[2][1], 0);
						al_draw_bitmap(redl, board[3][0], board[3][1], 0);
						al_draw_bitmap(leftandright, board[4][0], board[4][1], 0);
						al_draw_bitmap(upanddown, board[6][0], board[6][1], 0);
						al_draw_bitmap(box, board[7][0], board[7][1], 0);
						al_draw_bitmap(box, board[11][0], board[11][1], 0);
						al_draw_bitmap(box, board[15][0], board[15][1], 0);
						al_draw_bitmap(box, board[14][0], board[14][1], 0);
						al_draw_bitmap(upanddown, board[8][0], board[8][1], 0);
						al_draw_bitmap(downright, board[9][0], board[9][1], 0);
						al_draw_bitmap(leftup, board[10][0], board[10][1], 0);
						al_draw_bitmap(begu, board[12][0], board[12][1], 0);
						al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
						xpos += 0.1;
						al_flip_display();
						nextlevel = 1;
					}
				}
				while (nextlevel) {
					al_play_sample_instance(clap1);
					al_wait_for_event(queue, &ev);
					if (moves < 5) {
						al_draw_bitmap(next3, 0, 0, 0);
					}
					if (moves < 10 && moves > 5); {
						al_draw_bitmap(next2, 0, 0, 0);
					}
					if (moves > 10) {
						al_draw_bitmap(next1, 0, 0, 0);
					}
					if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
						if (ev.mouse.x < 475 && ev.mouse.x > 176 && ev.mouse.y < 440 && ev.mouse.y > 375) {
							al_play_sample_instance(playquit1);
							nextlevel = 0;
							onlevel = 0;
							levelsave = 4;
						}
					}
					al_flip_display();
				}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.x < 621 && ev.mouse.x > 576 && ev.mouse.y < 456 && ev.mouse.y > 413) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_play_sample_instance(playquit1);
				al_draw_bitmap(MainMenu, 0, 0, 0);
				onlevel = 0;
				ongamingsc = 0;
			}
		}
	}
}

void level_4() {

	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_EVENT ev;
	int board[16][2] = { {999},   {200,0},  {320,0}, {440,0},
						{80,120}, {200,120},   {999},  {440,120},
						{80,240}, {200,240}, {320,240}, {440,240},
						{80,360}, {200,360},   {999}, {440,360} };

	int space[3][2] = { {90,0}, {320,120}, {320,360} };
	int final[5][2] = { {200,0}, {200,120}, {200,240}, {80,360}, {200,360} };

	int i, x = 0, y = 0, j, moves = 0;
	bool boxistaken = 0, drop = 0, fixed = 0, onlevel = 1;

	float xpos = 140;
	float ypos = 180;

	queue = al_create_event_queue();
	playquit = al_load_sample("playquit.ogg");
	playquit1 = al_create_sample_instance(playquit);
	al_attach_sample_instance_to_mixer(playquit1, al_get_default_mixer());
	boxsound = al_load_sample("boxsound.ogg");
	boxsound1 = al_create_sample_instance(boxsound);
	al_attach_sample_instance_to_mixer(boxsound1, al_get_default_mixer());
	clap = al_load_sample("clap.ogg");
	clap1 = al_create_sample_instance(clap);
	al_attach_sample_instance_to_mixer(clap1, al_get_default_mixer());
	font = al_load_font("arial.ttf", 24, 0);
	Background = al_load_bitmap("gamingsc.bmp");
	box = al_load_bitmap("board.bmp");
	graylr = al_load_bitmap("graylr.bmp");
	grayud = al_load_bitmap("grayud.bmp");
	begd = al_load_bitmap("begd.bmp");
	redl = al_load_bitmap("redl.bmp");
	downright = al_load_bitmap("downright.bmp");
	upanddown = al_load_bitmap("uddu.bmp");
	upright = al_load_bitmap("upright.bmp");
	leftup = al_load_bitmap("leftup.bmp");
	gameover = al_load_bitmap("gameover.bmp");

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	while (onlevel && ongamingsc) {

		al_wait_for_event(queue, &ev);
		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
		al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);

		//spaces
		for (i = 0; i <= 2; i++) {
			al_draw_filled_rectangle(space[i][0], space[i][1], space[i][0] + 120, space[i][1] + 120, al_map_rgb(17, 17, 17));
		}

		//boxes
		al_draw_bitmap(box, board[9][0], board[9][1], 0);
		al_draw_bitmap(box, board[10][0], board[10][1], 0);
		al_draw_bitmap(box, board[11][0], board[11][1], 0);
		al_draw_bitmap(downright, board[1][0], board[1][1], 0);
		al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
		al_draw_bitmap(redl, board[3][0], board[3][1], 0);
		al_draw_bitmap(begd, board[4][0], board[4][1], 0);
		al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
		al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
		al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
		al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
		al_draw_bitmap(upright, board[12][0], board[12][1], 0);
		al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
		al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			x = ev.mouse.x;
			y = ev.mouse.y;
		}

		if (!((ev.mouse.x >= board[2][0] && ev.mouse.y >= board[2][1] && ev.mouse.x <= board[2][0] + 120 && ev.mouse.y <= board[2][1] + 120)
			|| (ev.mouse.x >= board[3][0] && ev.mouse.y >= board[3][1] && ev.mouse.x <= board[3][0] + 120 && ev.mouse.y <= board[3][1] + 120)
			|| (ev.mouse.x >= board[4][0] && ev.mouse.y >= board[4][1] && ev.mouse.x <= board[4][0] + 120 && ev.mouse.y <= board[4][1] + 120)
			|| (ev.mouse.x >= board[8][0] && ev.mouse.y >= board[8][1] && ev.mouse.x <= board[8][0] + 120 && ev.mouse.y <= board[8][1] + 120)
			)) {
			fixed = 1;
		}
		else { fixed = 0; }

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			for (i = 0; i <= 15; i++) {

				if (ev.mouse.x <= board[i][0] + 120 && ev.mouse.y <= board[i][1] + 120 && ev.mouse.x >= board[i][0] && ev.mouse.y >= board[i][1] && fixed) {

					al_draw_filled_rectangle(board[i][0], board[i][1], board[i][0] + 120, board[i][1] + 120, al_map_rgb(17, 17, 17));
					al_draw_filled_rectangle(x - 60, y - 60, x + 60, y + 60, al_map_rgb(184, 115, 51));
					al_play_sample_instance(boxsound1);
					boxistaken = 1;
					j = i;
				}
			}
		}

		if (boxistaken) {

			al_draw_filled_rectangle(board[j][0], board[j][1], board[j][0] + 120, board[j][1] + 120, al_map_rgb(17, 17, 17));
			if (j == 9 || j == 10 || j == 11) {
				al_draw_bitmap(box, x - 60, y - 60, 0);
			}
			if (j == 1) {
				al_draw_bitmap(downright, x - 60, y - 60, 0);
			}
			if (j == 5 || j == 7 || j == 15) {
				al_draw_bitmap(upanddown, x - 60, y - 60, 0);
			}
			if (j == 12) {
				al_draw_bitmap(upright, x - 60, y - 60, 0);
			}
			if (j == 13) {
				al_draw_bitmap(rightup, x - 60, y - 60, 0);
			}
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

				for (i = 0; i <= 2; i++) {

					if (ev.mouse.x >= space[i][0] && ev.mouse.x <= space[i][0] + 120
						&& ev.mouse.y >= space[i][1] && ev.mouse.y <= space[i][1] + 120
						&& fixed)
					{
						drop = 1;
					}

					if (ev.mouse.x >= board[j][0] + 120 && ev.mouse.x <= board[j][0] + 240 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

						board[j][0] += 120;
						space[i][0] -= 120;
						moves++;
					}

					if (ev.mouse.x <= board[j][0] && ev.mouse.x >= board[j][0] - 120 && ev.mouse.y >= board[j][1] && ev.mouse.y <= board[j][1] + 120 && drop) {

						board[j][0] -= 120;
						space[i][0] += 120;
						moves++;
					}

					if (ev.mouse.y >= board[j][1] + 120 && ev.mouse.y <= board[j][1] + 240 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

						board[j][1] += 120;
						space[i][1] -= 120;
						moves++;
					}

					if (ev.mouse.y <= board[j][1] && ev.mouse.y >= board[j][1] - 120 && ev.mouse.x >= board[j][0] && ev.mouse.x <= board[j][0] + 120 && drop) {

						board[j][1] -= 120;
						space[i][1] += 120;
						moves++;
					}
				}
				boxistaken = 0;
				drop = 0;
			}
		}

		al_flip_display();

		if (board[1][0] == final[0][0] && board[1][1] == final[0][1]
			&& ((board[5][0] == final[1][0] && board[5][1] == final[1][1]) || (board[7][0] == final[1][0] && board[7][1] == final[1][1]) || (board[15][0] == final[1][0] && board[15][1] == final[1][1]))
			&& ((board[5][0] == final[2][0] && board[5][1] == final[2][1]) || (board[7][0] == final[2][0] && board[7][1] == final[2][1]) || (board[15][0] == final[2][0] && board[15][1] == final[2][1]))
			&& board[12][0] == final[3][0] && board[12][1] == final[3][1]
			&& board[13][0] == final[4][0] && board[13][1] == final[4][1]) {

			for (int i = 0; i < 2100; i++) {
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_bitmap(box, board[9][0], board[9][1], 0);
				al_draw_bitmap(box, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[11][0], board[11][1], 0);
				al_draw_bitmap(downright, board[1][0], board[1][1], 0);
				al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
				al_draw_bitmap(redl, board[3][0], board[3][1], 0);
				al_draw_bitmap(begd, board[4][0], board[4][1], 0);
				al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
				al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
				al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
				al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
				al_draw_bitmap(upright, board[12][0], board[12][1], 0);
				al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos += 0.1;
				al_flip_display();
			}

			for (int i = 0; i < 300; i++) {
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_bitmap(box, board[9][0], board[9][1], 0);
				al_draw_bitmap(box, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[11][0], board[11][1], 0);
				al_draw_bitmap(downright, board[1][0], board[1][1], 0);
				al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
				al_draw_bitmap(redl, board[3][0], board[3][1], 0);
				al_draw_bitmap(begd, board[4][0], board[4][1], 0);
				al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
				al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
				al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
				al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
				al_draw_bitmap(upright, board[12][0], board[12][1], 0);
				al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos += 0.1;
				xpos += 0.1;
				al_flip_display();
			}

			for (int i = 0; i < 600; i++) {
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_bitmap(box, board[9][0], board[9][1], 0);
				al_draw_bitmap(box, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[11][0], board[11][1], 0);
				al_draw_bitmap(downright, board[1][0], board[1][1], 0);
				al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
				al_draw_bitmap(redl, board[3][0], board[3][1], 0);
				al_draw_bitmap(begd, board[4][0], board[4][1], 0);
				al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
				al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
				al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
				al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
				al_draw_bitmap(upright, board[12][0], board[12][1], 0);
				al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				xpos += 0.1;
				al_flip_display();
			}

			for (int i = 0; i < 300; i++) {
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_bitmap(box, board[9][0], board[9][1], 0);
				al_draw_bitmap(box, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[11][0], board[11][1], 0);
				al_draw_bitmap(downright, board[1][0], board[1][1], 0);
				al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
				al_draw_bitmap(redl, board[3][0], board[3][1], 0);
				al_draw_bitmap(begd, board[4][0], board[4][1], 0);
				al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
				al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
				al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
				al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
				al_draw_bitmap(upright, board[12][0], board[12][1], 0);
				al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos -= 0.1;
				xpos += 0.1;
				al_flip_display();
			}

			for (int i = 0; i < 3000; i++) {
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_bitmap(box, board[9][0], board[9][1], 0);
				al_draw_bitmap(box, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[11][0], board[11][1], 0);
				al_draw_bitmap(downright, board[1][0], board[1][1], 0);
				al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
				al_draw_bitmap(redl, board[3][0], board[3][1], 0);
				al_draw_bitmap(begd, board[4][0], board[4][1], 0);
				al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
				al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
				al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
				al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
				al_draw_bitmap(upright, board[12][0], board[12][1], 0);
				al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos -= 0.1;
				al_flip_display();
			}

			for (int i = 0; i < 300; i++) {
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_bitmap(box, board[9][0], board[9][1], 0);
				al_draw_bitmap(box, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[11][0], board[11][1], 0);
				al_draw_bitmap(downright, board[1][0], board[1][1], 0);
				al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
				al_draw_bitmap(redl, board[3][0], board[3][1], 0);
				al_draw_bitmap(begd, board[4][0], board[4][1], 0);
				al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
				al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
				al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
				al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
				al_draw_bitmap(upright, board[12][0], board[12][1], 0);
				al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				ypos -= 0.1;
				xpos += 0.1;
				al_flip_display();
			}

			for (int i = 0; i < 2100; i++) {
				al_draw_bitmap(Background, 0, 0, 0);
				al_draw_text(font, al_map_rgb(243, 197, 147), 28, 87, 0, "4");
				al_draw_textf(font, al_map_rgb(243, 197, 147), 585, 83, 0, "%i", moves);
				al_draw_bitmap(box, board[9][0], board[9][1], 0);
				al_draw_bitmap(box, board[10][0], board[10][1], 0);
				al_draw_bitmap(box, board[11][0], board[11][1], 0);
				al_draw_bitmap(downright, board[1][0], board[1][1], 0);
				al_draw_bitmap(graylr, board[2][0], board[2][1], 0);
				al_draw_bitmap(redl, board[3][0], board[3][1], 0);
				al_draw_bitmap(begd, board[4][0], board[4][1], 0);
				al_draw_bitmap(upanddown, board[5][0], board[5][1], 0);
				al_draw_bitmap(upanddown, board[7][0], board[7][1], 0);
				al_draw_bitmap(grayud, board[8][0], board[8][1], 0);
				al_draw_bitmap(upanddown, board[15][0], board[15][1], 0);
				al_draw_bitmap(upright, board[12][0], board[12][1], 0);
				al_draw_bitmap(leftup, board[13][0], board[13][1], 0);
				al_draw_filled_circle(xpos, ypos, 18, al_map_rgb(231, 231, 231));
				xpos += 0.1;
				nextlevel = 1;
				al_flip_display();
			}
			while (nextlevel) {
				al_play_sample_instance(clap1);
				al_wait_for_event(queue, &ev);
				al_draw_bitmap(gameover, 0, 0, 0);
				if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (ev.mouse.x < 410 && ev.mouse.x > 200 && ev.mouse.y < 405 && ev.mouse.y > 364) {
						
						al_play_sample_instance(playquit1);
						nextlevel = 0;
							
					}
				}
				al_flip_display();
			}
			onlevel = 0;
			levelsave = 0;
			ongamingsc = 0;
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.x < 621 && ev.mouse.x > 576 && ev.mouse.y < 456 && ev.mouse.y > 413) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_play_sample_instance(playquit1);
				al_draw_bitmap(MainMenu, 0, 0, 0);
				onlevel = 0;
				ongamingsc = 0;

			}
		}
	}
}

void destroy_all() {
	al_destroy_bitmap(Background);
	al_destroy_bitmap(MainMenu);
	al_destroy_bitmap(next1);
	al_destroy_bitmap(next2);
	al_destroy_bitmap(next3);
	al_destroy_bitmap(gameover);
	al_destroy_bitmap(begd);
	al_destroy_bitmap(begu);
	al_destroy_bitmap(leftup);
	al_destroy_bitmap(downright);
	al_destroy_bitmap(leftandright);
	al_destroy_bitmap(leftdown);
	al_destroy_bitmap(upanddown);
	al_destroy_bitmap(rightup);
	al_destroy_bitmap(upright);
	al_destroy_bitmap(graydr);
	al_destroy_bitmap(graylr);
	al_destroy_bitmap(grayud);
	al_destroy_bitmap(redd);
	al_destroy_bitmap(redl);
	al_destroy_bitmap(box);
	al_destroy_sample(theme);
	al_destroy_sample(playquit);
	al_destroy_sample(boxsound);
	al_destroy_sample(clap);
	al_destroy_sample_instance(playquit1);
	al_destroy_sample_instance(boxsound1);
	al_destroy_sample_instance(clap1);
	al_destroy_font(font);
	al_destroy_display(display);
}