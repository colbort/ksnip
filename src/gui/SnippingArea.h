/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef SNIPPINGAREA_H
#define SNIPPINGAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QDesktopWidget>

#include "src/widgets/CustomCursor.h"

class SnippingArea : public QWidget
{
    Q_OBJECT
public:
    SnippingArea(QWidget *parent);
    void show();

signals:
    void areaSelected(const QRect &);
    void cancel();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPoint        mMouseDownPosition;
    bool          mMouseIsDown;
    QRect         mCaptureArea;
    CustomCursor *mCursor;

    QRect calculateArea(const QPoint &pointA, const QPoint &pointB);
};

#endif // SNIPPINGAREA_H