#include "MainWindow.hpp"
#include <QComboBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QGridLayout>
#include <QIcon>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QSysInfo>
#include <filesystem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), logger("lawena.log"), settings("lawena.ini")
{
    this->setWindowTitle("lawena-ng");
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // TODO: this obviously only works when running from build directory
    this->setWindowIcon(QIcon("../data/icons/icon.ico"));

    createActions();
    createMenus();

    messageBox = new QMessageBox(this);

    fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::List);
    fileDialog->setOption(QFileDialog::ShowDirsOnly, true);
    fileDialog->setOption(QFileDialog::DontResolveSymlinks, true);
    fileDialog->setOption(QFileDialog::ReadOnly, true);

    sysInfo = new QSysInfo();
    sysInfoOS = sysInfo->kernelType();

    tf2Process = new QProcess(this);

    tabWidget = new QTabWidget(this);
    tabSettings = new QWidget(this);
    tabLog = new QWidget(this);
    tabWidget->addTab(tabSettings, "Settings");
    tabWidget->addTab(tabLog, "Log");
    tabWidget->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT - fileMenu->height());
    tabWidget->move(0, fileMenu->height());

    resolutionLabel = new QLabel("Resolution: ", tabSettings);
    resolutionLabel->move(0, 50);

    resolutionBox = new QComboBox(tabSettings);
    resolutionBox->move(resolutionLabel->width() + WINDOW_MARGIN, resolutionLabel->height());
    resolutionBox->addItems(resolutionBoxItems);
    resolutionBox->setCurrentIndex(0);
    connect(resolutionBox, &QComboBox::currentIndexChanged, this, &MainWindow::changeResolution);

    startTF2Button = new QPushButton("Start TF2", tabSettings);
    startTF2Button->setFixedSize(84, 34);
    // fix this, shouldn't have to hardcode in '-25'
    startTF2Button->move(tabWidget->width() - (startTF2Button->width() + WINDOW_MARGIN),
                         tabWidget->height() - (startTF2Button->height() + WINDOW_MARGIN) - 25);
    connect(startTF2Button, &QPushButton::clicked, this, &MainWindow::startTF2);
}

void MainWindow::createActions(void)
{
    changeSteamFolderAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::FolderNew), "Change Steam folder...", this);
    connect(changeSteamFolderAct, &QAction::triggered, this, &MainWindow::changeSteamFolder);

    changeTF2FolderAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::FolderNew), "Change TF2 folder...", this);
    connect(changeTF2FolderAct, &QAction::triggered, this, &MainWindow::changeTF2Folder);

    changeMovieFolderAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::FolderNew), "Change movie folder...", this);
    connect(changeMovieFolderAct, &QAction::triggered, this, &MainWindow::changeMovieFolder);

    openSteamFolderAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen), "Open Steam folder", this);
    connect(openSteamFolderAct, &QAction::triggered, this, &MainWindow::openSteamFolder);

    openTF2FolderAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen), "Open TF2 folder", this);
    connect(openTF2FolderAct, &QAction::triggered, this, &MainWindow::openTF2Folder);

    openMovieFolderAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen), "Open movie folder", this);
    connect(openMovieFolderAct, &QAction::triggered, this, &MainWindow::openMovieFolder);

    loadDefaultSettingsAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ViewRefresh), "Load default settings");
    connect(loadDefaultSettingsAct, &QAction::triggered, this, &MainWindow::loadDefaultSettings);

    saveSettingsAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave), "Save settings");
    saveSettingsAct->setShortcut(QKeySequence::Save);
    connect(saveSettingsAct, &QAction::triggered, this, &MainWindow::saveSettings);

    exitAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit), "Exit", this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &QApplication::quit);

    aboutAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout), "About", this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus(void)
{
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(changeSteamFolderAct);
    fileMenu->addAction(changeTF2FolderAct);
    fileMenu->addAction(changeMovieFolderAct);
    fileMenu->addSeparator();
    fileMenu->addAction(openSteamFolderAct);
    fileMenu->addAction(openTF2FolderAct);
    fileMenu->addAction(openMovieFolderAct);
    fileMenu->addSeparator();
    fileMenu->addAction(loadDefaultSettingsAct);
    fileMenu->addAction(saveSettingsAct);
    fileMenu->addSeparator();

    fileMenu->addAction(exitAct);

    advancedMenu = menuBar()->addMenu("Advanced");

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAct);
}

