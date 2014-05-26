/*
 * =====================================================================================
 *
 *       Filename:  Animation.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24/05/2014 15:49:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

class Battler;

class Animation : public Sprite {
	public:
		Animation(const char *filename, u16 frameWidth = 192, u16 frameHeight = 192);
		~Animation();
		
		void play(Battler *target);
};

#endif // ANIMATION_HPP_
