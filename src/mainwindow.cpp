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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addcommanddialog.h"
#include <vector>
#include <algorithm>
#include <QObject>
#include <QPushButton>
#include "constants.h"
#include "Device.h"
#include "commandreplydialog.h"
#include <QStandardPaths>
#include <QDir>
#include <QVariantList>
#include "qcustomplot.h"
#include "Wave.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(actionExit()));

    connect(ui->actionAdd_Command, SIGNAL(triggered()), this, SLOT(addCommandFromMenu()));
    connect(ui->actionSave_Settings, SIGNAL(triggered()), this, SLOT(saveSettings()));

    connect(ui->actionConnect_to_device, SIGNAL(triggered(bool)), this, SLOT(selectDevice()));



    connect(ui->waveCH1Button, SIGNAL(clicked(bool)), this, SLOT(customButtonClicked()));
    connect(ui->waveCH2Button, SIGNAL(clicked(bool)), this, SLOT(customButtonClicked()));
    connect(ui->spectrumCH1Button, SIGNAL(clicked(bool)), this, SLOT(customButtonClicked()));
    connect(ui->spectrumCH2Button, SIGNAL(clicked(bool)), this, SLOT(customButtonClicked()));


    this->loadSettings();
    this->findDeviceFileByDeviceString();

    if (this->deviceFile.size() == 0) {
        this->ui->statusBar->showMessage("ERROR: device not found...", 0);
    } else {
        this->ui->statusBar->showMessage("Connected to " + QString::fromStdString(this->deviceFile) + ": " + this->deviceString, 0);
    }

    ui->customPlot->setNoAntialiasingOnDrag(true);

    // from qcustomplot interactions example:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    // ui->customPlot->xAxis->setRange(-8, 8);
    // ui->customPlot->yAxis->setRange(-5, 5);

    ui->customPlot->axisRect()->setupFullAxesBox();

    // ui->customPlot->plotLayout()->insertRow(0);
    // ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot, "Interaction Example"));

    ui->customPlot->xAxis->setLabel("x Axis");
    ui->customPlot->yAxis->setLabel("y Axis");

    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    // addRandomGraph();
    // addRandomGraph();
    // addRandomGraph();
    // addRandomGraph();

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(ui->customPlot, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
    connect(ui->customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(ui->customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCommandFromMenu() {
    this->acd = new AddCommandDialog(this);
    connect(this->acd, SIGNAL(accepted()), this, SLOT(addCommandOK()));
    connect(this->acd, SIGNAL(rejected()), this, SLOT(addCommandCancel()));
    acd->show();
    acd->activateWindow();

}

void MainWindow::addCustomCommandButton(QString label, QString tooltip) {
    QPushButton* newbutton = new QPushButton(ui->scrollAreaWidgetContents);
    newbutton->setFocusPolicy(Qt::StrongFocus);
    newbutton->setLayoutDirection(Qt::LeftToRight);
    newbutton->setText(label);
    newbutton->setToolTip(tooltip);
    ui->horizontalLayout->addWidget(newbutton);

    connect(newbutton, SIGNAL(clicked(bool)), this, SLOT(customButtonClicked()));

    this->customButtons.push_back(newbutton);

    QAction* newaction = new QAction(this);
    newaction->setText(label);

    ui->menuDelete_command->addAction(newaction);

    connect(newaction, SIGNAL(triggered(bool)), this, SLOT(customCommandDeleteClicked()));
}

void MainWindow::addCommandOK() {
    // this->ui->statusBar->showMessage("Add Command OK", 1000);

    QString label = this->acd->getLabelText();
    QString tooltip = this->acd->getTooltipText();
    QString usbtmccommand = this->acd->getUsbtmccommandText();
    int expectReply = this->acd->getExpectReply();
    // this->acd->clearTextFields();
    disconnect(this->acd, SIGNAL(accepted()), this, SLOT(addCommandOK()));
    disconnect(this->acd, SIGNAL(rejected()), this, SLOT(addCommandCancel()));
    delete this->acd;
    this->acd = NULL;

    if (label.length() == 0 || usbtmccommand.length() == 0) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", "No point having empty label or command...");
        messageBox.setFixedSize(500,200);

        return;
    }


    if (this->customButtonLabels.indexOf(label) != -1) {
    // if(std::find(this->customButtonLabels->begin(), this->customButtonLabels->end(), label) != this->customButtonLabels->end()) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", "Already have command with this label...");
        messageBox.setFixedSize(500,200);

        return;
    }

    this->customButtonLabels.push_back(label);
    this->customButtonTooltips.push_back(tooltip);
    this->customButtonUsbtmcCommands.push_back(usbtmccommand);
    this->customButtonsExpectReply.push_back(expectReply);

    addCustomCommandButton(label, tooltip);


}

void MainWindow::addCommandCancel() {
    // this->acd->clearTextFields();
    disconnect(this->acd, SIGNAL(accepted()), this, SLOT(addCommandOK()));
    disconnect(this->acd, SIGNAL(rejected()), this, SLOT(addCommandCancel()));
    delete this->acd;
    this->acd = NULL;
}

void MainWindow::drawGraph(QString waveLabel, std::vector<std::pair<double, double>>* rawwave) {

    int wavelen = rawwave->size();
    QVector<double> x(wavelen);
    QVector<double> y(wavelen);
    for (int c = 0; c < wavelen; c++) {
        std::pair<double, double> wavepair = rawwave->at(c);
        x[c] = wavepair.second;
        y[c] = wavepair.first;
    }
    // yeah, we could do it in previous for cycle...
    QVector<double>::iterator it;
    it = std::max_element(x.begin(), x.end());
    double maxX = *it;
    it = std::min_element(x.begin(), x.end());
    double minX = *it;
    it = std::max_element(y.begin(), y.end());
    double maxY = *it;
    it = std::min_element(y.begin(), y.end());
    double minY = *it;


    this->removeAllGraphs();

    ui->customPlot->addGraph();
    ui->customPlot->graph()->setName(waveLabel);
    ui->customPlot->graph()->setData(x, y);



    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);

    // if (rand()%100 > 50)
      // ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
    QPen graphPen;

    // graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    graphPen.setColor(QColor("darkGreen"));

    // graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
    graphPen.setWidthF(1);

    ui->customPlot->graph()->setPen(graphPen);

    ui->customPlot->xAxis->setRange(minX, maxX);
    ui->customPlot->yAxis->setRange(minY, maxY);

    // ui->customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    // ui->customPlot->yAxis->setScaleLogBase(100);
    // ui->customPlot->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    // ui->customPlot->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"


}

void MainWindow::customButtonClicked() {
    // QPushButton* button = qobject_cast<QPushButton*>sender();
    QPushButton* button = (QPushButton*) sender();
    if (button != NULL) {
        QString buttonlabel = button->text();
        // this->ui->statusBar->showMessage("Button " + buttonlabel + " clicked!", 5000);
        for (int c = 0; c < this->customButtons.size(); c++) {
            QString label = this->customButtons.at(c)->text();
            if (label == buttonlabel) {
                QString command = this->customButtonUsbtmcCommands.at(c);
                std::string commandstr = command.toStdString();
                //FIXME: custom commands
                // this->ui->statusBar->showMessage(command, 10000);

                if (this->deviceFile != std::string()) {
                    try {
                        Device device((std::string *) &(this->deviceFile));
                        std::string errstring;
                        std::string result;

                        switch (this->customButtonsExpectReply.at(c)) {
                        case EXPECT_NOREPLY:
                            device.command(commandstr);
                            break;
                        case EXPECT_ONELINER:
                            result = device.query(commandstr, errstring);
                            if (errstring.length() != 0) {
                                this->ui->statusBar->showMessage("ERROR: " + QString::fromStdString(errstring), 0);
                            } else {
                                this->ui->statusBar->showMessage(QString::fromStdString(result), 0);
                            }
                            break;
                        case EXPECT_NEWWINDOW:
                            result = device.query(commandstr, errstring);
                            if (errstring.length() != 0) {
                                this->ui->statusBar->showMessage("ERROR: " + QString::fromStdString(errstring), 0);
                            } else {
                                // QMessageBox messageBox;
                                // messageBox.information(this, label, QString::fromStdString(result));
                                // messageBox.setFixedSize(500,200);
                                CommandReplyDialog crd(this);

                                // crd.setFixedSize(500,200);

                                crd.setText(QString::fromStdString(result));
                                crd.exec();
                            }
                            break;
                        }



                    } catch (std::string ex) {
                        this->ui->statusBar->showMessage("ERROR: " + QString::fromStdString(ex), 0);
                    }
                } else {
                    this->ui->statusBar->showMessage("ERROR: Device not conneted...", 0);
                }

                return;
            }
        }

        // builtin commands
        if (buttonlabel == "Wave CH1") {
            QString waveCommand = "C1:WF? ALL";
            QString waveLabel = "Wave CH1";

            std::vector<uint8_t> raw_wave_input;
            try {
                Device device((std::string *) &(this->deviceFile));
                raw_wave_input = device.waveform(waveCommand.toStdString());
            } catch (std::string ex) {
                this->ui->statusBar->showMessage("ERROR: " + QString::fromStdString(ex), 0);
                return;
            }

            Wave wave;
            if (wave.loadWave_Siglent_DSO_1000(raw_wave_input)) {
                this->ui->statusBar->showMessage("ERROR: Waveform data was not found from input.");
                return;
            }

            drawGraph(waveLabel, wave.getWave());
            ui->customPlot->xAxis->setLabel("s");
            ui->customPlot->yAxis->setLabel("V");
            ui->customPlot->replot();
        } else if (buttonlabel == "Wave CH2") {
            QString waveCommand = "C2:WF? ALL";
            QString waveLabel = "Wave CH2";

            std::vector<uint8_t> raw_wave_input;
            try {
                Device device((std::string *) &(this->deviceFile));
                raw_wave_input = device.waveform(waveCommand.toStdString());
            } catch (std::string ex) {
                this->ui->statusBar->showMessage("ERROR: " + QString::fromStdString(ex), 0);
                return;
            }

            Wave wave;
            if (wave.loadWave_Siglent_DSO_1000(raw_wave_input)) {
                this->ui->statusBar->showMessage("ERROR: Waveform data was not found from input.");
                return;
            }

            drawGraph(waveLabel, wave.getWave());
            ui->customPlot->xAxis->setLabel("s");
            ui->customPlot->yAxis->setLabel("V");
            ui->customPlot->replot();
        } else if (buttonlabel == "Spect CH1") {
            QString waveCommand = "C1:WF? ALL";
            QString waveLabel = "Spectrum CH1";

            std::vector<uint8_t> raw_wave_input;
            try {
                Device device((std::string *) &(this->deviceFile));
                raw_wave_input = device.waveform(waveCommand.toStdString());
            } catch (std::string ex) {
                this->ui->statusBar->showMessage("ERROR: " + QString::fromStdString(ex), 0);
                return;
            }

            Wave wave;
            if (wave.loadWave_Siglent_DSO_1000(raw_wave_input)) {
                this->ui->statusBar->showMessage("ERROR: Waveform data was not found from input.");
                return;
            }

            wave.calculateSpectrum();

            drawGraph(waveLabel, wave.getSpectrum());
            ui->customPlot->xAxis->setLabel("Hz");
            ui->customPlot->yAxis->setLabel("dBVrms");
            ui->customPlot->replot();
        } else if (buttonlabel == "Spect CH2") {
            QString waveCommand = "C2:WF? ALL";
            QString waveLabel = "Spectrum CH2";

            std::vector<uint8_t> raw_wave_input;
            try {
                Device device((std::string *) &(this->deviceFile));
                raw_wave_input = device.waveform(waveCommand.toStdString());
            } catch (std::string ex) {
                this->ui->statusBar->showMessage("ERROR: " + QString::fromStdString(ex), 0);
                return;
            }

            Wave wave;
            if (wave.loadWave_Siglent_DSO_1000(raw_wave_input)) {
                this->ui->statusBar->showMessage("ERROR: Waveform data was not found from input.");
                return;
            }

            wave.calculateSpectrum();

            drawGraph(waveLabel, wave.getSpectrum());
            ui->customPlot->xAxis->setLabel("Hz");
            ui->customPlot->yAxis->setLabel("dBVrms");
            ui->customPlot->replot();
        } else {
            this->ui->statusBar->showMessage("BUG!: unknow button???...", 0);
        }
    }
}

void MainWindow::customCommandDeleteClicked() {
    QAction* action = (QAction*) sender();
    if (action != NULL) {
        QString label = action->text();
        // this->ui->statusBar->showMessage("Menu Action " + label + " clicked!", 5000);
        ui->menuDelete_command->removeAction(action);
        delete action;

        for (int c = 0; c < this->customButtons.size(); c++) {
            QPushButton* button = this->customButtons.at(c);
            if (button->text() == label) {
                ui->horizontalLayout->removeWidget(button);
                delete button;
                this->customButtons.removeAt(c);
                this->customButtonLabels.removeAt(c);
                this->customButtonTooltips.removeAt(c);
                this->customButtonUsbtmcCommands.removeAt(c);
                this->customButtonsExpectReply.removeAt(c);
                break;
            }
        }

    }
}

void MainWindow::actionExit() {
    QApplication::quit();
}

void MainWindow::saveSettings() {

    QString settingsFile =  QDir::home().absolutePath() + "/.siglscope.settings";
    QSettings settings(settingsFile, QSettings::NativeFormat);

    settings.setValue("deviceString", this->deviceString);

    QVariantList cclvl;
    foreach(QString label, this->customButtonLabels) cclvl << label;
    settings.setValue("customCommandLabels", cclvl);

    QVariantList ccttvl;
    foreach(QString tooltip, this->customButtonTooltips) ccttvl << tooltip;
    settings.setValue("customCommandTooltips", ccttvl);

    QVariantList ccutcvl;
    foreach(QString usbtmccommand, this->customButtonUsbtmcCommands) ccutcvl << usbtmccommand;
    settings.setValue("customCommandUsbtmcCommands", ccutcvl);

    QVariantList ccervl;
    foreach(int exrpl, this->customButtonsExpectReply) ccervl << exrpl;
    settings.setValue("customCommandExpectReply", ccervl);

    this->ui->statusBar->showMessage("Settings saved...", 0);

}

void MainWindow::selectDevice() {

    this->sdd = new SelectDeviceDialog(this);
    connect(this->sdd, SIGNAL(rejected()), this, SLOT(selectDeviceCancel()));
    connect(this->sdd, SIGNAL(accepted()), this, SLOT(selectDeviceOK()));

    sdd->show();
    sdd->activateWindow();

}

void MainWindow::selectDeviceCancel() {
    disconnect(this->sdd, SIGNAL(rejected()), this, SLOT(selectDeviceCancel()));
    disconnect(this->sdd, SIGNAL(accepted()), this, SLOT(selectDeviceOK()));
    delete this->sdd;
    this->sdd = NULL;
}

void MainWindow::selectDeviceOK() {
    this->deviceString = this->sdd->getSelectedDevice();
    this->findDeviceFileByDeviceString();

    disconnect(this->sdd, SIGNAL(rejected()), this, SLOT(selectDeviceCancel()));
    disconnect(this->sdd, SIGNAL(accepted()), this, SLOT(selectDeviceOK()));
    delete this->sdd;
    this->sdd = NULL;
}

void MainWindow::findDeviceFileByDeviceString() {
    if (this->deviceString == QString()) {
        return;
    }

    QStringList qstl;
    qstl << "usbtmc*";
    QDirIterator it("/dev", qstl, QDir::System, QDirIterator::NoIteratorFlags);

    while (it.hasNext()) {
        QString filename = it.next();

        try {
            std::string devfile = filename.toStdString();
            Device device((std::string *) &devfile);
            std::string errstring;
            std::string idn = device.query("*IDN?", errstring);
            if (errstring.length() != 0) {
                continue;
            } else {
                QString qidn = QString::fromStdString(idn);
                if (qidn == this->deviceString) {
                    this->deviceFile = devfile;
                    return;
                }
            }

        } catch (std::string ex) {
            continue;
        }


    }
}

void MainWindow::loadSettings() {

    QString settingsFile =  QDir::home().absolutePath() + "/.siglscope.settings";
    QSettings settings(settingsFile, QSettings::NativeFormat);

    this->deviceString = settings.value("deviceString").toString();

    QVariantList customButtonLabelsQvl = settings.value("customCommandLabels").toList();
    foreach(QVariant v, customButtonLabelsQvl) {
        this->customButtonLabels << v.toString();
    }

    QVariantList customButtonTooltipsQvl = settings.value("customCommandTooltips").toList();
    foreach(QVariant v, customButtonTooltipsQvl) {
        this->customButtonTooltips << v.toString();
    }

    QVariantList customButtonUsbtmcCommandsQvl = settings.value("customCommandUsbtmcCommands").toList();
    foreach(QVariant v, customButtonUsbtmcCommandsQvl) {
        this->customButtonUsbtmcCommands << v.toString();
    }

    QVariantList customButtonsExpectReplyQvl = settings.value("customCommandExpectReply").toList();
    foreach(QVariant v, customButtonsExpectReplyQvl) {
        this->customButtonsExpectReply << v.toInt();
    }


    for (int c = 0; c < this->customButtonLabels.size(); c++ ) {
        QString label = this->customButtonLabels.at(c);
        QString tooltip = this->customButtonTooltips.at(c);
        addCustomCommandButton(label, tooltip);
    }

}

// from qcustomplot interactions example:

void MainWindow::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
{
  Q_UNUSED(event)
  // Set the plot title by double clicking on it
  bool ok;
  QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
  if (ok)
  {
    title->setText(newTitle);
    ui->customPlot->replot();
  }
}

void MainWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->customPlot->replot();
    }
  }
}

void MainWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->customPlot->replot();
    }
  }
}

void MainWindow::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<ui->customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = ui->customPlot->graph(i);
    QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelected(true);
    }
  }
}

void MainWindow::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::addRandomGraph()
{
  int n = 50; // number of points in graph
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*5;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }

  ui->customPlot->addGraph();
  ui->customPlot->graph()->setName(QString("New graph %1").arg(ui->customPlot->graphCount()-1));
  ui->customPlot->graph()->setData(x, y);
  ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 50)
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  ui->customPlot->graph()->setPen(graphPen);
  ui->customPlot->replot();
}

void MainWindow::removeSelectedGraph()
{
  if (ui->customPlot->selectedGraphs().size() > 0)
  {
    ui->customPlot->removeGraph(ui->customPlot->selectedGraphs().first());
    ui->customPlot->replot();
  }
}

void MainWindow::removeAllGraphs()
{
  ui->customPlot->clearGraphs();
  ui->customPlot->replot();
}

void MainWindow::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (ui->customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
    if (ui->customPlot->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (ui->customPlot->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }

  menu->popup(ui->customPlot->mapToGlobal(pos));
}

void MainWindow::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->customPlot->replot();
    }
  }
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable)
{
  ui->statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
}

