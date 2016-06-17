#pragma once
#include <SFML/graphics.hpp>
#include <memory>
#include <list>
#include "AppMenu.h"

class CVisualization
{
	using ActionHandler = std::function<void()>;
public:
	CVisualization();
	~CVisualization()=default;

	bool IsOpen();
	void Update();

	void SetLoad(const ActionHandler & hendler);
	void SetSave(const ActionHandler & hendler);
	void SetState(const std::string & text);
private:
	void DrawObjects();
	std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<std::pair<bool, sf::CircleShape>> m_nodes;
	std::map<unsigned, std::pair<bool, sf::Vertex[2]>> m_edges;

	CAppMenu m_appMenu;
	sf::Texture m_texture;
	sf::RectangleShape m_sprite;
	bool m_imageLoaded = false;

	sf::View m_view;

	bool m_pressed = false;
	bool m_dragging;
	sf::Vector2i m_shift;
};

