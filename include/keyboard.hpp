#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP 
#include <unordered_map>
#include <SDL2/SDL.h> 
#include <array>
#include <cinttypes>
#include <any>
#include <vector>
#include <algorithm> // find_if
#include <iostream> // TODO: remove
#include "ini_reader.hpp" 


/**
 * @brief Copies keys-value pairs to new a map only if key starts from a certain string
 *
 * @param map An input map to select entries from
 * @param mapNew An output map where filtered entries from input will be stored to
 * @param prefix If they key of each entry of input starts from `prefix`, select it and store it to mapNew
 */
static void copyOnlyForPrefix(
		const std::unordered_map<std::string, std::any>& map,
		std::unordered_map<std::string, std::any>& mapNew,
		std::string prefix)
{
	for (const auto& keyval: map) {
		if (keyval.first.substr(0, prefix.length()) == prefix)
			mapNew.insert({keyval.first, keyval.second});
	}
}


class Keyboard: public inireader::IniReader {
public:
	Keyboard (): IniReader() {
		// from ini file, select entries that start with s_key, e.g. s_key_5 = w
		decltype(m_iniSettings) iniSettingsCpy;
		copyOnlyForPrefix(m_iniSettings, iniSettingsCpy, "s_key");
		bool success;

		for (auto const& k2s: m_keyboard2sdl) {
			success = false;
			std::string key = k2s.first; // keyboard key
			// check if m_iniSettings *values* contain key above
			for (const auto& iniPair: iniSettingsCpy){
				if (std::any_cast<std::string> (iniPair.second).compare(key) == 0) {
					success = true;
					// rhs of ini entry - i.e. chip8 (hex) key
					m_ch8key = std::stoi(iniPair.first.substr(iniPair.first.size() - 1), 0, 16);
					break;
				}
			}
			if (success) {
				// "s" -> SDLK_s -> 0xb
				std::string slast(1, k2s.first.back());
				m_keyQwerty2Chip8[m_keyboard2sdl[slast]] = m_ch8key;
			}
		}
		m_keyQwerty2Chip8[SDLK_ESCAPE] = 0x10;
	};
	~Keyboard () {};

protected:
	uint8_t getKeyPress();
	unsigned m_ch8key;
	std::unordered_map<unsigned, unsigned> m_keyQwerty2Chip8;
	std::array<uint8_t, 16> m_keypresses {};
private:
	std::unordered_map<std::string, unsigned> m_keyboard2sdl = 
	{
		{"a", SDLK_a}, {"b", SDLK_b}, {"c", SDLK_c}, {"d", SDLK_d}, {"e", SDLK_e}, {"f", SDLK_f},
		{"g", SDLK_g}, {"h", SDLK_h}, {"i", SDLK_i}, {"j", SDLK_j}, {"k", SDLK_k}, {"l", SDLK_l},
		{"m", SDLK_m}, {"n", SDLK_n}, {"o", SDLK_o}, {"p", SDLK_p}, {"q", SDLK_q}, {"r", SDLK_r},
		{"s", SDLK_s}, {"t", SDLK_t}, {"u", SDLK_u}, {"v", SDLK_v}, {"w", SDLK_w}, {"x", SDLK_x},
		{"y", SDLK_y}, {"z", SDLK_z},
		{"0", SDLK_0}, {"1", SDLK_1}, {"2", SDLK_2}, {"3", SDLK_3}, {"4", SDLK_4}, {"5", SDLK_5},
		{"6", SDLK_6}, {"7", SDLK_7}, {"8", SDLK_8}, {"9", SDLK_9}
	};
};
#endif /* KEYBOARD_HPP */
