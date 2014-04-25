/*
 * =====================================================================================
 *
 *       Filename:  BattleActivity.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/04/2014 19:23:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

BattleActivity::BattleActivity() {
	m_type = Type::BattleAct;
	
	m_battle.addActor(new Actor());
	m_battle.addActor(new Actor());
	m_battle.addActor(new Actor());
	m_battle.addActor(new Actor());
	
	m_battle.addEnemy(new Enemy());
	
	m_currentActor = NULL;
	
	m_mode = Mode::Choice;
	
	Sound::Music::play(Sound::Music::battle, -1);
}

BattleActivity::~BattleActivity() {
}

void BattleActivity::update() {
	if(m_mode == Mode::Choice) {
		m_battleChoicewin.update();
	}
	
	if(Keyboard::isKeyPressedOnce(Keyboard::GameBack)) {
		Sound::Effect::play(Sound::Effect::back);
		ActivityManager::pop();
		Sound::Music::halt();
		Sound::Music::play(Sound::Music::theme, -1);
	}
}

void BattleActivity::render() {
	m_battle.renderBattleback();
	
	m_actorStatswin.draw(m_battle.enemies(), m_battle.actors());
	
	if(m_mode == Mode::Choice) {
		m_battleChoicewin.draw();
	}
}

