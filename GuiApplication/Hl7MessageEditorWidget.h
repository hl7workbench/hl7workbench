/*
 * This file is part of the HL7 Workbench project.
 *
 * Copyright (C) 2019  Individual HL7 Workbench contributors.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HL7MESSAGEEDITORWIDGET_H
#define HL7MESSAGEEDITORWIDGET_H

#include <QTextEdit>
#include <QFileInfo>

class Hl7MessageEditorWidget : public QTextEdit
{
    Q_OBJECT

public:
    explicit Hl7MessageEditorWidget(int untitledDocumentId = 1,
                                    QWidget *parent = Q_NULLPTR);
    explicit Hl7MessageEditorWidget(const QString &fileName,
                                    QWidget *parent = Q_NULLPTR);

    QString fileName() const;
    int untitledDocumentId() const;

signals:
    void removeUntitledDocumentId(int id);
    void fileNameChanged(QString newFileName);

public slots:
    void saveFile();
    void saveFileAs();

private:
    void saveTo(const QFileInfo &fileInfo);

    QFileInfo m_fileInfo;
    int m_untitledDocumentId;
};

#endif // HL7MESSAGEEDITORWIDGET_H
