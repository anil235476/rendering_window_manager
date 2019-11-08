#ifndef _BUTTON_HANDLER_H__
#define _BUTTON_HANDLER_H__
#include <Windows.h>
#include "display_manager/win32_window.h"

constexpr const char* button_handler_msg_id = "button_handler";

constexpr int ID_CLOSE = 1101;
constexpr int MIC_ON_OFF = ID_CLOSE + 1;
constexpr int CAM_ON_OFF = ID_CLOSE + 2;

namespace util {
	class func_thread_handler;
	struct button_handler {
		button_handler(HWND parent_wnd, util::func_thread_handler* handler_);
		void reposition();
		void on_button_click(int button_id);
		void on_button_click_msg(std::string button_id);
	private:
		util::func_thread_handler* function_handler_{ nullptr };
		bool toggle_mic();//returns true if off->on toggling
		bool toggle_cam();//returns true if off->on toggling
		display::win32_window leave_btn_;
		const int leave_btn_x_{ 0 }; //these can be removed if these remain constant
		const int leave_btn_y_{ 0 };

		display::win32_window mic_btn_;
		const int mic_btn_x_{ 0 };
		const int mic_btn_y_{ 0 };

		display::win32_window cam_btn_;
		const int cam_btn_x_{ 0 };
		const int cma_btn_y_{ 0 };
	};

}//namespace util


#endif//_BUTTON_HANDLER_H__