//@author A0128603L

// Class QSFMLCanvas
// Is a derived class to combine Qt(Widget) and SFML(RenderWindow)
// Code reference: http://sfml-dev.org/tutorials/1.6/graphics-qt.php

#include <SFML/Graphics.hpp>
#include <QtWidgets/Qwidget.h>
#include <QtCore/Qtimer.h>

class QSFMLCanvas : public QWidget, public sf::RenderWindow{
public:

    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
    virtual ~QSFMLCanvas();

private:

    virtual void Init() { return; }
    virtual void Update() { return; }
    virtual QPaintEngine* paintEngine() const;
	virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};