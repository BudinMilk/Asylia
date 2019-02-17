/*
 * =====================================================================================
 *
 *       Filename:  EquipState.cpp
 *
 *    Description:
 *
 *        Created:  10/04/2014 19:51:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/audio/AudioPlayer.hpp>

#include "ApplicationStateStack.hpp"
#include "CharacterManager.hpp"
#include "EquipState.hpp"
#include "GameWindow.hpp"
#include "Keyboard.hpp"
#include "MenuState.hpp"

EquipState::EquipState(u8 actorPos, ApplicationState *parent) : ApplicationState(parent) {
	m_itemMode = false;

	m_actor = CharacterManager::getInstance().getPlayer()->getTeamMember(actorPos);

	m_equipment = CharacterManager::getInstance().getPlayer()->getTeamMember(actorPos)->equipment();

	m_statswin.reset(new EquipStatsWindow(m_actor));
	m_choicewin.reset(new EquipChoiceWindow(m_equipment));

	m_itemwin.reset(new ItemWindow(150, 52 + (GameWindow::main->height() - 52) / 2, GameWindow::main->width() - 150, (GameWindow::main->height() - 52) / 2, CharacterManager::getInstance().getPlayer()->inventory(), 150, 0));
	m_itemwin->changeSet(0, 0, m_equipment);
}

void EquipState::update() {
	// FIXME: SLOW?? //
	if(m_choicewin->pos() == 0) {
		m_itemwin->changeSet(m_choicewin->pos(), m_choicewin->pos(), m_equipment);
	} else {
		m_itemwin->changeSet(m_choicewin->pos(), m_choicewin->pos() - 1, m_equipment);
	}

	if(m_itemMode) m_itemwin->update();
	else m_choicewin->update();

	if(Keyboard::isKeyPressedOnce(Keyboard::GameAttack)) {
		if(m_itemMode) {
			gk::AudioPlayer::playSound("sound-confirm");

			Item *currentItem = m_itemwin->currentItem();
			if(m_choicewin->pos() == 0) {
				if(currentItem) m_equipment->equipWeapon((Weapon*)currentItem);
				else m_equipment->unequipWeapon();
			} else {
				if(currentItem) m_equipment->equipArmor((Armor*)currentItem);
				else m_equipment->unequipArmor(m_choicewin->pos() - 1);
			}

			m_itemMode = false;
			m_itemwin->pos(0);
			m_itemwin->update();
		}
		else if(m_itemwin->itemMax() == 0) {
			gk::AudioPlayer::playSound("sound-blocked");
		} else {
			gk::AudioPlayer::playSound("sound-confirm");

			m_itemMode = true;
		}
	}

	if(Keyboard::isKeyPressedOnce(Keyboard::GameBack)) {
		gk::AudioPlayer::playSound("sound-back");
		if(m_itemMode) {
			m_itemMode = false;
			m_itemwin->pos(0);
			m_itemwin->update();
		} else {
			ApplicationStateStack::getInstance().pop();
			if(ApplicationStateStack::getInstance().top().type() == ApplicationState::Type::Menu)
				((MenuState&)ApplicationStateStack::getInstance().top()).actorChoiceModeOn();
		}
	}
}

void EquipState::render() {
	if (m_parent)
		m_parent->render();

	if(m_itemMode) m_statswin->draw(m_itemwin->currentItem());
	else m_statswin->draw();
	m_choicewin->draw(!m_itemMode);
	m_itemwin->draw(m_itemMode, m_itemMode);
}

