/*!
	@file
	@author		Albert Semenov
	@date		12/2008
	@module
*/
#ifndef __MYGUI_VERSION_H__
#define __MYGUI_VERSION_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Types.h"
#include "MyGUI_Utility.h"

namespace MyGUI
{

	struct MYGUI_EXPORT Version
	{

		Version() : value(0) { }
		Version(uint8 _major, uint8 _minor, uint16 _patch) : value((uint32(_major) << 24) + (uint32(_minor) << 16) + uint32(_patch)) { }
		Version(uint8 _major, uint8 _minor) : value((uint32(_major) << 24) + (uint32(_minor) << 16)) { }
		explicit Version(const std::string & _value) : value(parse(_value).value) { }

		friend bool operator < (Version const & a, Version const & b) { return a.getPoorVersion() < b.getPoorVersion(); }
		friend bool operator >= (Version const & a, Version const & b) { return !(a < b); }
		friend bool operator > (Version const & a, Version const & b) { return (b < a); }
		friend bool operator <= (Version const & a, Version const & b) { return !(a > b); }

		friend bool operator == (Version const & a, Version const & b) { return !(a < b) && !(a > b); }
		friend bool operator != (Version const & a, Version const & b) { return !(a == b); }

		friend std::ostream& operator << ( std::ostream& _stream, const Version &  _value ) {
			_stream << _value.print();
			return _stream;
		}

		friend std::istream& operator >> ( std::istream& _stream, Version &  _value ) {
			std::string value;
			_stream >> value;
			_value = Version::parse(value);
			return _stream;
		}

		uint8 getMajor() const { return uint16((value & 0xFF000000) >> 24); }
		uint8 getMinor() const { return uint8((value & 0x00FF0000) >> 16); }
		uint16 getPatch() const { return uint8(value & 0x0000FFFF); }

		int getPoorVersion() const { return value & 0xFFFF0000; }
		int getFullVersion() const { return value; }

		std::string print() const
		{
			if (getPatch() == 0) return utility::toString(getMajor(), ".", getMinor());
			return utility::toString(getMajor(), ".", getMinor(), ".", getPatch());
		}

		static Version parse(const std::string & _value)
		{
			const std::vector<std::string> & vec = utility::split(_value, ".");
			if (vec.empty()) return Version();
			uint8 major = utility::parseValue<uint8>(vec[0]);
			uint8 minor = vec.size() > 1 ? utility::parseValue<uint8>(vec[1]) : 0;
			uint16 patch = vec.size() > 2 ? utility::parseValue<uint16>(vec[2]) : 0;
			return Version(major, minor, patch);
		}

	private:
		uint32 value;
	};

} // namespace MyGUI

#endif // __MYGUI_VERSION_H__