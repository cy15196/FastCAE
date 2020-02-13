#include "MainWindowPy.h"
#include <QDebug>
#include <assert.h>
#include "mainWindow.h"
#include "signalHandler.h"
#include "SubWindowManager.h"
#include "python/PyAgent.h"
#include "PostWidgets/Post3DInterface.h"
#include "PostWidgets/Post3DWidget.h"
#include <QStringList>
#include <vtkIdTypeArray.h>
#include "meshData/meshSingleton.h"
#include "meshData/meshSet.h"
#include "meshData/setMember.h"
#include "GeometryCommand/GeoCommandList.h"
namespace GUI
{

	MainWindow* MainWindowPy::_mainWindow = nullptr;
	SignalHandler* MainWindowPy::_signalHander = nullptr;
	SubWindowManager* MainWindowPy::_subWindowManager = nullptr;
	Py::PythonAagent* MainWindowPy::_pyAgent = nullptr;

	/*void MainWindowPy::showFastCAE()
	{

	}*/

	void MainWindowPy::undo()
	{
		Command::GeoComandList::getInstance()->undo();
	}

	void MainWindowPy::redo()
	{
		Command::GeoComandList::getInstance()->redo();
	}

	void MainWindowPy::init(GUI::MainWindow* m, GUI::SignalHandler* sg)
	{
		_mainWindow = m;
		_signalHander = sg;
		_subWindowManager = _mainWindow->getSubWindowManager();
		_pyAgent = Py::PythonAagent::getInstance();
	}

	void MainWindowPy::importMesh(char* f)
	{
		QString file(f);
		QStringList fl = file.split(",");
		emit _signalHander->importMeshPySig(fl);
		//_pyAgent->unLock();

	}

	void MainWindowPy::exportMesh(char* f)
	{
		QString file(f);
		emit _signalHander->exportMeshPySig(file);
	}

	void MainWindowPy::importGeometry(char* f)
	{
		QString file(f);
		QStringList fl = file.split(",");
		emit _mainWindow->importGeometrySig(fl);
		//_pyAgent->unLock();
	}

	void MainWindowPy::exportGeometry(char* f)
	{
		QString file(f);
		emit _mainWindow->exportGeometrySig(file);
		//_pyAgent->unLock();
	}

	void MainWindowPy::openProjectFile(char* f)
	{
		QString file(f);

		emit _signalHander->openProjectFileSig(file);
		//_pyAgent->unLock();
	}
	
	void MainWindowPy::saveProjectFile(char* f)
	{
		QString file(f);
		 emit _signalHander->saveToProjectFileSig(file);
		//_pyAgent->unLock();
	}
	void MainWindowPy::openPost2D()
	{
		emit _signalHander->open2DPlotWindowPySig();
		//_pyAgent->unLock();
	}
	void MainWindowPy::openPost3D()
	{
		emit _signalHander->open3DGraphWindowPySig();
		
	}
	void MainWindowPy::openPreWindow()
	{
		emit _subWindowManager->openPreWindowSig();
	}

	void MainWindowPy::saveImage(int w, int h, int id, char* win, char* file)
	{
		QString wi(win);
		QString f(file);
		emit _subWindowManager->saveImageSig(w, h, id, wi, f);
		//_pyAgent->unLock();
	}
	
	void MainWindowPy::setView(int id,char* win, char* view)
	{
		QString wi(win);
		QString vi(view);
		emit _subWindowManager->setViewSig(id, wi, vi);
//		_pyAgent->unLock();
	}
	
	void MainWindowPy::setViewRandValue(int id, char*win, int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3)
	{
		QString wi(win);
		emit _subWindowManager->setViewValueSig(id,wi,x1,x2,x3,y1,y2,y3,z1,z2,z3);
		//_pyAgent->unLock();
	}
	void MainWindowPy::quit()
	{
		_subWindowManager->closeAllSubWindow();
		_signalHander->clearData();
		_mainWindow->close();
	}

	void MainWindowPy::solveProject(int projectIndex, int solverIndex)
	{
		emit _signalHander->solveProjectSig(projectIndex, solverIndex);
		//_pyAgent->unLock();
	}

	void MainWindowPy::script_openFile(int id, char* type, char* file)
	{
		QString stype(type);
		QString sfile(file);
		qDebug() << "sfile"<<sfile;
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
	//	w->openFile(sfile);
		emit w->openFileSig(sfile,false);
	}

