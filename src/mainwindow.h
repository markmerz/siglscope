/****************************************************************************
**                                                                         **
**  This file is part of SiglScope.                                        **
**  SiglScope is set of graphical and command line programs for            **
**  interacting with Siglent SDS 1000 series Digital Storage Oscilloscope. **
**                                                                         **
**  This program is free software: you can redistribute it and/or modify   **
**  it under the terms of the GNU General Public License as published by   **
**  the Free Software Foundation, either version 3 of the License, or      **
**  (at your option) any later version.                                    **
**                                                                         **
**  This program is distributed in the hope that it will be useful,        **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of         **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
**  GNU General Public License for more details.                           **
**                                                                         **
**  You should have received a copy of the GNU General Public License      **
**  along with this program.  If not, see http://www.gnu.org/licenses/.    **
**                                                                         **
************************************************************************** **
**           Author: Markko Merzin                                         **
**          Contact: markko.merzin@gmail.com                               **
**             Date: 30.09.2015                                            **
**          Version: 0.1                                                   **
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addcommanddialog.h"
#include <vector>
#include "selectdevicedialog.h"
#include <string>
#include <QSettings>
#include <QList>
#include <QString>
#include "qcustomplot.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void actionExit();
    void addCommandFromMenu();
    void addCommandOK();
    void addCommandCancel();
    void customButtonClicked();
    void customCommandDeleteClicked();
    void saveSettings();
    void selectDevice();
    void selectDeviceCancel();
    void selectDeviceOK();

    // from qcustomplot interaction example
    void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void addRandomGraph();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable);

private:
    Ui::MainWindow *ui;
    AddCommandDialog* acd;



    QList<QString> customButtonLabels;
    QList<QString> customButtonTooltips;
    QList<QString> customButtonUsbtmcCommands;
    QList<int> customButtonsExpectReply;

    QList<QPushButton*> customButtons;

    SelectDeviceDialog* sdd;

    QString deviceString;
    std::string deviceFile;

    void findDeviceFileByDeviceString();
    void loadSettings();

    void addCustomCommandButton(QString label, QString tooltip);
    void drawGraph(QString waveLabel, std::vector<std::pair<double, double>>* rawwave);
};

#endif // MAINWINDOW_H
