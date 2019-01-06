/*
 * =====================================================================================
 *
 *       Filename:  Player.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  22/03/2014 19:49:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

Player::Player(std::string filename, s16 x, s16 y, u8 direction) : Character(filename.c_str(), x, y, direction) {
	m_type = Type::Player;

	m_speed = CHARA_SPEED;

	addAnimation(SpriteAnimationManager::spriteAnimations["Character"][DIR_DOWN]);
	addAnimation(SpriteAnimationManager::spriteAnimations["Character"][DIR_LEFT]);
	addAnimation(SpriteAnimationManager::spriteAnimations["Character"][DIR_RIGHT]);
	addAnimation(SpriteAnimationManager::spriteAnimations["Character"][DIR_UP]);

	m_inventory->addItem(0, 1);
	m_inventory->addItem(1, 1);
	m_inventory->addItem(5, 1);
	m_inventory->addItem(2, 1);
	m_inventory->addItem(3, 1);
	m_inventory->addItem(4, 1);
	m_inventory->addItem(6, 1);

	m_inventory->addWeapon(0, 1);
	m_inventory->addWeapon(1, 1);
	m_inventory->addWeapon(2, 1);
	m_inventory->addWeapon(3, 1);

	m_inventory->addArmor(0, 1);
	m_inventory->addArmor(1, 1);
	m_inventory->addArmor(2, 1);
	m_inventory->addArmor(3, 1);
	m_inventory->addArmor(4, 1);

	m_quests.push_back(QuestManager::quests[0]);
}

Player::~Player() {
	m_quests.clear();

	m_team.clear();
}

void Player::move() {
	if(m_vxCount == 0 && m_vyCount == 0) {
		m_moving = false;

		if(Keyboard::isKeyPressed(Keyboard::GameUp)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameDown)) {
				m_vy = -m_speed;
				m_moving = true;
			}
		}
		else if(Keyboard::isKeyPressed(Keyboard::GameDown)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameUp)) {
				m_vy = m_speed;
				m_moving = true;
			}
		}
		else if(Keyboard::isKeyPressed(Keyboard::GameLeft)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameRight)) {
				m_vx = -m_speed;
				m_moving = true;
			}
		}
		else if(Keyboard::isKeyPressed(Keyboard::GameRight)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameLeft)) {
				m_vx = m_speed;
				m_moving = true;
			}
		}
	}

	if(m_vx > 0) m_direction = DIR_RIGHT;
	if(m_vx < 0) m_direction = DIR_LEFT;
	if(m_vy > 0) m_direction = DIR_DOWN;
	if(m_vy < 0) m_direction = DIR_UP;

	testCollisions();

	m_vxCount += abs(m_vx);
	m_vyCount += abs(m_vy);

	m_x += m_vx;
	m_y += m_vy;

	if(m_vxCount >= 32 || m_vyCount >= 32) {
		m_vxCount = 0;
		m_vyCount = 0;

		m_moving = false;

		m_vx = 0;
		m_vy = 0;
	}
}