	void MainWindowPy::script_applyClicked(int id, char* type)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->applyClickSig();

	}

	void MainWindowPy::script_Properties_Opacity(int id, char* type, int obj_id, double mOpacity)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_OpacitySig(obj_id, mOpacity);

	}

	void MainWindowPy::script_Properties_colorColumn(int id, char* type, int obj_id, char* mColorColumnStyle)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_colorColumnSig(obj_id,mColorColumnStyle);
	}

	void MainWindowPy::script_Properties_scalarBarTitle(int id, char* type, int obj_id, char* colName, char* m_title)
	{
		QString stype(type);
		QString scolName(colName);
		QString sm_title(m_title);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_scalarBarTitleSig(obj_id, scolName, sm_title);

	}
	void MainWindowPy::script_Properties_scalarBarFontSize(int id, char* type, int obj_id, char* colName, int m_fontSize)
	{
		QString stype(type);
		QString scolName(colName);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_scalarBarFontSizeSig(obj_id, scolName, m_fontSize);
	}

	void MainWindowPy::script_Properties_scalarBarNumLables(int id, char* type, int obj_id, char* colName, int m_numLables)
	{
		QString stype(type);
		QString scolName(colName);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_scalarBarNumLablesSig(obj_id, scolName, m_numLables);

	}

	void MainWindowPy::script_Properties_lineWidth(int id, char* type, int obj_id, int mLineWidth)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_lineWidthSig(obj_id, mLineWidth);
	}

	void MainWindowPy::script_Properties_pointSize(int id, char* type, int obj_id, int mPointSize)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_pointSizeSig(obj_id, mPointSize);
	}

	void MainWindowPy::script_Properties_translate(int id, char* type, int obj_id, double x, double y, double z)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_translateSig(obj_id, x, y, z);
	}

	void MainWindowPy::script_Properties_origin(int id, char* type, int obj_id, double x, double y, double z)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_originSig(obj_id, x, y, z);
	}

	void MainWindowPy::script_Properties_scale(int id, char* type, int obj_id, double x, double y, double z)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_scaleSig(obj_id, x, y, z);
	}

	void MainWindowPy::script_Properties_orientation(int id, char* type, int obj_id, double x, double y, double z)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_orientationSig(obj_id, x, y, z);
	}

	void MainWindowPy::script_Properties_representation(int id, char* type, int obj_id, int m_enum_representationtype)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_representationSig(obj_id, m_enum_representationtype);
	}

	void MainWindowPy::script_Properties_specular(int id, char* type, int obj_id, double mSpecular)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_specularSig(obj_id, mSpecular);
	}
	///////////////////
	void MainWindowPy::script_Properties_diffuse(int id, char* type, int obj_id, double mDiffuse)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_diffuseSig(obj_id, mDiffuse);
	}

	void MainWindowPy::script_Properties_ambient(int id, char* type, int obj_id, double mAmbient)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_ambientSig(obj_id, mAmbient);
	}

	void MainWindowPy::script_Properties_specularPower(int id, char* type, int obj_id, int mSpecularPower)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_specularPowerSig(obj_id, mSpecularPower);
	}

	void MainWindowPy::script_Properties_specularColor(int id, char* type, int obj_id, int r, int g, int b)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_specularColorSig(obj_id, r, g, b);
	}

	void MainWindowPy::script_Properties_solidColor(int id, char* type, int obj_id, int r, int g, int b)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_solidColorSig(obj_id, r, g, b);
	}

	void MainWindowPy::script_Properties_edgeColor(int id, char* type, int obj_id, int r, int g, int b)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_edgeColorSig(obj_id, r, g, b);
	}

	void MainWindowPy::script_Properties_interpolation(int id, char* type, int obj_id, int m_enum_interpolationtype)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_interpolationSig(obj_id, m_enum_interpolationtype);
	}

	void MainWindowPy::script_Properties_Flag_scalarBar(int id, char* type, int obj_id, char* mColorColumnStyle)
	{
		QString stype(type);
		QString smColorColumnStyle(mColorColumnStyle);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_Flag_scalarBarSig(obj_id, smColorColumnStyle);
	}

	void MainWindowPy::script_Properties_EnableOpacityMap(int id, char* type, int obj_id, bool val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_EnableOpacityMapSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_visible(int id, char* type, int obj_id, bool flag_show_actors)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_visibleSig(obj_id, flag_show_actors);
	}

	void MainWindowPy::script_Properties_show_scalarBars(int id, char* type, int obj_id, bool mScalarBarVisible)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_show_scalarBarsSig(obj_id, mScalarBarVisible);
	}

	void MainWindowPy::script_Properties_show_cubeAxes(int id, char* type, int obj_id, bool flag_cubeAxes)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_show_cubeAxesSig(obj_id, flag_cubeAxes);
	}

	void MainWindowPy::script_Properties_scalarBarPosition(int id, char* type, int obj_id, char* colName, int tep_orietation, double pos0, double pos1, double pos2, double pos3)
	{
		QString stype(type);
		QString scolName(colName);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_scalarBarPositionSig(obj_id, scolName, tep_orietation, pos0, pos1, pos2, pos3);
	}

	void MainWindowPy::script_FilterClip(int id, char* type, int obj_id)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->FilterClipSig(obj_id);
	}

	void MainWindowPy::script_FilterSlice(int id, char* type, int obj_id)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->FilterSliceSig(obj_id);
	}

	void MainWindowPy::script_FilterContour(int id, char* type, int obj_id)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->FilterContourSig(obj_id);
	}

	void MainWindowPy::script_FilterVector(int id, char* type, int obj_id)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->FilterVectorSig(obj_id);
	}

	void MainWindowPy::script_FilterReflection(int id, char* type, int obj_id)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->FilterReflectionSig(obj_id);
	}

	void MainWindowPy::script_FilterSmooth(int id, char* type, int obj_id)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->FilterSmoothSig(obj_id);
	}

	void MainWindowPy::script_FilterStreamLine(int id, char* type, int obj_id)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->FilterStreamLineSig(obj_id);
	}

	void MainWindowPy::script_Properties_vector_GlyphVector(int id, char* type, int obj_id, char* val)
	{
		QString stype(type);
		QString sval(val);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_GlyphVectorSig(obj_id,sval);
	}

	void MainWindowPy::script_Properties_vector_scalar(int id, char* type, int obj_id, char* val)
	{
		QString stype(type);
		QString sval(val);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_scalarSig(obj_id, sval);
	}

	void MainWindowPy::script_Properties_vector_normal(int id, char* type, int obj_id, char* val)
	{
		QString stype(type);
		QString sval(val);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_normalSig(obj_id, sval);
	}

	void MainWindowPy::script_Properties_vector_numPoints(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_numPointsSig(obj_id,val);
	}

	void MainWindowPy::script_Properties_vector_glyph_type(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_glyph_typeSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_vector_glyph_tipRes(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_glyph_tipResSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_vector_glyph_tipRad(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_glyph_tipRadSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_vector_glyph_tipLen(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_glyph_tipLenSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_vector_glyph_shaftRes(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_glyph_shaftResSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_vector_glyph_shaftRad(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_vector_glyph_shaftRadSig(obj_id, val);
	}
	//////////////////////////////
	void MainWindowPy::script_Properties_view_backgroundType(int id, char* type, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_view_backgroundTypedSig(val);
	}

	void MainWindowPy::script_Properties_view_backgroundColor(int id, char* type, int red, int green, int blue)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_view_backgroundColorSig(red, green, blue);
	}

	void MainWindowPy::script_Properties_view_background2Color(int id, char* type, int red, int green, int blue)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_view_background2ColorSig(red, green, blue);
	}

	void MainWindowPy::script_Properties_view_axesVisible(int id, char* type, int a)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_view_axesVisibleSig(a);
	}

	void MainWindowPy::script_Properties_view_cameraParallel(int id, char* type, int a)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_view_cameraParallelSig(a);
	}

	void MainWindowPy::script_Properties_view_interaction(int id, char* type, int a)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_view_interactionSig(a);
	}

	void MainWindowPy::script_Properties_renderView(int id, char* type)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_renderViewSig();
	}

	void MainWindowPy::script_Camera_Position(int id, char* type, double pos0, double pos1, double pos2)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Camera_PositionSig(pos0, pos1, pos2);
	}

	void MainWindowPy::script_Camera_FocalPoint(int id, char* type, double focalPoint0, double focalPoint1, double focalPoint2)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Camera_FocalPointSig(focalPoint0, focalPoint1, focalPoint2);
	}

	void MainWindowPy::script_Camera_ClippingRange(int id, char* type, double clippingRange0, double clippingRange1)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Camera_ClippingRangeSig(clippingRange0, clippingRange1);
	}

	void MainWindowPy::script_Camera_ViewUp(int id, char* type, double viewup0, double viewup1, double viewup2)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Camera_ViewUpSig(viewup0, viewup1, viewup2);
	}

	void MainWindowPy::script_Camera_ViewAngle(int id, char* type, double angle)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Camera_ViewAngleSig(angle);
	}

	void MainWindowPy::script_Camera_Zoom(int id, char* type, double zoom)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Camera_ZoomSig(zoom);
	}

	void MainWindowPy::script_Camera_Reset(int id, char* type)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Camera_ResetSig();
	}

	void MainWindowPy::script_Properties_planeOrigin(int id, char* type, int obj_id, double x, double y, double z)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_planeOriginSig(obj_id, x, y, z);
	}

	void MainWindowPy::script_Properties_planeNormal(int id, char* type, int obj_id, double x, double y, double z)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_planeNormalSig(obj_id, x, y, z);
	}

	void MainWindowPy::script_Properties_planeVisible(int id, char* type, int obj_id, int a)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_planeVisibleSig(obj_id, a);
	}

	void MainWindowPy::script_Properties_insideOut(int id, char* type, int obj_id, int a)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_insideOutSig(obj_id, a);
	}

	void MainWindowPy::script_Properties_contourColumn(int id, char* type, int obj_id, char* val)
	{
		QString stype(type);
		QString sval(val);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_contourColumnSig(obj_id, sval);
	}

	void MainWindowPy::script_Properties_contourValue(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_contourValueSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_contour_reflection(int id, char* type, int obj_id, int aaa)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_contour_reflectionSig(obj_id, aaa);
	}

	void MainWindowPy::script_Properties_contour_reflectionAxes(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_contour_reflectionAxesSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_reflectionAxes(int id, char* type, int obj_id, int reflection_axis)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_reflectionAxesSig(obj_id, reflection_axis);
	}

	void MainWindowPy::script_Properties_smooth(int id, char* type, int obj_id,int smotype, double coef)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_smoothSig(obj_id, smotype, coef);
	}
	////////////////////////////////
	void MainWindowPy::script_Properties_streamline_vector(int id, char* type, int obj_id, char* val)
	{
		QString stype(type);
		QString sval(val);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_vectorSig(obj_id, sval);
	}

	void MainWindowPy::script_Properties_streamline_integration_direction(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_integration_directionSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_integration_type(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_integration_typeSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_integration_stepUnit(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_integration_stepUnitSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_integration_initStepLen(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_integration_initStepLenSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_integration_miniStepLen(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_integration_miniStepLenSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_integration_maxiStepLen(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_integration_maxiStepLenSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_stream_maxiSteps(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_stream_maxiStepsSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_stream_maxiStreamLen(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_stream_maxiStreamLenSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_stream_terminalSpeed(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_stream_terminalSpeedSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_stream_maxiError(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_stream_maxiErrorSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_seeds_type(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_seeds_typeSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_seeds_mPoint(int id, char* type, int obj_id, double val0, double val1, double val2)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_seeds_mPointSig(obj_id, val0, val1, val2);
	}

	void MainWindowPy::script_Properties_streamline_seeds_num_points(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_seeds_num_pointsSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_seeds_radius(int id, char* type, int obj_id, double val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_seeds_radiusSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_vorticity(int id, char* type, int obj_id, bool val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_vorticitySig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_interpolatorType(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_interpolatorTypeSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_surface_streamLines(int id, char* type, int obj_id, bool val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_surface_streamLinesSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_reflection(int id, char* type, int obj_id, bool val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_reflectionSig(obj_id, val);
	}

	void MainWindowPy::script_Properties_streamline_reflectionAxes(int id, char* type, int obj_id, int val)
	{
		QString stype(type);
		ModuleBase::GraphWindowBase* gb = _subWindowManager->getWindowByTypeID(stype, id);
		if (gb == nullptr) return;
		Post::Post3DWindowInterface* p3d = dynamic_cast<Post::Post3DWindowInterface*>(gb);
		if (p3d == nullptr) return;
		Post::Post3DWindow* w = p3d->getWindow();
		if (w == nullptr) return;
		emit w->Properties_streamline_reflectionAxesSig(obj_id, val);
	}

	void MainWindowPy::createSet(char* name, char* type, char* idstring)
	{
		QString cname(name);
		QString cidstring(idstring);
		MeshData::SetType settype = MeshData::MeshSet::stringToSettype(type);

		QStringList strlist = cidstring.simplified().split(";");
		MeshData::MeshSet* s = new MeshData::MeshSet(cname, settype);
		for (QString idstring : strlist)
		{
			QStringList  kids = idstring.split(":");
			int ncount = kids.size();
			if (kids.size() < 2) continue;
			bool ok = false;
			const int kid = kids.at(0).toInt(&ok);
			if (!ok) continue;
			kids = kids.at(1).split(" ");
			ncount = kids.size();
			for (int i = 0; i < ncount; ++i)
			{
				int id = kids.at(i).toInt(&ok);
				if (!ok) continue;
				s->appendMember(kid, id);
			}
		}
		
		s->generateDisplayDataSet();
		MeshData::MeshData*  _meshData = MeshData::MeshData::getInstance();
		_meshData->appendMeshSet(s);
		emit _mainWindow->updateSetTreeSig();
	}



}

void importMesh(char* f)
{
	GUI::MainWindowPy::importMesh(f);
}

void exportMesh(char* f)
{
	GUI::MainWindowPy::exportMesh(f);
}

void importGeometry(char* f)
{
	GUI::MainWindowPy::importGeometry(f);
}

void exportGeometry(char* f)
{
	GUI::MainWindowPy::exportGeometry(f);
}


void openProjectFile(char* f)
{
	GUI::MainWindowPy::openProjectFile(f);
}

void saveProjectFile(char* f)
{
	GUI::MainWindowPy::saveProjectFile(f);
}

void saveImage(int w, int h, int id, char* win, char* file)
{
	GUI::MainWindowPy::saveImage(w,h,id,win,file);
}
void setView(int id ,char* win,char* file)
{
    GUI::MainWindowPy::setView(id, win, file);
}
void setViewRandValue(int id, char*win, int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3)
{
	GUI::MainWindowPy::setViewRandValue(id, win, x1, x2, x3, y1, y2, y3, z1, z2, z3);
}
//void setViewPostValue(int id, char*win, int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3)
//{
//	GUI::MainWindowPy::setViewPostValue(id, win,x1,x2,x3,y1,y2,y3,z1,z2,z3);
//}
void quit()
{
	GUI::MainWindowPy::quit();
}
void openPost3D()
{
	GUI::MainWindowPy::openPost3D();
}
void openPost2D()
{
	GUI::MainWindowPy::openPost2D();
}
void openPreWindow()
{
	GUI::MainWindowPy::openPreWindow();
}

void solveProject(int projectIndex, int solverIndex)
{
	GUI::MainWindowPy::solveProject(projectIndex,solverIndex);
}

void MAINWINDOWAPI script_openFile(int id, char* type, char* file)
{
	GUI::MainWindowPy::script_openFile(id, type, file);
}

void MAINWINDOWAPI script_applyClicked(int id, char* type)
{
	GUI::MainWindowPy::script_applyClicked(id, type);
}

void MAINWINDOWAPI createSet(char* name, char* type, char* idstring)
{
	GUI::MainWindowPy::createSet(name, type, idstring);
}

void MAINWINDOWAPI script_Properties_Opacity(int id, char* type, int obj_id, double mOpacity)
{
	GUI::MainWindowPy:: script_Properties_Opacity(id, type, obj_id, mOpacity);
}

void MAINWINDOWAPI script_Properties_colorColumn(int id, char* type, int obj_id, char* mColorColumnStyle)
{
	GUI::MainWindowPy::script_Properties_colorColumn(id, type, obj_id, mColorColumnStyle);
}

void MAINWINDOWAPI script_Properties_scalarBarTitle(int id, char* type, int obj_id, char* colName, char* m_title)
{
	GUI::MainWindowPy::script_Properties_scalarBarTitle(id, type, obj_id, colName, m_title);
}

void MAINWINDOWAPI script_Properties_scalarBarFontSize(int id, char* type, int obj_id, char* colName, int m_fontSize)
{
	GUI::MainWindowPy::script_Properties_scalarBarFontSize(id, type, obj_id, colName, m_fontSize);
}

void MAINWINDOWAPI script_Properties_scalarBarNumLables(int id, char* type, int obj_id, char* colName, int m_numLables)
{
	GUI::MainWindowPy::script_Properties_scalarBarNumLables(id, type, obj_id, colName, m_numLables);
}

void MAINWINDOWAPI script_Properties_lineWidth(int id, char* type, int obj_id, int mLineWidth)
{
	GUI::MainWindowPy::script_Properties_lineWidth(id, type, obj_id, mLineWidth);
}

void MAINWINDOWAPI script_Properties_pointSize(int id, char* type, int obj_id, int mPointSize)
{
	GUI::MainWindowPy::script_Properties_pointSize(id, type, obj_id, mPointSize);
}


void MAINWINDOWAPI script_Properties_translate(int id, char* type, int obj_id, double x, double y, double z)
{
	GUI::MainWindowPy::script_Properties_translate(id, type, obj_id, x, y, z);
}

void MAINWINDOWAPI script_Properties_origin(int id, char* type, int obj_id, double x, double y, double z)
{
	GUI::MainWindowPy::script_Properties_origin(id, type, obj_id, x, y, z);
}

void MAINWINDOWAPI script_Properties_scale(int id, char* type, int obj_id, double x, double y, double z)
{
	GUI::MainWindowPy::script_Properties_scale(id, type, obj_id, x, y, z);
}

void MAINWINDOWAPI script_Properties_orientation(int id, char* type, int obj_id, double x, double y, double z)
{
	GUI::MainWindowPy::script_Properties_orientation(id, type, obj_id, x, y, z);
}

void MAINWINDOWAPI script_Properties_representation(int id, char* type, int obj_id, int m_enum_representationtype)
{
	GUI::MainWindowPy::script_Properties_representation(id, type, obj_id, m_enum_representationtype);
}

void MAINWINDOWAPI script_Properties_specular(int id, char* type, int obj_id, double mSpecular)
{
	GUI::MainWindowPy::script_Properties_specular(id, type, obj_id, mSpecular);
}
//////////////////
void MAINWINDOWAPI script_Properties_diffuse(int id, char* type, int obj_id, double mDiffuse)
{
	GUI::MainWindowPy::script_Properties_diffuse(id, type, obj_id, mDiffuse);
}

void MAINWINDOWAPI script_Properties_ambient(int id, char* type, int obj_id, double mAmbient)
{
	GUI::MainWindowPy::script_Properties_ambient(id, type, obj_id, mAmbient);
}

void MAINWINDOWAPI script_Properties_specularPower(int id, char* type, int obj_id, int mSpecularPower)
{
	GUI::MainWindowPy::script_Properties_specularPower(id, type, obj_id, mSpecularPower);
}

void MAINWINDOWAPI script_Properties_specularColor(int id, char* type, int obj_id, int r, int g, int b)
{
	GUI::MainWindowPy::script_Properties_specularColor(id, type, obj_id, r, g, b);
}

void MAINWINDOWAPI script_Properties_solidColor(int id, char* type, int obj_id, int r, int g, int b)
{
	GUI::MainWindowPy::script_Properties_solidColor(id, type, obj_id, r, g, b);
}

void MAINWINDOWAPI script_Properties_edgeColor(int id, char* type, int obj_id, int r, int g, int b)
{
	GUI::MainWindowPy::script_Properties_edgeColor(id, type, obj_id, r, g, b);
}

void MAINWINDOWAPI script_Properties_interpolation(int id, char* type, int obj_id, int m_enum_interpolationtype)
{
	GUI::MainWindowPy::script_Properties_interpolation(id, type, obj_id, m_enum_interpolationtype);
}

void MAINWINDOWAPI script_Properties_Flag_scalarBar(int id, char* type, int obj_id, char* mColorColumnStyle)
{
	GUI::MainWindowPy::script_Properties_Flag_scalarBar(id, type, obj_id, mColorColumnStyle);
}

void MAINWINDOWAPI script_Properties_EnableOpacityMap(int id, char* type, int obj_id, bool val)
{
	GUI::MainWindowPy::script_Properties_EnableOpacityMap(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_visible(int id, char* type, int obj_id, bool flag_show_actors)
{
	GUI::MainWindowPy::script_Properties_visible(id, type, obj_id, flag_show_actors);
}

void MAINWINDOWAPI script_Properties_show_scalarBars(int id, char* type, int obj_id, bool mScalarBarVisible)
{
	GUI::MainWindowPy::script_Properties_show_scalarBars(id, type, obj_id, mScalarBarVisible);
}

void MAINWINDOWAPI script_Properties_show_cubeAxes(int id, char* type, int obj_id, bool flag_cubeAxes)
{
	GUI::MainWindowPy::script_Properties_show_cubeAxes(id, type, obj_id, flag_cubeAxes);
}

void MAINWINDOWAPI script_Properties_scalarBarPosition(int id, char* type, int obj_id, char* colName, int tep_orietation, double pos0, double pos1, double pos2, double pos3)
{
	GUI::MainWindowPy::script_Properties_scalarBarPosition(id, type, obj_id, colName, tep_orietation, pos0, pos1, pos2, pos3);
}

void MAINWINDOWAPI script_FilterClip(int id, char* type, int obj_id)
{
	GUI::MainWindowPy::script_FilterClip(id, type, obj_id);
}

void MAINWINDOWAPI script_FilterSlice(int id, char* type, int obj_id)
{
	GUI::MainWindowPy::script_FilterSlice(id, type, obj_id);
}

void MAINWINDOWAPI script_FilterContour(int id, char* type, int obj_id)
{
	GUI::MainWindowPy::script_FilterContour(id, type, obj_id);
}

void MAINWINDOWAPI script_FilterVector(int id, char* type, int obj_id)
{
	GUI::MainWindowPy::script_FilterVector(id, type, obj_id);
}

void MAINWINDOWAPI script_FilterReflection(int id, char* type, int obj_id)
{
	GUI::MainWindowPy::script_FilterReflection(id, type, obj_id);
}

void MAINWINDOWAPI script_FilterSmooth(int id, char* type, int obj_id)
{
	GUI::MainWindowPy::script_FilterSmooth(id, type, obj_id);
}

void MAINWINDOWAPI script_FilterStreamLine(int id, char* type, int obj_id)
{
	GUI::MainWindowPy::script_FilterStreamLine(id, type, obj_id);
}

void MAINWINDOWAPI script_Properties_vector_GlyphVector(int id, char* type, int obj_id, char* val)
{
	GUI::MainWindowPy::script_Properties_vector_GlyphVector(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_scalar(int id, char* type, int obj_id, char* val)
{
	GUI::MainWindowPy::script_Properties_vector_scalar(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_normal(int id, char* type, int obj_id, char* val)
{
	GUI::MainWindowPy::script_Properties_vector_normal(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_numPoints(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_vector_numPoints(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_glyph_type(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_vector_glyph_type(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_glyph_tipRes(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_vector_glyph_tipRes(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_glyph_tipRad(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_vector_glyph_tipRad(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_glyph_tipLen(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_vector_glyph_tipLen(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_glyph_shaftRes(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_vector_glyph_shaftRes(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_vector_glyph_shaftRad(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_vector_glyph_shaftRad(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_view_backgroundType(int id, char* type, int val)
{
	GUI::MainWindowPy::script_Properties_view_backgroundType(id, type, val);
}

void MAINWINDOWAPI script_Properties_view_backgroundColor(int id, char* type, int red, int green, int blue)
{
	GUI::MainWindowPy::script_Properties_view_backgroundColor(id, type, red, green, blue);
}

void MAINWINDOWAPI script_Properties_view_background2Color(int id, char* type, int red, int green, int blue)
{
	GUI::MainWindowPy::script_Properties_view_background2Color(id, type, red, green, blue);
}

void MAINWINDOWAPI script_Properties_view_axesVisible(int id, char* type, int a)
{
	GUI::MainWindowPy::script_Properties_view_axesVisible(id, type, a);
}

void MAINWINDOWAPI script_Properties_view_cameraParallel(int id, char* type, int a)
{
	GUI::MainWindowPy::script_Properties_view_cameraParallel(id, type, a);
}

void MAINWINDOWAPI script_Properties_view_interaction(int id, char* type, int a)
{
	GUI::MainWindowPy::script_Properties_view_interaction(id, type, a);
}

void MAINWINDOWAPI script_Properties_renderView(int id, char* type)
{
	GUI::MainWindowPy::script_Properties_renderView(id, type);
}

void MAINWINDOWAPI script_Camera_Position(int id, char* type, double pos0, double pos1, double pos2)
{
	GUI::MainWindowPy::script_Camera_Position(id, type, pos0, pos1, pos2);
}

void MAINWINDOWAPI script_Camera_FocalPoint(int id, char* type, double focalPoint0, double focalPoint1, double focalPoint2)
{
	GUI::MainWindowPy::script_Camera_FocalPoint(id, type, focalPoint0, focalPoint1, focalPoint2);
}

void MAINWINDOWAPI script_Camera_ClippingRange(int id, char* type, double clippingRange0, double clippingRange1)
{
	GUI::MainWindowPy::script_Camera_ClippingRange(id, type, clippingRange0, clippingRange1);
}

void MAINWINDOWAPI script_Camera_ViewUp(int id, char* type, double viewup0, double viewup1, double viewup2)
{
	GUI::MainWindowPy::script_Camera_ViewUp(id, type, viewup0, viewup1, viewup2);
}

void MAINWINDOWAPI script_Camera_ViewAngle(int id, char* type, double angle)
{
	GUI::MainWindowPy::script_Camera_ViewAngle(id, type, angle);
}

void MAINWINDOWAPI script_Camera_Zoom(int id, char* type, double zoom)
{
	GUI::MainWindowPy::script_Camera_Zoom(id, type, zoom);
}

void MAINWINDOWAPI script_Camera_Reset(int id, char* type)
{
	GUI::MainWindowPy::script_Camera_Reset(id, type);
}

void MAINWINDOWAPI script_Properties_planeOrigin(int id, char* type, int obj_id, double x, double y, double z)
{
	GUI::MainWindowPy::script_Properties_planeOrigin(id, type, obj_id, x, y, z);
}

void MAINWINDOWAPI script_Properties_planeNormal(int id, char* type, int obj_id,  double x, double y, double z)
{
	GUI::MainWindowPy::script_Properties_planeNormal(id, type, obj_id, x, y, z);
}

void MAINWINDOWAPI script_Properties_planeVisible(int id, char* type, int obj_id, int a)
{
	GUI::MainWindowPy::script_Properties_planeVisible(id, type, obj_id, a);
}

void MAINWINDOWAPI script_Properties_insideOut(int id, char* type, int obj_id, int a)
{
	GUI::MainWindowPy::script_Properties_insideOut(id, type, obj_id, a);
}

void MAINWINDOWAPI script_Properties_contourColumn(int id, char* type, int obj_id, char* val)
{
	GUI::MainWindowPy::script_Properties_contourColumn(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_contourValue(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_contourValue(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_contour_reflection(int id, char* type, int obj_id, int aaa)
{
	GUI::MainWindowPy::script_Properties_contour_reflection(id, type, obj_id, aaa);
}

void MAINWINDOWAPI script_Properties_contour_reflectionAxes(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_contour_reflectionAxes(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_reflectionAxes(int id, char* type, int obj_id, int reflection_axis)
{
	GUI::MainWindowPy::script_Properties_reflectionAxes(id, type, obj_id, reflection_axis);
}

void MAINWINDOWAPI script_Properties_smooth(int id, char* type, int obj_id, int smotype, double coef)
{
	GUI::MainWindowPy::script_Properties_smooth(id, type,obj_id, smotype, coef);
}

void MAINWINDOWAPI script_Properties_streamline_vector(int id, char* type, int obj_id, char* val)
{
	GUI::MainWindowPy::script_Properties_streamline_vector(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_integration_direction(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_integration_direction(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_integration_type(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_integration_type(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_integration_stepUnit(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_integration_stepUnit(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_integration_initStepLen(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_streamline_integration_initStepLen(id, type, obj_id, val);

}

void MAINWINDOWAPI script_Properties_streamline_integration_miniStepLen(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_streamline_integration_miniStepLen(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_integration_maxiStepLen(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_streamline_integration_maxiStepLen(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_stream_maxiSteps(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_stream_maxiSteps(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_stream_maxiStreamLen(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_streamline_stream_maxiStreamLen(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_stream_terminalSpeed(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_streamline_stream_terminalSpeed(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_stream_maxiError(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_streamline_stream_maxiError(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_seeds_type(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_seeds_type(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_seeds_mPoint(int id, char* type, int obj_id, double val0, double val1, double val2)
{
	GUI::MainWindowPy::script_Properties_streamline_seeds_mPoint(id, type, obj_id, val0, val1, val2);
}

void MAINWINDOWAPI script_Properties_streamline_seeds_num_points(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_seeds_num_points(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_seeds_radius(int id, char* type, int obj_id, double val)
{
	GUI::MainWindowPy::script_Properties_streamline_seeds_radius(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_vorticity(int id, char* type, int obj_id, bool val)
{
	GUI::MainWindowPy::script_Properties_streamline_vorticity(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_interpolatorType(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_interpolatorType(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_surface_streamLines(int id, char* type, int obj_id, bool val)
{
	GUI::MainWindowPy::script_Properties_streamline_surface_streamLines(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_reflection(int id, char* type, int obj_id, bool val)
{
	GUI::MainWindowPy::script_Properties_streamline_reflection(id, type, obj_id, val);
}

void MAINWINDOWAPI script_Properties_streamline_reflectionAxes(int id, char* type, int obj_id, int val)
{
	GUI::MainWindowPy::script_Properties_streamline_reflectionAxes(id, type, obj_id, val);
}

/*
void MAINWINDOWAPI showFastCAE()
{
	GUI::MainWindowPy::showFastCAE();
}*/

void MAINWINDOWAPI undo()
{
	GUI::MainWindowPy::undo();
}

void MAINWINDOWAPI redo()
{
	GUI::MainWindowPy::redo();
}
