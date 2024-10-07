#ifndef SETTINGS_H
#define SETTINGS_H

#include <ostream>
#include <istream>

// A structure containing all game settings
struct Settings {
	bool music_muted, sound_muted;
};

constexpr Settings DEFAULT_SETTINGS = {
	.music_muted = false,
	.sound_muted = false
};

inline std::istream& operator>>(std::istream& is, Settings& s) { return is >> s.music_muted >> s.sound_muted; }
inline std::ostream& operator<<(std::ostream& os, const Settings& s) { return os << s.music_muted << ' ' << s.sound_muted << '\n'; }

#endif