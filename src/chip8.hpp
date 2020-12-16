#ifndef CHIP8_HPP
#define CHIP8_HPP 

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm> // fill()
#include <cinttypes>
#include <bits/stdc++.h>
#include <random>
#include <chrono>
#include <thread>
#include <random>
#include "display.hpp"
#include "keyboard.hpp"


typedef struct bitfields_t {
	/* see http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.0 */
	unsigned type;
	unsigned n;
	unsigned y;
	unsigned x;
	unsigned kk;
	unsigned nnn;
} bitfields;


class Chip8: public Display, public Keyboard {
public:
	Chip8 () {
		for (auto& m: m_mem)
			m = 0xff; // 0xff indicates free space
		initFont();
	};
	~Chip8 () {};
	void loadRom(const char* filename, unsigned offset = 0x200);
	void run(unsigned startingOffset = 0x200);

private:
	/* define the architecture */
	std::array<uint8_t, 0x1000> m_mem {};		// Whole memory
	std::array<uint8_t, 16> m_V {};			// V (general) registers
	uint8_t m_delayTimer, m_soundTimer;
	uint16_t m_SP = 0;							// Stack pointer
	uint16_t m_PC = 0x200;						// Program counter
	uint16_t m_I = 0;							// Index register
	uint16_t m_opcode;							// current opcode
	bitfields m_bitfields;					// opcode bitfields
	std::array<uint16_t, 12>m_stack;						// stack
	std::vector<uint8_t> m_fontset;				// font sprites
	void fetch();
	void decode();
	void exec();
	void initFont(unsigned offset = 0x50);
	void init();
};

#endif /* CHIP8_HPP */
