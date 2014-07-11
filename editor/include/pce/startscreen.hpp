//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_STARTSCREEN_HPP
#define PCE_STARTSCREEN_HPP


#include <QDesktopWidget>
#include <QLabel>
#include <QTimer>


namespace pce
{
	class startscreen : public QLabel
	{
		QTimer m_killtimer;
		
	public:
		startscreen()
		{
			// set up the visuals
			this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
			this->setPixmap(QPixmap{}.fromImage(QImage{"://assets/logo_editor.png"}));
			this->adjustSize();
			this->move(QDesktopWidget{}.availableGeometry().center() - this->geometry().center());
			
			// set up timer
			this->connect(&m_killtimer, SIGNAL(timeout()), this, SLOT(close()));
			m_killtimer.start(3000);
		}
	};
}


#endif // PCE_STARTSCREEN_HPP
