#include "stdafx.h"
#include "AppMenu.h"

CAppMenu::CAppMenu()
{
	m_font.loadFromFile("Fonts/RistrettoPro-Regular.otf");
	m_clarification.setFont(m_font);
	m_clarification.setColor({ 0, 0, 0 });
	m_clarification.setCharacterSize(16);
	m_clarification.setString("");
}


CAppMenu::~CAppMenu()
{
}

void CAppMenu::EventHendler(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		auto position = sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y));
		for (auto & button : m_buttons)
		{
			if (button.Contain(position))
			{
				button.Release();
			}
		}

	}
}

void CAppMenu::AddButton(const std::string & text, const ActionHandler & hendler)
{
	m_buttons.push_back(CButtons(m_font, text, hendler));
	Alignment();
}

void CAppMenu::SetState(const std::string & text)
{
	m_clarification.setString(text);
}

void CAppMenu::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	for (auto & button : m_buttons)
	{
		target.draw(button, states);
	}
	target.draw(m_clarification);
}

void CAppMenu::Alignment()
{
	sf::Vector2f position(0, 0);
	for (auto & button : m_buttons)
	{
		button.SetPosition(position);
		position += sf::Vector2f(button.GetSize().x, 0);
	}
	m_clarification.setPosition({ 0.f, 10.f + m_buttons.front().GetSize().y });
}
