#pragma once
#include<exception>
#define WERROR_UNKNOWN 0
#define WERROR_ARGUMENT 1
#define WERROR_INITIALIZE 2
#define WERROR_ARGUMENT 3
#define WERROR_ARGUMENT 4
#define WERROR_FILE_LOAD 9
#define WERROR_LIBRARY_LOAD 10
#define WERROR_BAD_POINTER 11
#define WERROR_BAD_CALL 12

#include"debuger.h"

#define excep(error_type) _excep(error_type,__func__,__LINE__,__FILE__)
#define excep(error_type,error_message) _excep(error_type,__func__,__LINE__,__FILE__,error_message)

inline void _excep(int error_type, const char* func_name, int line, const char* file_name, const string& error_str = "")
{
	switch (error_type)
	{
	case WERROR_ARGUMENT:
		debug << "[Argument Error]";
		break;
	case WERROR_INITIALIZE:
		debug << "[Initialize Error]";
		break;
	case WERROR_FILE_LOAD:
		debug << "[File Load Error]";
		break;
	case WERROR_LIBRARY_LOAD:
		debug << "[Library Load Error]";
		break;
	case WERROR_BAD_POINTER:
		debug << "[Bad Pointer]";
	case WERROR_BAD_CALL:
		debug << "[Bad function call]";
	default:
	case WERROR_UNKNOWN:
		debug << "[Unknown Error] ";
		break;
	}
	debug << "[Function: " << func_name << "]" <<
		"[Line: " << line << "]" << "[File: " << file_name << "]" << endl;
	debug << "[Error message]: " << error_str << endl;
	__debugbreak();
}
