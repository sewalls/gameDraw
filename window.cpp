#include "renderarea.h"
#include "window.h"

#include <QtWidgets>

Window::Window()
{
    renderArea = new RenderArea;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Drawing"));
    setFixedSize(1200, 800);
    renderArea->setFocusPolicy(Qt::StrongFocus);
}
