/*
 * MenuView.h
 *
 *  Created on: 25/03/2013
 *      Author: tomas
 */

#ifndef MENUVIEW_H_
#define MENUVIEW_H_

#include <view/Button.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <vector>

namespace std {

class MenuView {
public:
	MenuView();

	SDL_Surface *screen;
	vector<Button*> buttons;

	void initScreen();
	void initButtons(int numButtons,const char** buttons_released,const char** buttons_pressed,const MenuEvent* buttons_events);
	void initMusic();

	virtual ~MenuView();
private:

	Mix_Music *musica;
	Mix_Chunk *sonido;
	Mix_Chunk *darknessVoice;


	void startLaugh();
	void startVoice();
};

} /* namespace std */
#endif /* MENUVIEW_H_ */
