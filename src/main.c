#include "flappy-box.h"

int main(int argc, char* argv[])
{
	InitWindow(800, 600, "flappy-box");
	SetTargetFPS(60);

    run_flappy_box();

	CloseWindow();

    return 0;
}
