#ifndef DISPLAY_HPP
#include <SDL2/SDL.h>


class Display {
public:
	Display (unsigned w = 320, unsigned h = 640) {
		m_w = w;
		m_h = h;
		init();	
	};
	~Display () { };
	void drawBlock(unsigned x, unsigned y);
	void reset();
	void close();

private:
	unsigned m_w;
	unsigned m_h;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	void init();
};

#define DISPLAY_HPP 
#endif /* DISPLAY_HPP */
