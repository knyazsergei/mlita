#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Buttons.h"
#include <memory>
#include <fstream>
#include <functional>
#include "tinyfiledialogs.h"

class CAppMenu:public sf::Drawable
{
	using ActionHandler = std::function<void()>;
public:
	CAppMenu();
	~CAppMenu();

	void EventHendler(sf::Event & event);
	void AddButton(const std::string & text, const ActionHandler & hendler);
	void SetState(const std::string & text);
protected:
	void draw(sf::RenderTarget &target, sf::RenderStates states)const override;
private:
	void Alignment();
	sf::Font m_font;
	std::list<CButtons> m_buttons;
	sf::Text m_clarification;
};

