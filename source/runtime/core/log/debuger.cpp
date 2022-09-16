#include"debuger.h"

void Debuger::debugall(const string& s)
{
	string ret;
	for (int i = 0; i < s.length(); i++)
	{
		switch (s[i])
		{
		case '\n':
			ret += "\\n\n";
			break;
		case '\r':
			ret += "\\r";
			break;
		case '\0':
			break;
		case '\t':
			ret += "\t\\t";
			break;
		default:
			ret += s[i];
			break;
		}
	}
	ret += "\n\0";
	o << ret;
}

void Debuger::debugbyte(const string& s)
{
	string out;
	unsigned char cha;
	for (int i = 0; i < s.length(); i++)
	{
		cha = s[i];
		out += "\\" + itos(cha);
	}
	out.append("\n");
	o << out;
}

void Debuger::debughex(const string& s)
{
	string out;
	unsigned char c;
	for (int i = 0; i < s.length(); i++)
	{
		out += "\\";
		c = s[i];
		int first = c / 16;
		if (first < 10)
		{
			out += itos(first);
		}
		else out += char('A' + first - 10);
		int firsts = c % 16;
		if (firsts < 10)
		{
			out += itos(firsts);
		}
		else out += char('A' + firsts - 10);
	}
	out += "\n";
	o << out;
}

GLenum glCheckError_(const char* fun, const char* file, int line)
{
	GLenum errorCode = 0; bool noerror = true;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		noerror = false;
		string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		debug << error << " | " << file << " (" << line << " , " << fun << ")\n";
	}
	return noerror;
}

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	void* userParam)
{
	// 忽略一些不重要的错误/警告代码
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	debug << "---------------\n";
	debug << "Debug message (" << id << "): " << message << "\n";

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             debug << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   debug << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: debug << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     debug << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     debug << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           debug << "Source: Other"; break;
	} debug << "\n";

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               debug << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: debug << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  debug << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         debug << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         debug << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              debug << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          debug << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           debug << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               debug << "Type: Other"; break;
	} debug << "\n";

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         debug << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       debug << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          debug << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: debug << "Severity: notification"; break;
	} debug << "\n";
	debug << "\n";
}

