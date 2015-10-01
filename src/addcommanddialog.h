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


#ifndef ADDCOMMANDDIALOG_H
#define ADDCOMMANDDIALOG_H

#include <QDialog>

namespace Ui {
class AddCommandDialog;
}

class AddCommandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCommandDialog(QWidget *parent = 0);
    ~AddCommandDialog();

    void clearTextFields();

    QString getLabelText();
    QString getTooltipText();
    QString getUsbtmccommandText();
    int getExpectReply();

private:
    Ui::AddCommandDialog *ui;


};

#endif // ADDCOMMANDDIALOG_H
