/*
 * =====================================================================================
 *
 *       Filename:  BattleAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/05/2014 14:02:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

BattleAction::BattleAction(Battler *actor, Battler *receiver, Item *item) {
	m_actor = actor;
	m_receiver = receiver;
	
	m_item = item;
	
	m_damages = -1;
	
	m_variance = 0.20;
	
	m_animation = new Animation("graphics/animations/Attack01.png");
	m_animationAtEnd = false;
}

BattleAction::~BattleAction() {
	delete m_animation;
}

void BattleAction::process() {
	if(m_actor->hp() == 0) return;
	if(!m_receiver) return;
	
	if(m_item->type() == Item::Type::Skill) {
		m_damages = (m_actor->totalAtk() + ((Skill*)(m_item))->atk()) * 4 - m_receiver->def() * 2;
		if(m_damages <= 0) m_damages = 1;
		m_damages += (rand() % (int)ceil(m_variance * m_damages * 2)) - m_variance * m_damages;
		if(m_damages <= 0) m_damages = 0;
		m_receiver->hurt(m_damages);
	}
}

/*s16 dmgx = -1;
s16 dmgy = -1;
s8 dmgvx = 0;
s8 dmgvy = 0;
u16 dmgmvcount = 0;*/

u16 dmgy = 0;
s16 dmgvy = 0;
u16 dmgmvcount = 0;
bool BattleAction::drawDamages() {
	if(m_actor->hp() == 0) return true;
	if(!m_receiver) return true;
	
	if(m_animation->animationAtEnd(0)) {
		m_animation->stopAnimation(0);
		m_animation->resetAnimation(0);
		
		m_animationAtEnd = true;
		
		dmgy = m_receiver->image()->posRect().y + m_receiver->image()->height() / 2 - 8;
	} else {
		if(!m_animationAtEnd) m_animation->play(m_receiver);
	}
	
	if(m_animationAtEnd) {
		if(dmgmvcount < 15) {
			dmgvy = -2;
		}
		else if(dmgmvcount < 60) {
			dmgvy = 2;
		} else {
			m_animationAtEnd = false;
			dmgy = 0;
			dmgvy = 0;
			dmgmvcount = 0;
			return true;
		}
		
		dmgy += dmgvy;
		
		dmgmvcount += abs(dmgvy);
		
		u16 dmgx = m_receiver->image()->posRect().x + m_receiver->image()->posRect().w / 2 - log10(m_damages + 10) * 9 / 2;
		Interface::defaultFont->printDamages(m_damages, dmgx, dmgy, Color::red);
	}
		
	return false;
	
	/*if(dmgx == -1 && dmgy == -1) {
		dmgx = m_receiver->image()->posRect().x + m_receiver->image()->posRect().w / 2 - 12;
		dmgy = m_receiver->image()->posRect().y + m_receiver->image()->posRect().h / 2 - 12;
		
		dmgvx = rand() % 2 * 2 - 1;
		dmgvy = rand() % 2 * 2 - 1;
		
		dmgmvcount = 0;
	}
	
	if(m_item->type() == Item::Type::Skill) {
		Interface::defaultFont->printDamages(m_damages, dmgx, dmgy, Color::red);
		
		dmgx += dmgvx;
		dmgy += dmgvy;
		
		dmgmvcount++;
	}
	
	if(dmgmvcount > 32) {
		dmgx = -1;
		dmgy = -1;
		return true;
	} else {
		return false;
	}*/
	
}

