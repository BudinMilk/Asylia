/*
 * =====================================================================================
 *
 *       Filename:  ActorChoiceWindow.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2014 15:54:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef ACTORCHOICEWINDOW_HPP_
#define ACTORCHOICEWINDOW_HPP_

class ActorChoiceWindow : public SelectableWindow {
	public:
		ActorChoiceWindow(s16 x, s16 y, u16 width, u16 height);
		~ActorChoiceWindow();
		
		void update();
		
		void drawActor(u16 pos);
		
		void draw();
};

#endif // ACTORCHOICEWINDOW_HPP_
