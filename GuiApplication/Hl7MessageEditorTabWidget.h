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

#ifndef HL7MESSAGEEDITORTABWIDGET_H
#define HL7MESSAGEEDITORTABWIDGET_H

#include <QTabWidget>

class QFileInfo;

namespace HL7WB
{

class Hl7MessageEditorWidget;

class Hl7MessageEditorTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit Hl7MessageEditorTabWidget(QWidget *parent = Q_NULLPTR);

    void closeTab(int index, bool openNewWhenLast);

signals:
    void copyAvailable(bool available);
    void redoAvailable(bool available);
    void viewedFileNameChanged(QString fileName);
    void undoAvailable(bool available);

public slots:
    void closeAllExceptCurrentTab();
    void closeAllTabs();
    void closeCurrentTab();
    void closeTab(int index);
    void copy();
    void copyAvailableChangedInEditor(bool available);
    void currentTabChanged(int index);
    void cut();
    void fileNameChangedInEditor(QString newFileName);
    void filePathChangedInEditor(QString newFilePath);
    void newFile();
    void newTab(Hl7MessageEditorWidget *widget);
    void openFile();
    void openRecentFile();
    void paste();
    void redo();
    void redoAvailableChangedInEditor(bool available);
    void removeSelectedText();
    void removeUntitledDoucmentId(int id);
    void saveFile();
    void saveFileAs();
    void saveAllFiles();
    void selectAll();
    void undo();
    void undoAvailableChangedInEditor(bool available);

protected:
    virtual void showEvent(QShowEvent *e) override;

private:
    void openFile(const QString &filePath);

    Hl7MessageEditorWidget *m_lastEditorWidget;
    QList<int> m_untitledDocumentIds;
};

} // namespace

#endif // HL7MESSAGEEDITORTABWIDGET_H
