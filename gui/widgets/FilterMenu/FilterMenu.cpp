#include "FilterMenu.h"

FilterMenu::FilterMenu(const QStringList &filters, QWidget *parent) : QToolButton(parent) {
	setPopupMode(QToolButton::InstantPopup);
	setArrowType(Qt::DownArrow);

	if(filters.size() != 0) {
		menu = new QMenu(this);
		setMenu(menu);

		if(filters.contains("installed")) {
			// Installed
			QMenu *menuInstalled = new QMenu(tr("Installed"), menu);
			menu->addMenu(menuInstalled);
			QActionGroup *installedGroup = new QActionGroup(menuInstalled);
			installedGroup->setExclusive(true);

			QAction *installedTrue = new QAction(tr("installed"), installedGroup);
			installedTrue->setCheckable(true);
			installedTrue->setData("installed");
			installedGroup->addAction(installedTrue);
			menuInstalled->addAction(installedTrue);

			QAction *installedFalse = new QAction(tr("~installed"), installedGroup);
			installedFalse->setCheckable(true);
			installedFalse->setData("~installed");
			installedGroup->addAction(installedFalse);
			menuInstalled->addAction(installedFalse);

			QAction *installedNone = new QAction(tr("No filter"), installedGroup);
			installedNone->setCheckable(true);
			installedNone->setChecked(true);
			installedGroup->addAction(installedNone);
			menuInstalled->addAction(installedNone);

			actions << installedTrue << installedFalse << installedNone;
		}
		if(filters.contains("devel")) {
			// Development
			QMenu *menuDevelopment = new QMenu(tr("Development"), menu);
			menu->addMenu(menuDevelopment);
			QActionGroup *developmentGroup = new QActionGroup(menuDevelopment);
			developmentGroup->setExclusive(true);

			QAction *developmentTrue = new QAction(tr("development"), developmentGroup);
			developmentTrue->setCheckable(true);
			developmentTrue->setData("development");
			developmentGroup->addAction(developmentTrue);
			menuDevelopment->addAction(developmentTrue);

			QAction *developmentFalse = new QAction(tr("~development"), developmentGroup);
			developmentFalse->setCheckable(true);
			developmentFalse->setData("~development");
			developmentGroup->addAction(developmentFalse);
			menuDevelopment->addAction(developmentFalse);

			QAction *developmentNone = new QAction(tr("No filter"), developmentGroup);
			developmentNone->setCheckable(true);
			developmentNone->setChecked(true);
			developmentGroup->addAction(developmentNone);
			menuDevelopment->addAction(developmentNone);

			actions << developmentTrue << developmentFalse << developmentNone;
		}
		if(filters.contains("gui")) {
			// Graphical
			QMenu *menuGui = new QMenu(tr("Graphical"), menu);
			menu->addMenu(menuGui);
			QActionGroup *guiGroup = new QActionGroup(menuGui);
			guiGroup->setExclusive(true);

			QAction *guiTrue = new QAction(tr("gui"), guiGroup);
			guiTrue->setCheckable(true);
			guiTrue->setData("gui");
			guiGroup->addAction(guiTrue);
			menuGui->addAction(guiTrue);

			QAction *guiFalse = new QAction(tr("~gui"), guiGroup);
			guiFalse->setCheckable(true);
			guiFalse->setData("~gui");
			guiGroup->addAction(guiFalse);
			menuGui->addAction(guiFalse);

			QAction *guiNone = new QAction(tr("No filter"), guiGroup);
			guiNone->setCheckable(true);
			guiNone->setChecked(true);
			guiGroup->addAction(guiNone);
			menuGui->addAction(guiNone);

			actions << guiTrue << guiFalse << guiNone;
		}
		if(filters.contains("free")) {
			// Free
			QMenu *menuFree = new QMenu(tr("Free"), menu);
			menu->addMenu(menuFree);
			QActionGroup *freeGroup = new QActionGroup(menuFree);
			freeGroup->setExclusive(true);

			QAction *freeTrue = new QAction(tr("free"), freeGroup);
			freeTrue->setCheckable(true);
			freeTrue->setData("free");
			freeGroup->addAction(freeTrue);
			menuFree->addAction(freeTrue);

			QAction *freeFalse = new QAction(tr("~free"), freeGroup);
			freeFalse->setCheckable(true);
			freeFalse->setData("~free");
			freeGroup->addAction(freeFalse);
			menuFree->addAction(freeFalse);

			QAction *freeNone = new QAction(tr("No filter"), freeGroup);
			freeNone->setCheckable(true);
			freeNone->setChecked(true);
			freeGroup->addAction(freeNone);
			menuFree->addAction(freeNone);

			actions << freeTrue << freeFalse << freeNone;
		}
		if(filters.contains("basename")) {
			menu->addSeparator();
			QAction *basename = new QAction(tr("Hide subpackages"), menu);
			basename->setCheckable(true);
			basename->setData("basename");
			menu->addAction(basename);

			actions << basename;
		}

	} else {
		setDisabled(true);
	}
}

QString FilterMenu::filters() {
	QStringList buffer;
	for(int i = 0 ; i < actions.size() ; ++i) {
		if(actions.at(i)->isChecked())
			if(actions.at(i)->data() != QVariant())
				buffer << actions.at(i)->data().toString();
	}
	if(buffer.size() == 0) buffer << "none";
	return buffer.join(";");
}
