#include "playbutton.h"

PlayButton::PlayButton(const QString& startText, const QString& stopText, QWidget *parent) :
    QPushButton(startText, parent), _startText(startText), _stopText(stopText), _started(false)
{
    connect(this, SIGNAL(clicked()), this, SLOT(changeState()));
}

void PlayButton::changeState() {
    _started = !_started;
    setText(_started ? _stopText : _startText);
    if (_started) emit timerStart();
    else emit timerStop();
}
