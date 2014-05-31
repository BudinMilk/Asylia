/*
 * =====================================================================================
 *
 *       Filename:  Event.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/03/2014 23:50:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef EVENT_HPP_
#define EVENT_HPP_

class Event : public Character {
	public:
		Event(std::string name, std::string appearance, u16 x, u16 y, u8 anim, bool solid = false);
		~Event();
		
		void init();
		
		void update();
		void render();
		
		void action();
		void collisionAction();
		
		std::string name() const { return m_name; }
		
	private:
		std::string m_folder;
		std::string m_name;
};

#endif // EVENT_HPP_