#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Logger.hpp"
#include "SettingsManager.hpp"
#include <QApplication>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QStringList>
#include <QSysInfo>
#include <QWidget>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_MARGIN 10

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    /* Menu bar*/
    void changeSteamFolder(void);
    void changeTF2Folder(void);
    void changeMovieFolder(void);
    void openSteamFolder(void);
    void openTF2Folder(void);
    void openMovieFolder(void);
    void loadDefaultSettings(void);
    void saveSettings(void);
    void about(void);

    /* Settings tab */
    void changeResolution(void);
    void startTF2(void);

private:
    void createActions(void);
    void createMenus(void);
    void printMessage(QMessageBox::Icon icon, const QString &title, const QString &text);

    Logger logger;
    SettingsManager settings;

    /* "Invisible" */
    QFileDialog *fileDialog{nullptr};

    QMenu *fileMenu{nullptr};
    QAction *changeSteamFolderAct{nullptr};
    QAction *changeTF2FolderAct{nullptr};
    QAction *changeMovieFolderAct{nullptr};
    QAction *openSteamFolderAct{nullptr};
    QAction *openTF2FolderAct{nullptr};
    QAction *openMovieFolderAct{nullptr};
    QAction *loadDefaultSettingsAct{nullptr};
    QAction *saveSettingsAct{nullptr};
    QAction *exitAct{nullptr};
    QAction *aboutAct{nullptr};

    QMenu *advancedMenu{nullptr};
    QMenu *helpMenu{nullptr};

    QSysInfo *sysInfo{nullptr};
    QString sysInfoOS;

    QProcess *tf2Process{nullptr};

    /* Seeable on the GUI */
    QTabWidget *tabWidget{nullptr};
    QWidget *tabSettings{nullptr};
    QWidget *tabLog{nullptr};

    QLabel *resolutionLabel{nullptr};
    QComboBox *resolutionBox{nullptr};
    QStringList resolutionBoxItems{"1920x1080", "1280x720"};

    QPushButton *startTF2Button{nullptr};

    QMessageBox *messageBox{nullptr};
};

#endif // MAINWINDOW_HPP
