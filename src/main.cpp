#include "Application.hpp"

CApp App;

int main() {
	App.Set("config.txt", "no title");
	App.Run();
	App.Exit();

	return 0;
}

