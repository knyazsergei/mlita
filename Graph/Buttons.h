#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class CButtons:public sf::Drawable
{
	using ActionHandler = std::function<void()>;
public:
	CButtons(sf::Font & font, const std::string & text, const ActionHandler & hendler);
	~CButtons();
	sf::Vector2f GetSize();
	void SetSize(sf::Vector2f);
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	bool Contain(sf::Vector2f position);
	void Release();
protected:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Text m_text;
	sf::RectangleShape m_background;
	ActionHandler m_handler;
};

