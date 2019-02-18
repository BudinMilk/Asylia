/*
 * =====================================================================================
 *
 *       Filename:  Interface.hpp
 *
 *    Description:
 *
 *        Created:  22/03/2014 00:35:05
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include "Font.hpp"
#include "Image.hpp"

class Interface {
	public:
		static void init();

		static Font *defaultFont;
		static Image *interface;
};

#endif // INTERFACE_HPP_
