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


#include "selectdevicedialog.h"
#include "ui_selectdevicedialog.h"
#include "Device.h"

#include <QDirIterator>
#include <vector>
#include <string>
#include <QRadioButton>
#include <QGroupBox>


SelectDeviceDialog::SelectDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDeviceDialog)
{
    ui->setupUi(this);

    listDevices();

}

SelectDeviceDialog::~SelectDeviceDialog()
{
    delete ui;
}

void SelectDeviceDialog::listDevices() {

    QGroupBox *groupBox = new QGroupBox("Found Devices:");
    QVBoxLayout *vbox = new QVBoxLayout;

    QStringList qstl;
    qstl << "usbtmc*";
    QDirIterator it("/dev", qstl, QDir::System, QDirIterator::NoIteratorFlags);

    while (it.hasNext()) {
        QString filename = it.next();

        QString result;
        try {
            std::string devfile = filename.toStdString();
            Device device((std::string *) &devfile);
            std::string errstring;
            std::string idn = device.query("*IDN?", errstring);
            if (errstring.length() != 0) {
                result.append(QString::fromStdString(errstring));
                this->deviceStrings.push_back(QString());
            } else {
                result.append(QString::fromStdString(idn));
                this->deviceStrings.push_back(QString::fromStdString(idn));
            }

        } catch (std::string ex) {
            result.append(QString::fromStdString(ex));
            this->deviceStrings.push_back(QString());
        }

        QRadioButton* qrb = new QRadioButton(filename + ": " + result);
        vbox->addWidget(qrb);

        this->deviceButtons.push_back(qrb);
    }

    groupBox->setLayout(vbox);
    ui->scrollArea->setWidget(groupBox);


}

QString SelectDeviceDialog::getSelectedDevice() {
    for (unsigned int c = 0; c < this->deviceButtons.size(); c++) {
        QRadioButton* qrb = this->deviceButtons.at(c);
        if (qrb->isChecked()) {
            if (this->deviceStrings.at(c) != QString()) {
                return this->deviceStrings.at(c);
            }
        }
    }
    return QString();
}
