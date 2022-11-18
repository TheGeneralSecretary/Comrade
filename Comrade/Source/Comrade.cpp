#include "comradepch.h"

#include <Comrade/Core/Application.h>
#include <Comrade/Core/Logger.h>

class Sandbox : public Comrade::Application
{
public:
	Sandbox(const Comrade::ApplicationProps& props)
		: Comrade::Application(props)
	{
	}

	~Sandbox()
	{
	}

	virtual void OnUpdate(Comrade::DeltaTime dt) override
	{
		COMRADE_LOG_INFO("FPS {}", (1.0f/dt));
	}
};

int main(int argc, char** argv)
{
	Comrade::Logger::Init();

	Sandbox* sandbox = new Sandbox({ "Sandbox", 640, 480, true });
	sandbox->Run();
	delete sandbox;
	return 0;
}
