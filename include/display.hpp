#ifndef DISPLAY_HPP
#define DISPLAY_HPP 
#include <SDL2/SDL.h>
#include <unordered_map>
#include <cinttypes>
#include "keyboard.hpp" 


class Display {
public:
	Display (unsigned w = 640, unsigned h = 320) {
		m_w = w;
		m_h = h;
		init();	
	};
	~Display () { 
#ifndef HIDE_DISPLAY
		//free(m_window);
		//free(m_renderer);
#endif
	};

protected:
	void cls();
	void close();
	void renderAll(uint8_t (&array2D)[32][64]); // must have the same return type was screendump
	uint8_t m_display[32][64] = {0};

private:
	unsigned m_w;
	unsigned m_h;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	void init();
	void drawPixelXY(unsigned x, unsigned y, unsigned colour);
};

#endif /* DISPLAY_HPP */
