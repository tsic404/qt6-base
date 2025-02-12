// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QPlainTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTextStream>
#include <QTimer>
#include <QPainter>
#include <QLinearGradient>

#include "previewwindow.h"

void PreviewWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0, QColor("#64b3f4"));
    gradient.setColorAt(1, QColor("#c2e59c"));
    painter.fillRect(QRect(0, 0, width(), height()), gradient);
}

static void formatWindowFlags(QTextStream &str, Qt::WindowFlags flags)
{
    str << "Window flags: " << Qt::hex << Qt::showbase << unsigned(flags) << Qt::noshowbase
        << Qt::dec << ' ';
    switch (flags & Qt::WindowType_Mask) {
    case Qt::Window:
        str << "Qt::Window";
        break;
    case Qt::Dialog:
        str << "Qt::Dialog";
        break;
    case Qt::Sheet:
        str << "Qt::Sheet";
        break;
    case Qt::Drawer:
        str << "Qt::Drawer";
        break;
    case Qt::Popup:
        str << "Qt::Popup";
        break;
    case Qt::Tool:
        str << "Qt::Tool";
        break;
    case Qt::ToolTip:
        str << "Qt::ToolTip";
        break;
    case Qt::SplashScreen:
        str << "Qt::SplashScreen";
        break;
    }

    if (flags & Qt::MSWindowsFixedSizeDialogHint)
        str << "\n| Qt::MSWindowsFixedSizeDialogHint";
    if (flags & Qt::BypassWindowManagerHint)
        str << "\n| Qt::BypassWindowManagerHint";
    if (flags & Qt::FramelessWindowHint)
        str << "\n| Qt::FramelessWindowHint";
    if (flags & Qt::WindowTitleHint)
        str << "\n| Qt::WindowTitleHint";
    if (flags & Qt::WindowSystemMenuHint)
        str << "\n| Qt::WindowSystemMenuHint";
    if (flags & Qt::WindowMinimizeButtonHint)
        str << "\n| Qt::WindowMinimizeButtonHint";
    if (flags & Qt::WindowMaximizeButtonHint)
        str << "\n| Qt::WindowMaximizeButtonHint";
    if (flags & Qt::WindowCloseButtonHint)
        str << "\n| Qt::WindowCloseButtonHint";
    if (flags & Qt::WindowContextHelpButtonHint)
        str << "\n| Qt::WindowContextHelpButtonHint";
    if (flags & Qt::WindowShadeButtonHint)
        str << "\n| Qt::WindowShadeButtonHint";
    if (flags & Qt::WindowStaysOnTopHint)
        str << "\n| Qt::WindowStaysOnTopHint";
    if (flags & Qt::CustomizeWindowHint)
        str << "\n| Qt::CustomizeWindowHint";
    if (flags & Qt::WindowStaysOnBottomHint)
        str << "\n| Qt::WindowStaysOnBottomHint";
    if (flags & Qt::WindowFullscreenButtonHint)
        str << "\n| Qt::WindowFullscreenButtonHint";
    if (flags & Qt::WindowTransparentForInput)
        str << "\n| Qt::WindowTransparentForInput";
    if (flags & Qt::WindowOverridesSystemGestures)
        str << "\n| Qt::WindowOverridesSystemGestures";
    if (flags & Qt::WindowDoesNotAcceptFocus)
        str << "\n| Qt::WindowDoesNotAcceptFocus";
    if (flags & Qt::MaximizeUsingFullscreenGeometryHint)
        str << "\n| Qt::MaximizeUsingFullscreenGeometryHint";
    if (flags & Qt::NoDropShadowWindowHint)
        str << "\n| Qt::NoDropShadowWindowHint";
}

static void formatWindowStates(QTextStream &str, Qt::WindowStates states)
{
    str << "Window states: " << Qt::hex << Qt::showbase << unsigned(states) << Qt::noshowbase
        << Qt::dec << ' ';
    if (states & Qt::WindowActive) {
        str << "Qt::WindowActive ";
        states &= ~Qt::WindowActive;
    }
    switch (states) {
    case Qt::WindowNoState:
        str << "Qt::WindowNoState";
        break;
    case Qt::WindowMinimized:
        str << "Qt::WindowMinimized";
        break;
    case Qt::WindowMaximized:
        str << "Qt::WindowMaximized";
        break;
    case Qt::WindowFullScreen:
        str << "Qt::WindowFullScreen";
        break;
    default:
        break;
    }
}

QTextStream &operator<<(QTextStream &str, const QRect &r)
{
    str << r.width() << 'x' << r.height() << Qt::forcesign << r.x() << r.y() << Qt::noforcesign;
    return str;
}

