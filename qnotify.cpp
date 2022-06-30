/* Copyright 2013 Mohammed Nafees. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY MOHAMMED NAFEES ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL EELI REILIN OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * official policies, either expressed or implied, of Mohammed Nafees.
 */

// Self
#include "qnotify.h"

#include <QPixmapCache>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QTimer>

QNotify::QNotify( QWidget *parent ) :
    QWidget( parent )
{    
    QPixmapCache::insert( "success.png", QPixmap( ":/icons/success.png" ).scaledToHeight( 80, Qt::SmoothTransformation ) );
    QPixmapCache::insert( "error.png", QPixmap( ":/icons/error.png" ).scaledToHeight( 80, Qt::SmoothTransformation ) );
    QPixmapCache::insert( "warning.png", QPixmap( ":/icons/warning.png" ).scaledToHeight( 80, Qt::SmoothTransformation ) );
    
    animation = new QPropertyAnimation( this, "geometry" );
    connect( animation, SIGNAL(finished()), SLOT(onFinished()) );
    
    // defaults
    w = 800;
    x = parent->width() - w - 10;
    y = 10;
    setGeometry( x, y, w, 40 );
    showingNow = false;

    this->setStyleSheet("font: 35 12pt \"Microsoft Yahei\";");
}

QNotify::~QNotify()
{
    QPixmapCache::clear();
}

void QNotify::setPosition( QPoint p )
{
    x = p.x();
    y = p.y();
    setGeometry( x, y, w, 100 );
    repaint();
}

void QNotify::setDialogWidth( int width )
{
    w = width;
    setGeometry( x, y, w, 100 );
    repaint();
}

void QNotify::notify( QString text, NotificationType type, int duration )
{
    msgText = text;
    notifType = type;
    keepDuration = duration;
    repaint();
    
    animation->setDuration( 500 );
    animation->setStartValue( QRect( x, -100, w, 100 ) );
    animation->setEndValue( QRect( x, y, w, 100 ) );
    showingNow = true;
    animation->start();
    show();
}

void QNotify::onFinished()
{
    if ( showingNow ) {
        animation->setStartValue( QRect( x, y, w, 100 ) );
        animation->setEndValue( QRect( x, -100, w, 100 ) );
        QTimer::singleShot( keepDuration, animation, SLOT(start()) );
        showingNow = false;
    } else {
        showingNow = false;
        hide();
    }
}

void QNotify::paintEvent( QPaintEvent * )
{
    QPainter painter( this );
    painter.setRenderHints( QPainter::HighQualityAntialiasing | QPainter::Qt4CompatiblePainting );
    painter.setBrush( Qt::white );
    painter.setPen( Qt::NoPen );
    painter.drawRoundedRect( 0, 0, width(), height(), 5.0, 5.0 );
    QString key;
    if ( notifType == QNotify::SUCCESS ) {
        key = "success.png";
    } else if ( notifType == QNotify::ERROR ) {
        key = "error.png";
    } else if ( notifType == QNotify::WARNING ) {
        key = "warning.png";
    }
    int proposedCoord = height()/2 - QPixmapCache::find( key )->height()/2;
    painter.drawPixmap( 10, proposedCoord, *QPixmapCache::find( key ) );
    painter.setPen( Qt::black );
    int remainingWidth = width() - 120;
    painter.drawText( 120, 10, remainingWidth, height() - 20, Qt::AlignCenter | Qt::TextWordWrap, msgText );
}

void QNotify::mousePressEvent( QMouseEvent *mouseEvent )
{
    if ( mouseEvent->buttons() == Qt::LeftButton ) {
        animation->setStartValue( QRect( x, y, w, 100 ) );
        animation->setEndValue( QRect( x, -100, w, 100 ) );
        animation->start();
        showingNow = false;
    }
}
