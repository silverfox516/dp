#include "dialog.h"
#include "button.h"
#include "application.h"

const Topic PRINT_TOPIC = 1;
const Topic PAPER_ORIENTATION_TOPIC = 2;
const Topic APPLICATION_TOPIC = 3;

int main(void)
{
	Application* application = new Application(APPLICATION_TOPIC);
	Dialog* dialog = new Dialog(application, PRINT_TOPIC);
	Button* button1 = new Button(dialog, PAPER_ORIENTATION_TOPIC);
	Button* button2 = new Button(dialog, -1);

	button1->HandleHelp();
	button2->HandleHelp();

	return 0;
}
