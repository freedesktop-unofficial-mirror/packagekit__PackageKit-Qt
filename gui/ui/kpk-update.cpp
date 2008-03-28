/*  This file is part of the KDE project
 *  Copyright (C) 2007 Carlo Segato <brandon.ml@gmail.com>
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301, USA.
 * 
 */

#include <kgenericfactory.h>
#include <KAboutData>
#include <KDebug>
#include "kpk-update.h"


typedef KGenericFactory<KPackageKit, QWidget> KPackageKitFactory;
 K_EXPORT_COMPONENT_FACTORY( kcm_kpk_update, KPackageKitFactory("kcm_kpk_update") );

// K_PLUGIN_FACTORY(KPackageKitFactory, registerPlugin<KPackageKit>();)
// K_EXPORT_PLUGIN(KPackageKitFactory("zkpackagekit"))

KPackageKit::KPackageKit(QWidget *&parent, const QStringList &args)
    : KCModule(KPackageKitFactory::componentData(), parent)
{
    KAboutData *about = new KAboutData("kcm_kpk_update", 0, ki18n("KPackageKit Update"),"0.1");
    setAboutData(about);
    setupUi(this);
    kDebug() << args;
}
