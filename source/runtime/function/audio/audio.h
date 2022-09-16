#pragma once
#include"core/log/debuger.h"
#include<mmsystem.h>

#pragma comment(lib,"Winmm.lib")
class AudioPlayer {
public:
	void open(const string& fileName, const string& alias) {
		if (sendCommand("open " + fileName + " alias " + alias)) {//´ò¿ª ±³¾°ÒôÀÖ
			debug("something not good when open audio");
		}
	}
	void close(const string& alias) {
		sendCommand("close " + alias);//´ò¿ª ±³¾°ÒôÀÖ
	}

	void play(const string& alias, bool repeat = false) {
		sendCommand("play " + alias + (repeat ? " repeat" : ""));
	}
	void pause(const string& alias) {
		sendCommand("pause " + alias);
	}
	void resume(const string& alias) {
		sendCommand("resume " + alias);
	}
	void stop(const string& alias) {
		sendCommand("stop " + alias);
	}

	int step(const string& alias, int new_step = -1) {
		if (new_step > -1) {
			sendCommand("step " + alias + " by " + itos(new_step));
			return new_step;
		}
		return queryStatus(alias, "position");
	}
	int seek(const string& alias, int newPos) {
		sendCommand("seek " + alias + " to " + itos(newPos));
	}
	int volume(const string& alias, int new_volume = -1) {
		if (new_volume > -1) {
			sendCommand("setaudio " + alias + " volume to " +itos(new_volume));
			return new_volume;
		}
		return queryStatus(alias, "volume");
	}
private:
	int queryStatus(const string& alias, const string& what) {
		string str = "status " + alias + " " + what;
		static char st[100] = {};
		memset(st, 0, sizeof(st));
		mciSendStringA(str.c_str(), st, sizeof(st), 0);
		return std::stoi(st);
	}

	bool sendCommand(const string& s) {
		return mciSendString(_T(s.c_str()), 0, 0, 0);
	}
	BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
	{
		DWORD dwMinSize;
		dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);
		assert(dwSize >= dwMinSize);

		MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
		return TRUE;
	}

	LPWSTR _T(string str) {
		static wchar_t s[500] = {};
		memset(s, 0, sizeof(s));
		MByteToWChar(str.c_str(), s, 500);
		return s;
	}
};