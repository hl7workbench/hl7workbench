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

#include "Hl7MessageEditorWidget.h"

#include "Hl7GuiCommon.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QStandardPaths>
#include <QTextStream>

Hl7MessageEditorWidget::Hl7MessageEditorWidget(int untitledDocumentId,
                                               QWidget *parent) :
    QTextEdit(parent),
    m_fileInfo(QString("Untitled %1.hl7").arg(untitledDocumentId)),
    m_untitledDocumentId(untitledDocumentId)
{
    QFont f = currentFont();

    setFont(QFont("Ubuntu Mono", f.pointSize()));
}

Hl7MessageEditorWidget::Hl7MessageEditorWidget(const QString &plainText,
                                               const QFileInfo &fileInfo,
                                               QWidget *parent) :
    QTextEdit(parent),
    m_fileInfo(fileInfo),
    m_untitledDocumentId(-1)
{
    QFont f = currentFont();

    setFont(QFont("Ubuntu Mono", f.pointSize()));

    setPlainText(plainText);
}

const QFileInfo &Hl7MessageEditorWidget::fileInfo() const
{
    return m_fileInfo;
}

QString Hl7MessageEditorWidget::fileName() const
{
    return m_fileInfo.fileName();
}

QString Hl7MessageEditorWidget::filePath() const
{
    return m_fileInfo.absoluteFilePath();
}

int Hl7MessageEditorWidget::untitledDocumentId() const
{
    return m_untitledDocumentId;
}

void Hl7MessageEditorWidget::saveFile()
{
    if (-1 != m_untitledDocumentId)
    {
        saveFileAs();
    }
    else
    {
        saveTo(m_fileInfo.filePath());
    }
}

void Hl7MessageEditorWidget::saveFileAs()
{
    QString folder;
    if (-1 == m_untitledDocumentId)
    {
        folder = m_fileInfo.absoluteDir().absolutePath();
    }
    else
    {
        QDir documentsDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));

        if (documentsDir.exists())
        {
            folder = documentsDir.absolutePath();
        }
        else
        {
            folder = QDir::currentPath();
        }
    }

    QFileDialog saveDialog(this,
                           "Save File As",
                           folder,
                           HL7_FILE_FILTER);
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.selectFile(m_fileInfo.fileName());

    if (QDialog::Accepted == saveDialog.exec() &&
            1 == saveDialog.selectedFiles().count())
    {
        saveTo(QFileInfo(QDir(folder).absoluteFilePath(saveDialog.selectedFiles()[0])));
    }
}

void Hl7MessageEditorWidget::saveTo(const QFileInfo &fileInfo)
{
    QFile file(fileInfo.absoluteFilePath());
    if (file.open(QFile::Text | QFile::WriteOnly))
    {
        QTextStream stream(&file);
        QStringList lines = toPlainText().split('\n');
        for (const QString l : lines)
        {
            stream << l << endl;
        }
        stream.flush();
        file.close();

        emit removeUntitledDocumentId(m_untitledDocumentId);
        m_untitledDocumentId = -1;

        m_fileInfo = fileInfo;
        emit fileNameChanged(m_fileInfo.fileName());
        emit filePathChanged(m_fileInfo.absoluteFilePath());
    }
}
