#include "stdafx.h"
#include "Buttons.h"


CButtons::CButtons(sf::Font & font, const std::string & text, const CButtons::ActionHandler & hendler):
	m_handler(hendler)
{
	m_text.setFont(font);
	m_text.setString(text);
	m_text.setColor({ 0, 0, 0 });

	m_background.setFillColor({ 230, 220, 220 });
	m_background.setSize({ 200, 40 });
}


CButtons::~CButtons()
{
}

sf::Vector2f CButtons::GetSize()
{
	return m_background.getSize();
}

void CButtons::SetSize(sf::Vector2f size)
{
	m_background.setSize(size);
}

sf::Vector2f CButtons::GetPosition()
{
	return m_background.getPosition();
}

void CButtons::SetPosition(sf::Vector2f position)
{
	std::cout << m_background.getPosition().x << " " << m_background.getPosition().y << std::endl;
	m_background.setPosition(position);
	m_text.setPosition(position + m_background.getSize() * 0.5f + -sf::Vector2f({ m_text.getLocalBounds().width, m_text.getLocalBounds().height }));
}

bool CButtons::Contain(sf::Vector2f position)
{
	return m_background.getGlobalBounds().contains(position);
}

void CButtons::Release()
{
	m_handler();
}

void CButtons::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
	target.draw(m_text, states);
}