#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <CGAL/Qt/DemosMainWindow.h>

class QDragEnterEvent;
class QDropEvent;

class Viewer;
class Scene;

namespace Ui {
	class MainWindow;
}

class MainWindow : public CGAL::Qt::DemosMainWindow
{
	Q_OBJECT
private:
	Ui::MainWindow* ui;

	// parameters
	double m_alpha;
	double m_angle_max;
	double m_area_min;

	Viewer* m_pViewer;
	Scene* m_pScene;
    
public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();
    
    public slots:
	void updateViewerBBox(int input_type = 0);
    void open(QString filename);
	void open_mesh(const QString& filename);
    void setAddKeyFrameKeyboardModifiers(Qt::KeyboardModifiers);
    
    protected slots:    
    // settings
    void quit();
    void readSettings();
    void writeSettings();
    
    // drag & drop
    void dropEvent(QDropEvent *event);
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    
    // file menu
    void on_actionLoad_points_triggered();
	void on_actionLoad_mesh_triggered();
    void on_actionCopy_snapshot_triggered();
    void on_actionSave_snapshot_triggered();
    
   
    // view menu
    void on_actionView_edges_triggered();
    void on_actionView_points_triggered();
    
    // algorithms menu
    void on_actionParameters_triggered();
    void on_actionClassification_triggered();
	void on_actionPlane_Extraction_triggered();
};

#endif // ifndef MAINWINDOW_H
