/*
 * =====================================================================================
 *
 *       Filename:  CommandWindow.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/03/2014 13:15:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

CommandWindow::CommandWindow(s16 x, s16 y, u16 width, bool horizontal, bool centered) : SelectableWindow(x, y, width, (horizontal)?(64):(32)) {
	m_horizontal = horizontal;
	m_centered = centered;
	
	m_itemMax = 0;
	
	m_pos = 0;
}

CommandWindow::CommandWindow(u16 width) : SelectableWindow(0, 0, width, 32) {
	m_horizontal = false;
	m_centered = false;
	
	m_itemMax = 0;
	
	m_pos = 0;
}

CommandWindow::~CommandWindow() {
}

void CommandWindow::drawItem(u8 pos) {
	Interface::defaultFont->printScaled(_t(m_commands[pos].first).c_str(), m_x + 22, m_y + 22 + 32 * pos, m_width - 40 - 5, 32, FONT_LARGE, (!m_commands[pos].second)?(Color::white):(Color::disabled));
}

void CommandWindow::drawHorizontalCenteredItem(u8 pos) {
	u16 x, y, width;
	
	width = m_width / m_columnMax - 32;
	x = pos % m_columnMax * (width + 32) + 16;
	y = pos / m_columnMax * 32 + 16;
	
	Interface::defaultFont->printCentered(m_commands[pos].first.c_str(), m_x + x, m_y + y, width, 32, FONT_LARGE, (!m_commands[pos].second)?(Color::white):(Color::disabled));
}

void CommandWindow::draw(bool cursor) {
	SelectableWindow::draw(cursor);
	
	for(u8 i = 0 ; i < m_itemMax ; i++) {
		if(!m_horizontal && !m_centered) {
			drawItem(i);
		} else {
			drawHorizontalCenteredItem(i);
		}
	}
}

