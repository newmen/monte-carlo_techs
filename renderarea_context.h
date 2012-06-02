#ifndef RENDERAREA_CONTEXT_H
#define RENDERAREA_CONTEXT_H

#include <QWidget>
#include "area_data.h"

class RenderAreaContext : public QWidget
{
    Q_OBJECT
public:
    explicit RenderAreaContext(const AreaData *area);

protected:
    void paintEvent(QPaintEvent *);
    
private:
    const AreaData *_area;
};

#endif // RENDERAREA_CONTEXT_H
