#pragma once

namespace Game
{
	template <typename T>
	class function
	{
	public:
		using result_type = typename std::function<T>::result_type;

		function() : func_(reinterpret_cast<T*>(nullptr))
		{
		};

		function(const std::uintptr_t& address) : func_(reinterpret_cast<T*>(address))
		{
		}

		function(const function<T>& function) : func_(function.func_)
		{
		}

		function& operator=(const std::uintptr_t& address)
		{
			this->func_ = std::function<T>(reinterpret_cast<T*>(address));
			return *this;
		}

		function& operator=(const function<T>& function)
		{
			this->func_ = function.func_;
			return *this;
		}

		template <typename ...Args>
		result_type operator()(Args&& ...args)
		{
			return this->func_(args...);
		}

		result_type operator()(void)
		{
			return this->func_();
		}

		T* get() const
		{
			return func_;
		}

		operator void*() const
		{
			return this->func_;
		}

	protected:
		T* func_;
	};

	void iPrintLnBold(const char* text);

	void dvar_set_value_dirty(dvar_s* dvar, int value);
	void dvar_set_value_dirty(dvar_s* dvar, bool value);
	void dvar_set_value_dirty(dvar_s* dvar, float dvar_value);
	void dvar_set_value_dirty(dvar_s* dvar, const float* dvar_value, int size);
	void dvar_set_value_dirty(dvar_s* dvar, const char* dvar_value);

	typedef void(*Cmd_ExecuteSingleCommand_t)(int controller, int a2, const char* cmd);
		extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

	typedef void(*Com_PrintMessage_t)(int, const char*, char);
		extern Com_PrintMessage_t Com_PrintMessage;

	typedef void(*Com_Printf_t)(int, const char*, char);
		extern Com_Printf_t Com_Printf;

	typedef void(__cdecl* Com_Error_t)(int code, const char* fmt, ...);
		extern Com_Error_t Com_Error;
}