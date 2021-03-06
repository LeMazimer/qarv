/*
    QArv, a Qt interface to aravis.
    Copyright (C) 2012, 2013 Jure Varlec <jure.varlec@ad-vega.si>
                             Andrej Lajovic <andrej.lajovic@ad-vega.si>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef QARVGUI_H
#define QARVGUI_H

#include "qarvcamera.h"
#include <QMainWindow>
#include <QApplication>

#include <opencv2/opencv.hpp>

#pragma GCC visibility push(default)

class QArvGuiExtension;

//! QArvGui represents the widget for working with a camera.
/*! The init() functions should be called to load translations and other setup.
 *  After that, the GUI can be instantiated. It will immediately start looking
 *  for available cameras.
 *
 * Using QArvGui in standalone mode is very easy. The following example is
 * basically the main() function for QArv's standalone program:
 * \code
   int main(int argc, char** argv) {
     QApplication a(argc, argv);
     QArvCamera::init();
     QArvGui::init(&a);

     QCoreApplication::setOrganizationDomain("myorganization.com");
     QCoreApplication::setOrganizationName("My Organization");
     QCoreApplication::setApplicationName("ProgramName");

     QArvGui g;
     g.show();
   return a.exec();
   }
 * \endcode
 *
 * When not in standalone mode, the "Recording" tab disappears and the "Record"
 * button enables or disables the frameReady() signal. This can be overriden by
 * forceRecording(), which permanenly enables the signal. The current frame can
 * always be read using getFrame(), but is only updated when frameReady is
 * emitted.
 *
 * The underlying widget is a subclass of QMainWindow and can be accessed via
 * mainWindow(). This allows the host application to control dock behaviour
 * etc.
 */
class QArvGui : public QWidget {
    Q_OBJECT

public:
    QArvGui(QWidget* parent = 0, bool standalone = true);
    ~QArvGui();

    //! Does static initialization.
    static void init(QApplication* a);

    //! Permanently enable the frameReady() signal and disable some GUI options.
    void forceRecording();

    //! Returns the camera object.
    QArvCamera* camera();

    //! Returns the underlying QMainWindow.
    QMainWindow* mainWindow();

signals:
    //! Emitted when a new frame arrives from the camera.
    /*!
     * If the QArvGui will not be used to display frames, connecting
     * to this signal and using QArvDecoder is more efficient.
     *
     * \param raw Undecoded buffer. Be aware that, depending on the settings in the GUI, this data may be overwritten if not used or copied soon enough.
     * \param rawAravisBuffer See QArvCamera::getFrame().
     */
    void frameReady(QByteArray raw, ArvBuffer* rawAravisBuffer);

    //! Emitted when a new frame arrives from the processing thread.
    /*!
     * If the QArvGui is used to display frames, it will need to decode
     * and (possibly) process them. In that case, connecting to this signal
     * is more efficient than using the raw frame and decoding it again.
     *
     * \param processed The frame as seen in the GUI video display. It is not copied, use cv::Mat::clone() if necessary.
     */
    void frameReady(cv::Mat processed);

    //! Emmited when the Record button is toggled.
    void recordingToggled(bool enabled);

private slots:
    void signalForwarding(bool enable);

protected:
    void closeEvent(QCloseEvent* event);

private:
    QArvGuiExtension* ext;

    friend class QArvGuiExtension;
};

#pragma GCC visibility pop

#endif
