#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "rendering_server_client/rendering_server_client.h"
#include "json_parser/json_parser.h"
#include <chrono>

TEST_CASE("test show hide", "[unit-test]") {
	grt::sender sender;
	auto r = sender.sync_connect(RENDERING_SERVER_IP, RENDERING_SERVER_PORT);
	const auto status = r.wait_for(std::chrono::seconds(5));
	REQUIRE(status == std::future_status::ready);
	REQUIRE(r.get());

	auto makeShowRenderer = [&sender](bool flag) {
		const auto m = grt::make_show_hide_msg(flag); //hide
		sender.send_to_renderer("hide", m, [](auto, auto) {});
		sender.done("hide");
	};

	{
		makeShowRenderer(false);
		std::cout << "enter 1 if rendering window gets hide\n";
		int response;
		std::cin >> response;
		REQUIRE(response == 1);
		std::cout << "\ngoing to show window now\n";
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	{
		makeShowRenderer(true);
		std::cout << "enter 1 if rendering window gets shown\n";
		int response;
		std::cin >> response;
		REQUIRE(response == 1);
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	{
		sender.register_for_session_leave_msg([](auto, auto) {
			std::cout << "received close request, \n";
		});
		std::cout << "wait for leave from rendering window\n";
		int response;
		std::cin >> response;
	}

}