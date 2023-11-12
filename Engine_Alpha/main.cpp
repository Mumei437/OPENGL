#include"Renderer.h"
#include"math.h"
int main(int argc, char** argv)
{
	
	Renderer renderer(600, 600, "Muramasa");

	//Vector3 clear_color(1, 1, 0);

	//renderer.SetClearColor(clear_color);

	while(renderer.IsContinue())
	{
		renderer.Run();
	}

	return 0;
}