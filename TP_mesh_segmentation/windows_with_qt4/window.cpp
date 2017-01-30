#include "window.h"
#include "viewer.h"
#include "scene.h"
#include "options.h"

#include "ui_alpha.h"
#include "ui_options.h"

#include <CGAL/Qt/debug.h>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QTextStream>
#include <QUrl>
#include <QFileDialog>
#include <QSettings>
#include <QHeaderView>
#include <QClipboard>

MainWindow::MainWindow(QWidget* parent)
: CGAL::Qt::DemosMainWindow(parent)
{
	ui = new Ui::MainWindow;
	ui->setupUi(this);

	// default alpha parameter
	m_alpha = 0.2;
	m_angle_max = 0.8;
	m_area_min = 10;
    
	// saves some pointers from ui, for latter use.
	m_pViewer = ui->viewer;
    
	// does not save the state of the viewer 
	m_pViewer->setStateFileName(QString::null);
    
	// accepts drop events
	setAcceptDrops(true);
    
	// setups scene
	m_pScene = new Scene;
	m_pViewer->setScene(m_pScene);
    
	// connects actionQuit (Ctrl+Q) and qApp->quit()
	connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    
	this->addRecentFiles(ui->menuFile, ui->actionQuit);
	connect(this, SIGNAL(openRecentFile(QString)), this, SLOT(open(QString)));
    
	readSettings();
}

MainWindow::~MainWindow()
{
    delete(m_pScene);
	delete ui;
}

void MainWindow::quit()
{
	writeSettings();
	close();
}

void MainWindow::readSettings()
{
	this->readState("MainWindow", Size|State);
}

void MainWindow::writeSettings()
{
	this->writeState("MainWindow");
	std::cerr << "Write setting...done.\n";
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	writeSettings();
	event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
	Q_FOREACH(QUrl url, event->mimeData()->urls()) {
		QString filename = url.toLocalFile();
		if(!filename.isEmpty())
		{
			QTextStream(stderr) << QString("dropEvent(\"%1\")\n").arg(filename);
			open(filename);
		}
	}
	event->acceptProposedAction();
}

void MainWindow::updateViewerBBox(int input_type)
{
	m_pScene->update_bbox(input_type);
	const Bbox bbox = m_pScene->bbox();
	const double xmin = bbox.xmin();
	const double ymin = bbox.ymin();
	const double zmin = bbox.zmin();
	const double xmax = bbox.xmax();
	const double ymax = bbox.ymax();
	const double zmax = bbox.zmax();
	qglviewer::Vec vec_min(xmin, ymin, zmin);
    qglviewer::Vec vec_max(xmax, ymax, zmax);
	m_pViewer->setSceneBoundingBox(vec_min, vec_max);
	m_pViewer->camera()->showEntireScene();
}

void MainWindow::open(QString filename)
{
	QFileInfo fileinfo(filename);
	if(fileinfo.isFile() && fileinfo.isReadable())
	{
		int index = m_pScene->open(filename);
		if(index >= 0)
		{
			QSettings settings;
			settings.setValue("open directory",
                              fileinfo.absoluteDir().absolutePath());
			this->addToRecentFiles(filename);
            
			// update bbox
			updateViewerBBox();
			m_pViewer->update();
		}
	}
}

void MainWindow::open_mesh(const QString& filename)
{
/*	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_pScene->clear();
	m_pScene->load_mesh(filename);
	QApplication::restoreOverrideCursor();
	addToRecentFiles(filename);
	updateViewerBBox();
	m_pViewer->update();*/

	m_pScene->clear();

	QFileInfo fileinfo(filename);
	if (fileinfo.isFile() && fileinfo.isReadable())
	{
		int index = m_pScene->load_mesh(filename);

		if (index >= 0)
		{
			QSettings settings;
			settings.setValue("open directory",
				fileinfo.absoluteDir().absolutePath());
			this->addToRecentFiles(filename);

			// update bbox
			int input_type = 1;
			updateViewerBBox(input_type);
			m_pViewer->update();
			update();
		}
	}

/*	this->actionInit->setEnabled(true);
	on_actionSet_parameters_triggered();//open dialog now for parameters*/
}


void MainWindow::on_actionLoad_mesh_triggered()
{
	QSettings settings;
	QString directory = settings.value("Open directory",
		QDir::current().dirName()).toString();
	QStringList filenames =
		QFileDialog::getOpenFileNames(this,
		tr("Load mesh..."),
		directory,
		"All files (*)");
	if (!filenames.isEmpty()) {
		Q_FOREACH(QString filename, filenames) {
			open_mesh(filename);
		}
	}
}

void MainWindow::setAddKeyFrameKeyboardModifiers(::Qt::KeyboardModifiers m)
{
	m_pViewer->setAddKeyFrameKeyboardModifiers(m);
}

void MainWindow::on_actionLoad_points_triggered()
{
	QSettings settings;
	QString directory = settings.value("Open directory",
                                       QDir::current().dirName()).toString();
	QStringList filenames = 
    QFileDialog::getOpenFileNames(this,
                                  tr("Load point set..."),
                                  directory,
                                  "All files (*)");
	if(!filenames.isEmpty()) {
		Q_FOREACH(QString filename, filenames) {
			open(filename);
		}
	}
}

void MainWindow::on_actionSave_snapshot_triggered()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_pViewer->saveSnapshot(QString("snapshot.png"));
	QApplication::restoreOverrideCursor();
}

// copy snapshot to clipboard
void MainWindow::on_actionCopy_snapshot_triggered()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QClipboard *qb = QApplication::clipboard();
	m_pViewer->makeCurrent();
	m_pViewer->raise();
	QImage snapshot = m_pViewer->grabFrameBuffer(true);
	qb->setImage(snapshot);
	QApplication::restoreOverrideCursor();
}


void MainWindow::on_actionView_points_triggered()
{
	m_pScene->toggle_view_points();
	m_pViewer->update();
}

void MainWindow::on_actionView_edges_triggered()
{
    m_pScene->toggle_view_edges();
    m_pViewer->update();
}

void MainWindow::on_actionParameters_triggered()
{
	Dialog_options dlg;
   
	dlg.set_alpha(m_alpha);
	dlg.set_angle_max(m_angle_max);
	dlg.set_area_min(m_area_min);

	if(dlg.exec() == QDialog::Accepted){
		m_alpha = dlg.get_alpha();
		m_angle_max = dlg.get_angle_max();
		m_area_min = dlg.get_area_min();
	}
}

void MainWindow::on_actionClassification_triggered()
{
	m_pScene->toggle_Classification(m_alpha);
	m_pViewer->update();
}

void MainWindow::on_actionPlane_Extraction_triggered()
{
	m_pScene->toggle_Plane_Extraction(m_angle_max,m_area_min);
	m_pViewer->update();
}


