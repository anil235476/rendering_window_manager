#include <cassert>
#include "win32_window.h"

namespace display {

	win32_window::win32_window(HWND handle, std::string name, HWND leave_btn)
		:hwnd_{ handle }, name_{ name }, leave_btn_{ leave_btn } {
		
	}

	win32_window::~win32_window() {
		DestroyWindow(hwnd_);
	}

	void win32_window::reposition(int x, int y, int w, int h) {
		const auto ret = SetWindowPos(
			hwnd_,
			HWND_TOP,
			x,
			y,
			w,
			h,
			SWP_SHOWWINDOW
		);
		assert(ret);
		ShowWindow(hwnd_, SW_SHOWNORMAL);

		SetWindowPos(leave_btn_, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
	}

	std::pair<int, int>
		get_desktop_width_height() {
		auto hwnd = GetDesktopWindow();
		assert(hwnd);
		RECT rect;
		const auto r = GetWindowRect(hwnd, &rect);
		assert(r);
		int const width = rect.right - rect.left;
		assert(width > 0);

		int const height = rect.bottom - rect.top;

		assert(height > 0);

		return std::make_pair(width, height);
	}

	int get_desktop_width() {
		return get_desktop_width_height().first;
	}
	int get_desktop_height() {
		return get_desktop_width_height().second;
	}


}			//display