void MainWindow::printMessage(QMessageBox::Icon icon, const QString &title, const QString &text)
{
    messageBox->setIcon(icon);
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    messageBox->button(QMessageBox::Ok);
    messageBox->exec();
}

void MainWindow::changeSteamFolder(void)
{
    const QString steamFolder = fileDialog->getExistingDirectory();
    if (!steamFolder.isEmpty())
    {
        settings.setSteamDir(steamFolder);
    }
}

void MainWindow::changeTF2Folder(void)
{
    const QString tf2Folder = fileDialog->getExistingDirectory();
    if (!tf2Folder.isEmpty())
    {
        settings.setTfDir(tf2Folder);
    }
}

void MainWindow::changeMovieFolder(void)
{
    const QString movieFolder = fileDialog->getExistingDirectory();
    if (!movieFolder.isEmpty())
    {
        settings.setMovieDir(movieFolder);
    }
}

void MainWindow::openSteamFolder(void)
{
    const QString steamDir = QString::fromStdString(settings.getSteamDir());

    if (steamDir.isEmpty())
    {
        printMessage(QMessageBox::Warning, "Warning", "Failed to open Steam folder:\nnot defined!");
        return;
    }

    const QUrl directoryUrl = QUrl::fromLocalFile(steamDir);

    QDesktopServices::openUrl(directoryUrl);
}

void MainWindow::openTF2Folder(void)
{
    const QString tfDir = QString::fromStdString(settings.getTfDir());

    if (tfDir.isEmpty())
    {
        printMessage(QMessageBox::Warning, "Warning", "Failed to open TF2 folder:\nnot defined!");
        return;
    }

    const QUrl directoryUrl = QUrl::fromLocalFile(tfDir);
}

void MainWindow::openMovieFolder(void)
{
    const QString movieDir = QString::fromStdString(settings.getMovieDir());

    if (movieDir.isEmpty())
    {
        printMessage(QMessageBox::Warning, "Warning", "Failed to open movie folder:\nnot defined!");
        return;
    }

    const QUrl directoryUrl = QUrl::fromLocalFile(movieDir);
}

void MainWindow::loadDefaultSettings(void)
{
    settings.loadDefaults();
    // TODO: redraw everything in the gui
}

void MainWindow::saveSettings(void)
{
    ;
    settings.saveToFile();
}

void MainWindow::about()
{
    ;
    printMessage(QMessageBox::Information, "About", "Version 0.0.1\nBlah blah blah...");
}

void MainWindow::changeResolution(void)
{
    /* Get the width and height */
    const QStringList result = resolutionBox->currentText().split('x');

    if (result.size() != 2)
    {
        // TODO: print error message
        return;
    }

    settings.setWidth(result[0]);
    settings.setHeight(result[1]);
}

void MainWindow::startTF2()
{
    /* TODO: expand and move this logic into CommandLine class */

    /* Check if Steam directory exists, otherwise there's no point in trying to launch */
    const std::string steamDir = settings.getSteamDir();
    if (!std::filesystem::exists(steamDir) || !std::filesystem::is_directory(steamDir))
    {
        printMessage(
            QMessageBox::Warning, "Refusing to launch TF2",
            "Steam directory isn't valid!\nIt's either not defined (check settings) or it doesn't exist on disk");
        return;
    }

    /* Check if TF2 directory exists, otherwise there's no point in trying to launch */
    const std::string tfDir = settings.getTfDir();

    if (!std::filesystem::exists(tfDir) || !std::filesystem::is_directory(tfDir))
    {
        printMessage(
            QMessageBox::Warning, "Refusing to launch TF2",
            "TF2 directory isn't valid!\nIt's either not defined (check settings) or it doesn't exist on disk");
        return;
    }

    /* Build platform-specific launcher */
    QString program;
    QStringList arguments;

    if (sysInfoOS == "linux")
    {
        /*
        program = QString::fromStdString(steamDir) + "/ubuntu12_64/" + "/steam-runtime-sniper/" + "/run " +
                  QString::fromStdString(tfDir + "/../tf2.sh -- ");
        arguments << QString::fromStdString(settings.getLaunchOptions());
        */
        program = "steam";
        arguments << "steam://rungameid/440" << "-novid" << "-console"; // launch options are borke
    } else
    {
        printMessage(QMessageBox::Warning, "Windows not supported yet", "Windows is not supported yet");
        return;
    }

    tf2Process->start(program, arguments);
}
