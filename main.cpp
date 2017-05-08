// main() function
// Copyright © 2009 The University of Chicago

// Entry point (it all starts here)
int main(int argc, char** argv);

#include <memory>
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include "linguisticamainwindow.h"

int main( int argc, char** argv )
{
	typedef std::auto_ptr<LinguisticaMainWindow> main_window_ptr;
	QApplication app(argc, argv);

	main_window_ptr main_window;
	
	{
		// splash screen image is linked into the Linguistica
		// executable (see linguistica.qrc)
		QSplashScreen splash(QPixmap(":/splash.png"));
		splash.show();

		main_window = main_window_ptr(new LinguisticaMainWindow(
					argc, argv, &app, NULL, 0));
		if (main_window->commandLineMode())
			// Don’t show main window; just exit.
			return 0;

		app.setMainWidget(main_window.get());
		splash.finish(main_window.get());
	}

	main_window->show();
	return app.exec();
}
