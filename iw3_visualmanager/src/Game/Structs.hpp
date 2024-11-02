#pragma once

namespace Game
{
	union DvarLimits
	{
		struct
		{
			int stringCount;
			const char **strings;
		} enumeration;

		struct
		{
			int min;
			int max;
		} integer;

		struct
		{
			float min;
			float max;
		} value;

		struct
		{
			float min;
			float max;
		} vector;
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char *string;
		char color[4];
	};

	enum class dvar_type : std::int8_t
	{
		boolean = 0,
		value = 1,
		vec2 = 2,
		vec3 = 3,
		vec4 = 4,
		integer = 5,
		enumeration = 6,
		string = 7,
		color = 8,
		rgb = 9 // Color without alpha
	};

	enum dvar_flags : std::uint16_t
	{
		none				= 0x0,
		saved				= 0x1,
		user_info			= 0x2, // sent to server on connect or change
		server_info			= 0x4, // sent in response to front end requests
		replicated			= 0x8,
		write_protected		= 0x10,
		latched				= 0x20,
		read_only			= 0x40,
		cheat_protected		= 0x80,
		temp				= 0x100,
		no_restart			= 0x400, // do not clear when a cvar_restart is issued
		user_created		= 0x4000, // created by a set command
	};

	struct dvar_s
	{
		const char *name;
		const char *description;
		//unsigned __int16 flags;
		dvar_flags flags;
		//char type;
		dvar_type type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		bool(__cdecl *domainFunc)(dvar_s *, DvarValue);
		dvar_s *hashNext;
	};
}