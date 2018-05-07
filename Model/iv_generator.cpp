#include "iv_generator.hpp"

#include <chrono>		// system_clock
#include <random>		// default_random_engine, uniform_int_distribution
#include <cctype>		// isspace()
#include <string>		// string, stoi()
#include <algorithm>	// remove_if()

namespace Ivg
{
namespace Random
{

using Generator = std::default_random_engine;
using Distribution = std::uniform_int_distribution<int>;

} // Random

Generator::Generator()
	: m_nCount(0)
	, m_max(0)
	, m_filter(-1)
	, m_filterSign(0)
	, m_nums(0)
	, m_errorStatus()
{
}

bool Generator::load(const char* str)
{
	std::string nCount, max, filter;
	enum {
		Count, Max, Filter
	} parsingState = Count;

	for (const char* c = str; *c != '\0'; ++c) {
		if (isspace(*c)) {
			continue;
		}

		if (*c == 'd') {
			parsingState = Max;
			continue;
		} else if (*c == ',') {
			parsingState = Filter;
			continue;
		}

		switch (parsingState) {
			case Count:
				nCount += *c;
				continue;
			case Max:
				max += *c;
				continue;
			case Filter:
				filter += *c;
				continue;
		}
	}

	try {
		m_nCount = std::stoi(nCount);
		m_max = std::stoi(max);
		if (!filter.empty()) {
			char lastChar = filter.at(filter.size() - 1);
			if (!isdigit(lastChar)) {
				filter.pop_back();
				m_filterSign = lastChar;
				m_filter = std::stoi(filter);
			} else {
				m_filterSign = '+';
				m_filter = std::stoi(filter);
			}
		}
	} catch (std::exception& ex) {
		m_errorStatus = ex.what();
		return false;
	}

	return generateNums();
}

void Generator::clear()
{
	m_nums.clear();
}

bool Generator::generateNums()
{
	// Initialize random generator
	long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	Random::Distribution distrib(1, m_max);
	Random::Generator gen(static_cast<unsigned>(seed));

	// Generate random numbers
	for (int i = 0; i < m_nCount; ++i) {
		m_nums.emplace_back(distrib(gen));
	}

	// Apply filter if required
	if (m_filter != -1) {
		if (m_filterSign == '-') {
			m_nums.erase(std::remove_if(m_nums.begin(), m_nums.end(), [&](int i) {
				return i > m_filter;
			}), m_nums.end());
		} else {
			m_nums.erase(std::remove_if(m_nums.begin(), m_nums.end(), [&](int i) {
				return i < m_filter;
			}), m_nums.end());
		}
	}
	return true;
}

} // Ivg
