#include "renderarea.h"
#include "window.h"

#include <QtWidgets>

Window::Window()
{
    renderArea = new RenderArea;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor{255, 230, 255});
    setPalette(pal);

    setWindowTitle(tr("Basic Drawing"));
    setFixedSize(1600, 900);
    renderArea->setFocusPolicy(Qt::StrongFocus);
    renderArea->setAutoFillBackground(true);
}
