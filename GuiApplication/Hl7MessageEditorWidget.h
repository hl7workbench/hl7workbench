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

namespace HL7WB
{

class Hl7MessageEditorWidget : public QTextEdit
{
    Q_OBJECT

public:
    explicit Hl7MessageEditorWidget(const QString &plainText,
                                    const QFileInfo &fileInfo,
                                    QWidget *parent = Q_NULLPTR);
    explicit Hl7MessageEditorWidget(int untitledDocumentId = 1,
                                    QWidget *parent = Q_NULLPTR);

    const QFileInfo &fileInfo() const;
    QString fileName() const;
    QString filePath() const;
    bool isCopyAvailable() const;
    bool isRedoAvailable() const;
    bool isUndoAvailable() const;
    int untitledDocumentId() const;

signals:
    void removeUntitledDocumentId(int id);
    void fileNameChanged(QString newFileName);
    void filePathChanged(QString newFilePath);

public slots:
    void removeSelectedText();
    void saveFile();
    void saveFileAs();

private slots:
    void copyAvailableChanged(bool available);
    void redoAvailableChanged(bool available);
    void undoAvailableChanged(bool available);

private:
    void saveTo(const QFileInfo &fileInfo);

    bool m_copyAvailable;
    QFileInfo m_fileInfo;
    bool m_redoAvaiable;
    bool m_undoAvailable;
    int m_untitledDocumentId;
};

} // namespace

#endif // HL7MESSAGEEDITORWIDGET_H
