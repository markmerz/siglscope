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

#include "addcommanddialog.h"
#include "ui_addcommanddialog.h"
#include "constants.h"

AddCommandDialog::AddCommandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCommandDialog)
{
    ui->setupUi(this);    

}

AddCommandDialog::~AddCommandDialog()
{
    delete ui;
}

void AddCommandDialog::clearTextFields() {
    ui->labelText->setText("");
    ui->tooltipText->setText("");
    ui->usbtmccommandText->setText("");
    // ui->expectReply->setChecked(false);
}

QString AddCommandDialog::getLabelText() {
    return ui->labelText->text();
}

QString AddCommandDialog::getTooltipText() {
    return ui->tooltipText->text();
}

QString AddCommandDialog::getUsbtmccommandText() {
    return ui->usbtmccommandText->text();

}

int AddCommandDialog::getExpectReply() {
    if (ui->expectNoReply->isChecked()) {
        return EXPECT_NOREPLY;
    } else if (ui->expectOneLiner->isChecked()) {
        return EXPECT_ONELINER;
    } else {
        return EXPECT_NEWWINDOW;
    }
}
