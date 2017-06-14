/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#ifndef VIEWER_WINDOW_MANAGER_H
#define VIEWER_WINDOW_MANAGER_H

#include <QFrame>
#include <QColor>
#include <iostream>
#include "../mainwindow.h"

namespace Ui {
    class WindowManager;
}

class WindowManager : public QFrame {
        Q_OBJECT

    public:
        explicit WindowManager(QWidget *parent = 0);
        ~WindowManager();

    private slots:
        void on_backgroundColorButton_clicked();

        void on_saveSnapshotButton_clicked();

        void on_fullScreenCheckBox_stateChanged(int state);

        void on_showAxisCheckBox_stateChanged(int state);

    private:
        Ui::WindowManager* ui;
        MainWindow* mainwindow;
};

#endif // VIEWER_WINDOW_MANAGER_H
