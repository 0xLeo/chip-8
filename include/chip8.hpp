#ifndef CHIP8_HPP
#define CHIP8_HPP 

#include <iostream>
#include <fstream>
#include <memory>
#include <array>
#include <algorithm> // fill()
#include <cinttypes> // uint8_t, uint16_t
#include <bits/stdc++.h>
#include "display.hpp"
#include "keyboard.hpp"
#include "ini_reader.hpp"
#include "bitfields.hpp"


enum {
	SPEED_NORMAL,								// Opcodes per sec configured by user 
	SPEED_OVERCLOCK								// As fast as host computer allows
};


class Chip8: public Display, public Keyboard, public IniReader {
public:
	// the constructor must call the init(...) method
	Chip8 () {
		init();
	};
	Chip8 (std::string fnameIni) :
		IniReader(fnameIni) {
			// initReader constructor saves values in m_iniSettings
			int overclock = m_iniSettings["overclock"];
			int instrPerSec = m_iniSettings["instructions_per_sec"];
			int maxIter = m_iniSettings["stop_after_iter"];
			int mute = m_iniSettings["mute"];
			// use m_settings member here	
			init(overclock, instrPerSec, maxIter, mute);
	};
	~Chip8 () {};
	void loadRom(const char* filename, unsigned offset = 0x200);
	void run(unsigned startingOffset = 0x200);

private:
	/* define the architecture */
	std::array<uint8_t, 0x1000> m_mem {};		// Whole memory
	std::array<uint8_t, 16> m_V {};				// V (general) registers
	uint8_t m_delayTimer, m_soundTimer;			// timers
	uint16_t m_SP;								// Stack pointer
	uint16_t m_PC;								// Program counter
	uint16_t m_I;								// Index register
	uint16_t m_opcode;							// current opcode
	unsigned m_clockSpeed;						// clock speed (enum); normal or overclocked
	bitfields m_bitfields;						// opcode bitfields
	std::array<uint16_t, 12>m_stack;			// stack
	std::vector<uint8_t> m_fontset;				// font sprites
	uint8_t rand();								// Chip8 has a random number generator 

	inline void fetch();						// handles current instruction
	inline void decode();						// handles current instruction
	void exec();								// handles current instruction

	// config options corresponding to .init file fields
	bool m_overclock;
	int m_instrPerSec;
	int m_maxIter;
	bool m_mute;

	/**
	 * @brief resets the machine and sets the .init config options
	 *
	 * @param overclock If != 0, the host runs the loaded rom as fast as possible, also on mute
	 * @param instrPerSec How many instructions (2-byte codes) to run per sec
	 * @param maxIter How many instructions to run before terminating. If < 0, infinite
	 * @param mute If != 0, don't play beeping sound
	 */
	void init(const int& overclock = 0,
			const int& instrPerSec = 400,
			const int& maxIter = -1,
			const int& mute = 0);

};

#endif /* CHIP8_HPP */