static QString formatWidgetInfo(const QWidget *w)
{
    QString result;
    QTextStream str(&result);
    formatWindowFlags(str, w->windowFlags());
    str << '\n';
    formatWindowStates(str, w->windowState());
    const QRect frame = w->frameGeometry();
    const QRect geometry = w->geometry();
    str << "\n\nFrame: " << frame << "\nGeometry: " << geometry << "\nMargins: "
        << (geometry.x() - frame.x()) << ", " << (geometry.top() - frame.top())
        << ", " << (frame.right() - geometry.right()) << ", "
        << (frame.bottom() - geometry.bottom());
    return result;
}

static QPlainTextEdit *createControlPanel(QWidget *widget)
{
    QVBoxLayout *layout = new QVBoxLayout(widget);
    QPlainTextEdit *textEdit = new QPlainTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    layout->addWidget(textEdit);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    layout ->addLayout(bottomLayout);
    QGridLayout *buttonLayout = new QGridLayout;
    bottomLayout->addStretch();
    bottomLayout->addLayout(buttonLayout);
    QPushButton *showNormalButton = new QPushButton(PreviewWidget::tr("Show normal"));
    QObject::connect(showNormalButton, SIGNAL(clicked()), widget, SLOT(showNormal()));
    buttonLayout->addWidget(showNormalButton, 0, 0);
    QPushButton *showMinimizedButton = new QPushButton(PreviewWidget::tr("Show minimized"));
    QObject::connect(showMinimizedButton, SIGNAL(clicked()), widget, SLOT(showMinimized()));
    buttonLayout->addWidget(showMinimizedButton, 0, 1);
    QPushButton *showMaximizedButton = new QPushButton(PreviewWidget::tr("Show maximized"));
    QObject::connect(showMaximizedButton, SIGNAL(clicked()), widget, SLOT(showMaximized()));
    buttonLayout->addWidget(showMaximizedButton, 0, 2);
    QPushButton *showFullScreenButton = new QPushButton(PreviewWidget::tr("Show fullscreen"));
    QObject::connect(showFullScreenButton, SIGNAL(clicked()), widget, SLOT(showFullScreen()));
    buttonLayout->addWidget(showFullScreenButton, 0, 3);

    QPushButton *updateInfoButton = new QPushButton(PreviewWidget::tr("&Update Info"));
    QObject::connect(updateInfoButton, SIGNAL(clicked()), widget, SLOT(updateInfo()));
    buttonLayout->addWidget(updateInfoButton, 1, 0);
    QPushButton *closeButton = new QPushButton(PreviewWidget::tr("&Close"));
    QObject::connect(closeButton, SIGNAL(clicked()), widget, SLOT(close()));
    buttonLayout->addWidget(closeButton, 1, 3);

    return textEdit;
}

PreviewWidget::PreviewWidget(QWidget *parent)
    : QWidget(parent)
{
    textEdit = createControlPanel(this);
    setWindowTitle(tr("Preview <QWidget> Qt %1").arg(QLatin1String(QT_VERSION_STR)));
}

bool PreviewWidget::event(QEvent *event)
{
    const bool ret = QWidget::event(event);

    switch (event->type()) {
    case QEvent::Move:
    case QEvent::Resize:
    case QEvent::WindowStateChange:
        updateInfo();
        break;
    default:
        break;
    }

    return ret;
}

void PreviewWidget::setWindowFlags(Qt::WindowFlags flags)
{
    if (flags == windowFlags())
        return;
    QWidget::setWindowFlags(flags);
    QTimer::singleShot(0, this, SLOT(updateInfo()));
}

void PreviewWidget::updateInfo()
{
      textEdit->setPlainText(formatWidgetInfo(this));
}

PreviewDialog::PreviewDialog(QWidget *parent)
    : QDialog(parent)
{
    textEdit = createControlPanel(this);
    setWindowTitle(tr("Preview <QDialog> Qt %1").arg(QLatin1String(QT_VERSION_STR)));
}

bool PreviewDialog::event(QEvent *event)
{
    const bool ret = QDialog::event(event);

    switch (event->type()) {
    case QEvent::Move:
    case QEvent::Resize:
    case QEvent::WindowStateChange:
        updateInfo();
        break;
    default:
        break;
    }

    return ret;
}

void PreviewDialog::setWindowFlags(Qt::WindowFlags flags)
{
    if (flags == windowFlags())
        return;
    QWidget::setWindowFlags(flags);
    QTimer::singleShot(0, this, SLOT(updateInfo()));
}

void PreviewDialog::updateInfo()
{
    textEdit->setPlainText(formatWidgetInfo(this));
}
