#include "Header.h"
#include "main.h"



int main() {
	//variable
	bool done = false, redraw = false, finish = false;
	enum KEYS {UP,DOWN,LEFT,RIGHT,SPACE};
	int fps = 60, count = 0;
	bool keys[5] = { false, false, false, false,false };



	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT ev;

	//class variable
	SpaceShip MyShip(PLAYER);
	Bullet Bullets[5];
	Meteor Meteors[10];

	if (!al_init())
		return -1;
	display = al_create_display(width, height);
	if (!display) 
		return -1;
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//initiate addons
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font12 = al_load_font("arial.ttf",12,0);
	
	al_install_keyboard();
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / fps);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_start_timer(timer);
	srand(time(NULL));
	while (!done) {
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				for (count = 0; keys[SPACE] == true && count < sizeof(Bullets) / sizeof(Bullet);count++) {
					if (!Bullets[count].bullet_live()) {
						Bullets[count].init_bullet(MyShip.get_position_x(), MyShip.get_position_y() + MyShip.get_y_bound());
						Bullets[count].fire_bullet();
						break;
					}
				}
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				for (int i = 0; i <sizeof(Bullets) / sizeof(Bullet); i++) {
					if (Bullets[i].bullet_live())
						Bullets[i].update_bullet();
				}
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (keys[UP])
				MyShip.move_up();
			if (keys[DOWN])
				MyShip.move_down();
			if (keys[LEFT])
				MyShip.move_left();
			if (keys[RIGHT])
				MyShip.move_right();
			redraw = true;
		}
		if (rand() % 10 == 0) {
			for (int l = 0; l < sizeof(Meteors) / sizeof(Meteor); l++) {
				if (!Meteors[l].is_meteor_alive()) {
					Meteors[l].init_Meteor();
					break;
				}
			}
		}
		if(!finish)
			collision_detection(Bullets, sizeof(Bullets) / sizeof(Bullet), Meteors, sizeof(Meteors) / sizeof(Meteor), &MyShip);

		if (redraw && al_is_event_queue_empty(event_queue) && !finish) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for(int l = 0; l < sizeof(Meteors)/sizeof(Meteor);l++){
				Meteors[l].update_meteor();
				if (Meteors[l].is_meteor_alive()) {
					Meteors[l].draw_meteor();
				}
			}
			al_draw_textf(font12, al_map_rgb(255, 255, 255), width - 30, 20, ALLEGRO_ALIGN_RIGHT, "score: %d", MyShip.get_score());
			al_draw_textf(font12, al_map_rgb(255, 255, 255), width - 30, 35, ALLEGRO_ALIGN_RIGHT, "life: %d", MyShip.get_life());
			MyShip.draw_space_ship();
			for (int i = 0; i <sizeof(Bullets)/sizeof(Bullet); i++) {
				if(Bullets[i].bullet_live())
				Bullets[i].draw_bullet();
			}
			al_flip_display();
			redraw = false;
		}
		if (MyShip.get_life() == 0) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_textf(font12, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "Final Score: %d", MyShip.get_score());
			al_flip_display();
			finish = true;
		}

	}//while(!done)

	//free memory
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}

void collision_detection(Bullet *b, int num_of_b, Meteor *m, int num_of_m,SpaceShip *s) {
	for (int i = 0; i < num_of_b; i++) 
		for (int j = 0; j < num_of_m; j++) 
			if (b[i].bullet_live() && m[j].is_meteor_alive())
				if (b[i].get_position_y() <= m[j].get_position_y() + m[j].get_bound_y() / 2 && b[i].get_position_y() >= m[j].get_position_x() - m[j].get_bound_x() / 2)
					if (b[i].get_position_x() >= m[j].get_position_x() - m[j].get_bound_x() / 2 && b[i].get_position_x() <= m[j].get_position_x() + m[j].get_bound_x() / 2) {
						b[i].dead();
						m[j].dead();
						s->add_score(10);
						i++;
					}
				
	for (int j = 0; j < num_of_m; j++) {
		if (m[j].is_meteor_alive()) {
			if (m[j].get_position_x() - m[j].get_bound_x() / 2 < s->get_position_x() + s->get_x_bound() && m[j].get_position_x() + m[j].get_bound_x() / 2 > s->get_position_x() - s->get_x_bound()) {
				if (m[j].get_position_y() + m[j].get_bound_y() / 2 > s->get_position_y() + s->get_y_bound() && m[j].get_position_y() - m[j].get_bound_y() / 2 < s->get_position_y()) {
					//s->reduce_life();
					m[j].dead();
				}
			}
		}
	}
}