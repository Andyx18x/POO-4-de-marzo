#include <SFML/Graphics.hpp>
#include <string>

// Version: 2024-01-03

class InputText : public sf::Text {
	
public:
	InputText() = default;
	InputText(const sf::Font &font, int size=30, sf::Color color=sf::Color::Black) {
		setFont(font);
		setCharacterSize(size);
		setFillColor(color);
	}
	
	bool processEvent(const sf::Event &event) {
		if (!m_editable) return false;
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode=='\b') {
				if (m_value.size()) m_value.erase(m_value.size()-1,1);
			} else if (event.text.unicode>=32 && event.text.unicode<128) {
				if (m_max_len==0 || m_value.size()<m_max_len ) 
					if (!m_single_word || event.text.unicode!=' ')
						m_value += static_cast<char>(event.text.unicode);
			}
			return true;
		}
		return false;
	}
	void setMaxChars(unsigned int max_len) { m_max_len = max_len; }
	void update() {
		if (m_editable && int(m_clock.getElapsedTime().asSeconds()*3)%2)
			setString(m_value+"|");
		else 
			setString(m_value);
	}
	void setEditable(bool m_value) { m_editable=m_value; }
	void setSingleWord(bool m_value) { m_single_word=m_value; }
	std::string getValue() { return m_value; }
	void reset() { m_value.clear(); }
	
private:
		sf::Clock m_clock;
		std::string m_value;
		unsigned int m_max_len = 0;
		bool m_editable = true;
		bool m_single_word = false;
};
