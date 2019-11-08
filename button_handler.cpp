#include "button_handler.h"
#include <string>
#include <cassert>
#include "function_thread_handler/func_thread_handler.h"
#include "json_parser.h"

constexpr int LEAVE_BT_WIDTH = 70;

constexpr int LEAVE_BT_HEIGHT = 20;
constexpr const char* LEAVE_STR = "Leave";
constexpr const char* MIC_OFF_STR = "Mic OFF";
constexpr const char* MIC_ON_STR = "Mic ON";
constexpr const char* CAM_OFF_STR = "Cam OFF";
constexpr const char* CAM_ON_STR = "Cam ON";


auto to_wstring(std::string v) {
	return std::wstring{ v.begin(), v.end() };
}

auto to_wstring_str(std::string v) {
	return to_wstring(v).c_str();
}

namespace detail {
	HWND create_button_window(HWND parent_wnd, std::wstring name, int ID) {
		auto window = ::CreateWindowEx(WS_EX_TOPMOST, L"Button", name.c_str(), WS_CHILD | WS_TABSTOP, 0, 0, 0, 0,
			parent_wnd, reinterpret_cast<HMENU>(ID), GetModuleHandle(NULL), NULL);
		assert(window);
		return window;
	}
}

namespace util {

	button_handler::button_handler(HWND hwnd, util::func_thread_handler* handler_)
		:function_handler_{handler_}
		, leave_btn_{ detail::create_button_window(hwnd, to_wstring(LEAVE_STR),ID_CLOSE), LEAVE_STR }
		, leave_btn_x_{ display::get_desktop_width() / 2 - 30 },
		leave_btn_y_{ display::get_desktop_height() - 120 },
		mic_btn_{ detail::create_button_window(hwnd, to_wstring(MIC_OFF_STR),MIC_ON_OFF), MIC_OFF_STR }
		, mic_btn_x_{ leave_btn_x_ + LEAVE_BT_WIDTH + 5 }
		, mic_btn_y_{ leave_btn_y_ }
		, cam_btn_{ detail::create_button_window(hwnd, to_wstring(CAM_OFF_STR),CAM_ON_OFF), CAM_OFF_STR }
		,cam_btn_x_{ mic_btn_x_  + LEAVE_BT_WIDTH  + 5}
		, cma_btn_y_{ leave_btn_y_ }
        {
		assert(function_handler_);
		function_handler_->register_id(button_handler_msg_id, std::bind(&button_handler::on_button_click_msg, this, std::placeholders::_1));
		
	}

	void button_handler::reposition() {
		leave_btn_.reposition(leave_btn_x_, leave_btn_y_, LEAVE_BT_WIDTH, LEAVE_BT_HEIGHT);
		mic_btn_.reposition(mic_btn_x_, mic_btn_y_, LEAVE_BT_WIDTH, LEAVE_BT_HEIGHT);
		cam_btn_.reposition(cam_btn_x_, cma_btn_y_, LEAVE_BT_WIDTH, LEAVE_BT_HEIGHT);
	}

	void button_handler::on_button_click(int button_id) {
		if (button_id == ID_CLOSE) {
			//leave button clicked
			//MessageBoxA(0, "Leave Button Clicked...", "	Clicked... ", 0);
			const auto m = grt::make_user_session_leave_req();
			function_handler_->dispatch(UI_SERVER_ID, m);
		}
		else if (button_id == MIC_ON_OFF) {
			//mic on off clicked
			//MessageBoxA(0, "MIC Button Clicked...", "	Clicked... ", 0);
			const bool mic_on = this->toggle_mic();
			function_handler_->dispatch(UI_SERVER_ID, grt::make_mic_toggle_req(mic_on));
		}
		else if (button_id == CAM_ON_OFF) {
			//cam on off clicked
			//MessageBoxA(0, "CAM Button Clicked...", "	Clicked... ", 0);
			const bool cam_on = this->toggle_cam();
			function_handler_->dispatch(UI_SERVER_ID, grt::make_camera_toggle_req(cam_on));
		}
		else {
			assert(false);//undefined message received.
		}
	}

	void button_handler::on_button_click_msg(std::string button_id) {
		this->on_button_click(std::stoi(button_id));
	}

	bool button_handler::toggle_mic() {
		if (mic_btn_.get_window_name() == MIC_OFF_STR)//command is for off
		{
			mic_btn_.set_window_name(MIC_ON_STR);
			return false;
		}
		//command is for off to on	
		mic_btn_.set_window_name(MIC_OFF_STR);
		return true;
	}
	bool button_handler::toggle_cam() {
		if (cam_btn_.get_window_name() == CAM_OFF_STR)//command is for off
		{
			cam_btn_.set_window_name(CAM_ON_STR);
			return false;
		}

		//command is for off to on toggling
		cam_btn_.set_window_name(CAM_OFF_STR);
		return true;
	}


}//namespace util