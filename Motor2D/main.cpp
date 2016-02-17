#include <stdio.h>
#include <stdlib.h>

#include "p2Log.h"
#include "App.h"

#pragma comment (lib, "Motor2D/SDL/libx86/SDL2.lib")

// Due to a problem with SDL:
//"  Error1 error LNK2005: _main already defined in
//   SDL2main.lib(SDL_windows_main.obj)  "
// I also include...
//#include "SDL\include\SDL.h"

// pragma is an exclusive extension of Visual Studio,
// so it only works on here. 
//#pragma comment( lib, "SDL/lib/x86/SDL2.lib")
//#pragma comment( lib, "SDL/lib/x86/SDL2main.lib")

// --------------- Dr Memory ---------------	
// Arguments -visual_studio -- "$(TargetPath)"
// Directory $(SolutionDir)/

// ------------- SDL Config --------------------------

/* Setting up SDL configuration. On Project Properties
Configuration Propertires/VC++ Directories:
->Include directories: $(ProjectDir)SDL\include
->Library directories: $(ProjectDir)SDL\lib\x86
Linker/Input/Additional Dependencies, include
$(ProjectDir)SDL\lib\x86\SDL2.lib
$(ProjectDir)SDL\lib\x86\SDL2main.lib
Linker/Input/System/Subsystem/ choose
Windows (/SUBSYSTEM:WINDOWS)
*/

// ------------- PhysFS Config --------------------------

/* Setting up PhysFS configuration. On Project Properties
Configuration Propertires/VC++ Directories:
->Include directories: $(ProjectDir)PhysFS\include
->Library directories: $(ProjectDir)PhysFS\libx86
Linker/Input/Additional Dependencies, include
$(ProjectDir)PhysFS\libx86\physfs.lib
$(ProjectDir)PhysFS\libx86\physfs.exp
Linker/Input/System/Subsystem/ choose
Windows (/SUBSYSTEM:WINDOWS)
*/

// ------------- Include rules ------------------------

/*If, for example, class A uses class B, then class B is one of class A's
dependencies. Whether it can be forward declared or needs to be included
depends on how B is used within A:

-do nothing if : A makes no references at all to B
-do nothing if : The only reference to B is in a friend declaration
-forward declare B if : A contains a B pointer or reference : B* myb;
-forward declare B if: one or more functions has a B object / pointer / reference
as a parementer, or as a return type : B MyFunction(B myb);
-#include "b.h" if: B is a parent class of A
-#include "b.h" if : A contains a B object : B myb;*/

enum MainStates
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App *app = NULL;

int main(int argc, char** argv)
{
	LOG("======> Application initiating <=======");

	MainStates state = CREATE;
	int exit = EXIT_FAILURE;

	while (state != EXIT)
	{
		switch (state)
		{
		case(CREATE) :

			LOG("======> Creation Step...");
			app = new App(argc, argv);
			if (app == NULL)
			{
				LOG("Creation Error!");
				state = FAIL;
			}
			else
				state = AWAKE;
			break;

		case(AWAKE) :

			LOG("======> awake Step...");
			if (app->awake() != true)
			{
				LOG("awake Error!");
				state = FAIL;
			}
			else
				state = START;
			break;

		case(START) :

			LOG("======> start Step...");
			if (app->start() != true)
			{
				LOG(" start Error!");
				state = FAIL;
			}
			else
			{
				LOG("======> update Step...");
				state = LOOP;
			}
			break;

		case(LOOP) :
			if (app->update() == false)
				state = CLEAN;
			break;

		case(CLEAN) :

			LOG("======> Clean Step...");
			if (app->cleanUp() != true)
				state = FAIL;
			else
			{
				if (app != NULL)
				{
					delete app;
					app = NULL;
				}
				state = EXIT;
				exit = EXIT_SUCCESS;
			}
			break;

		case(FAIL) :

			LOG("Exiting program due to errors.");
			state = EXIT;
			exit = EXIT_FAILURE;
			break;

		}
	}

	LOG("Exiting program.");
	return exit;
}