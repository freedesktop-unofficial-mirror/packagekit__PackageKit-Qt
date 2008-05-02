/***************************************************************************
 *   Copyright (C) 2007 by Daniel Nicoletti   *
 *   mirttex@users.sourceforge.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <klocale.h>
#include <kstandarddirs.h>
#include <QPalette>
#include <QColor>
#include "PkAddRm.h"

PkAddRm::PkAddRm( QWidget *parent ) : QWidget( parent )
{
    setupUi( this );
    //initialize the model, delegate, client and  connect it's signals
    packageView->setModel(m_pkg_model_main = new PkAddRmModel(this));
    packageView->setItemDelegate(pkg_delegate = new PkAddRmDelegate(this));
    m_pkClient_main = new Client();
    qDebug() << "We have tid " << m_pkClient_main->tid();
    connect( m_pkClient_main, SIGNAL(newPackage(Package *)), m_pkg_model_main, SLOT(addPackage(Package *)) );
    connect( m_pkClient_main, SIGNAL(Finished(Exit::Value, uint)), this, SLOT(Finished(Exit::Value, uint)) );
    connect( m_pkClient_main, SIGNAL(Files(Package *, QStringList)), this, SLOT(Files(Package *, QStringList)) );
    //initialize the groups
    //TODO create a better approach on this.
    for (int i = 0; i < m_pkClient_main->getGroups().size(); ++i)
        groupsCB->addItem(KIcon("applications-" + m_pkClient_main->getGroups().at(i)),m_pkClient_main->getGroups().at(i));
    //initialize the dependecies and description client, and model.
    m_pkClient_dep = new Client();
    qDebug() << "We have tid " << m_pkClient_dep->tid();
    dependsOnLV->setModel(m_pkg_model_dep = new PkAddRmModel(this));
    connect( m_pkClient_dep, SIGNAL(newPackage(Package *)), m_pkg_model_dep, SLOT(addPackage(Package *)) );
    connect( m_pkClient_dep, SIGNAL(Description(Package *,  const QString, const QString, const QString,
        const QString, qulonglong) ),
        this, SLOT( Description(Package *, const QString, const QString, const QString,
        const QString, qulonglong) ) );
    //initialize the requirements client, and model.
    m_pkClient_req = new Client();
    qDebug() << "We have tid " << m_pkClient_req->tid();
    dependsOnLV->setModel(m_pkg_model_req = new PkAddRmModel(this));
    connect( m_pkClient_req, SIGNAL(newPackage(Package *)), m_pkg_model_req, SLOT(addPackage(Package *)) );
    // connect the timer...
    connect(&m_notifyT, SIGNAL(timeout()), this, SLOT(notifyUpdate()));
    // hides the description to have more space.
    descriptionDW->hide();
    actionPB->hide();
    notifyF->hide();
    QStringList filters;
    filters << "installed" << "devel" << "gui" << "free" << "basename";
    FilterMenu(filters);
}

PkAddRm::~PkAddRm()
{
    delete m_pkg_model_main;
    delete pkg_delegate;
    delete m_pkClient_main;
    delete m_toolQM;
    delete m_pkg_model_dep;
    delete m_pkClient_dep;
    delete m_pkg_model_req;
    delete m_pkClient_req;
}

void PkAddRm::on_searchPB_clicked()
{
    m_pkg_model_main->clear();
    qDebug() << "Search Name " << filters() ;
    m_pkClient_main->searchName(filters(), lineEdit->text());
    m_pkClient_dep->searchName(filters(), lineEdit->text());
    descriptionDW->setVisible(false);
}

void PkAddRm::on_groupsCB_currentIndexChanged( const QString & text )
{
    qDebug() << "Search Group " << text;
    m_pkg_model_main->clear();
    m_pkClient_main->searchGroup(filters(), text);
    descriptionDW->setVisible(false);
}

void PkAddRm::on_packageView_pressed( const QModelIndex & index )
{
    m_pkClient_dep->getDescription(index.model()->data(index, PkAddRmModel::IdRole).toString());
    m_pkClient_dep->getDepends(new Package(index.model()->data(index, PkAddRmModel::IdRole).toString()),false);
    notifyF->show();
    actionPB->show();
}

void PkAddRm::Finished(Exit::Value status, uint runtime)
{
    notifyF->show();
    notifyL->setText("Search finished in " + KGlobal::locale()->formatDuration(runtime) );
    QPalette teste;
    teste.setColor( QPalette::Normal, QPalette::Window, QColor(0,255,0,50));
    notifyL->setPalette(teste);
    notifyL->setAutoFillBackground(true);
    m_notifyT.start(5000);
//     notifyL->show();
}

void PkAddRm::notifyUpdate()
{
    qDebug() << "oi";
    m_notifyT.stop();
    notifyL->setAutoFillBackground(false);
    notifyF->hide();
}

void PkAddRm::Description(Package *p, const QString& license, const QString& group, const QString& detail, const QString& url, qulonglong size)
{

    m_pkClient_dep->getRequires(p,true);
    QString description;
    description += "<b>" + i18n("Package Name") + ":</b> " + p->name() + "<br />";
    if ( !license.isEmpty() )
        description += "<b>" + i18n("License") + ":</b> " + license + "<br />";
    if ( !group.isEmpty() )
        description += "<b>" + i18n("Group") + ":</b> " + group + "<br />";
    if ( !detail.isEmpty() )
        description += "<b>" + i18n("Details") + ":</b> " + detail + "<br />";
    if ( !url.isEmpty() )
        description += "<b>" + i18n("Home Page") + ":</b> <a href=\"" + url + "\">" + url + "</a><br />";
    if ( size > 0 )
        description += "<b>" + i18n("Size") + ":</b> " + KGlobal::locale()->formatByteSize(size);
    descriptionKTB->setHtml(description);
    descriptionDW->setVisible(true);
}

void PkAddRm::Files(Package *, QStringList files)
{
    filesPTE->clear();
    for (int i = 0; i < files.size(); ++i)
        filesPTE->appendPlainText(files.at(i));
    descriptionDW->setVisible(true);
}

void PkAddRm::FilterMenu(const QStringList &filters)
{
    filtersTB->setPopupMode(QToolButton::InstantPopup);
    filtersTB->setArrowType(Qt::DownArrow);

    if(filters.size() != 0) {
        m_toolQM = new QMenu(this);
        filtersTB->setMenu(m_toolQM);

        if(filters.contains("installed")) {
            // Installed
            QMenu *menuInstalled = new QMenu(tr("Installed"), m_toolQM);
            m_toolQM->addMenu(menuInstalled);
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
            QMenu *menuDevelopment = new QMenu(tr("Development"), m_toolQM);
            m_toolQM->addMenu(menuDevelopment);
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
            QMenu *menuGui = new QMenu(tr("Graphical"), m_toolQM);
            m_toolQM->addMenu(menuGui);
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
            QMenu *menuFree = new QMenu(tr("Free"), m_toolQM);
            m_toolQM->addMenu(menuFree);
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
            m_toolQM->addSeparator();
            QAction *basename = new QAction(tr("Hide subpackages"), m_toolQM);
            basename->setCheckable(true);
            basename->setData("basename");
            m_toolQM->addAction(basename);

            actions << basename;
        }

    }
    else {
        filtersTB->setDisabled(true);
    }
}

QString PkAddRm::filters()
{
    QStringList buffer;
    for(int i = 0 ; i < actions.size() ; ++i) {
        if(actions.at(i)->isChecked())
            if(actions.at(i)->data() != QVariant())
                buffer << actions.at(i)->data().toString();
    }
    if(buffer.size() == 0) buffer << "none";
        return buffer.join(";");
}

#include "PkAddRm.moc"
