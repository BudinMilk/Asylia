/*
 * =====================================================================================
 *
 *       Filename:  GameWindow.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/03/2014 22:06:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef GAMEWINDOW_HPP_
#define GAMEWINDOW_HPP_

class GameWindow {
	public:
		GameWindow(const char *caption);
		~GameWindow();
		
		void clear();
		
		void update();
		
		void updateViewportPosition(s16 x, s16 y);
		
		void centerViewportWithObject(s16 x, s16 y, u16 w, u16 h);
		
		void setRendererColor(Color color);
		
		void drawRect(s16 x, s16 y, u16 w, u16 h, Color c);
		
		void drawFillRect(s16 x, s16 y, u16 w, u16 h, Color c);
		
		SDL_Renderer *renderer() const { return m_renderer; }
		
		u16 width() const { return m_width; }
		u16 height() const { return m_height; }
		
		s16 viewportX() const { return m_viewportX; }
		s16 viewportY() const { return m_viewportY; }
		
		u16 viewportW() const { return m_viewportW; }
		u16 viewportH() const { return m_viewportH; }
		
		static GameWindow *main;
		
	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		
		u16 m_width;
		u16 m_height;
		
		s16 m_viewportX;
		s16 m_viewportY;
		
		u16 m_viewportW;
		u16 m_viewportH;
};

#endif // GAMEWINDOW_HPP_