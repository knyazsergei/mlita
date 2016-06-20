#include "stdafx.h"
#include "Visualization.h"


CVisualization::CVisualization()
{
	auto width = 800;
	auto height = 600;
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Visualization!");
	
	m_view = sf::View(sf::Vector2f(), sf::Vector2f(float(width), float(height)));
	m_sprite.setPosition(sf::Vector2f(float(width), float(height)) * 0.5f);
}

bool CVisualization::IsOpen()
{
	return m_window->isOpen();
}

void CVisualization::Update()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			m_pressed = true;
			m_shift = sf::Mouse::getPosition();
		}
		else if (event.type == sf::Event::MouseMoved && m_pressed)
		{
			m_dragging = true;
			m_shift -= sf::Mouse::getPosition();
			m_sprite.setPosition(m_sprite.getPosition() - sf::Vector2f(float(m_shift.x),float( m_shift.y)));
			m_shift = sf::Mouse::getPosition();
		}
		else if (event.type == sf::Event::MouseButtonReleased &&
			(m_dragging))
		{
			m_pressed = false;
			m_dragging = false;
		}
		else
		{
			m_appMenu.EventHendler(event);
			m_pressed = false;
			m_dragging = false;
		}
	}
	sf::Image img;
	if (!img.loadFromFile("g.png"))
	{	
		std::cout << "failed image loading\n";
		m_imageLoaded = false;
	}
	else
	{
		m_imageLoaded = true;
		
		m_texture.loadFromImage(img);
		m_sprite = sf::Sprite();
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(sf::Vector2f(m_window->getSize().x, m_window->getSize().y)  * 0.5f);
		m_sprite.setOrigin(sf::Vector2f({ m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height }) * 0.5f);
		m_texture.loadFromFile("g.png");
	}
	m_window->clear({ 255, 255, 255 });
	DrawObjects();
	m_window->display();
}

void CVisualization::SetLoad(const ActionHandler & hendler)
{
	m_appMenu.AddButton("open", hendler);
}

void CVisualization::SetSave(const ActionHandler & hendler)
{
	m_appMenu.AddButton("save", hendler);
}

void CVisualization::SetState(const std::string & text)
{
	m_appMenu.SetState(text);
}

void CVisualization::DrawObjects()
{
	if (m_imageLoaded)
		m_window->draw(m_sprite);
	m_window->draw(m_appMenu);
}
