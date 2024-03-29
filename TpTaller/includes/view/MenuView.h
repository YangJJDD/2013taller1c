/*
 * MenuView.h
 *
 *  Created on: 25/03/2013
 *      Author: tomas
 */

#ifndef MENUVIEW_H_
#define MENUVIEW_H_

#include <view/Button.h>
#include <view/configuration/GameConfiguration.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <vector>

using namespace std;

class MenuView {
public:
	MenuView(GameConfiguration* configuration);

	SDL_Surface *screen;
	vector<Button*> buttons;

	void initScreen();
	void initButtons(int numButtons, const char** buttons_released,
			const char** buttons_pressed, const char** buttons_hovered, const MenuEvent* buttons_events);
	void initMusic();

	void close();

	virtual ~MenuView();
private:

	Mix_Music *musica;
	Mix_Chunk *darknessVoice;
	GameConfiguration* gameConfig;
	void initImages();
	bool audioOpen;
};

#endif /* MENUVIEW_H_ */
