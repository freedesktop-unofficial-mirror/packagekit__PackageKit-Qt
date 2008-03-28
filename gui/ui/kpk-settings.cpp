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

#include "kpk-settings.h"

K_PLUGIN_FACTORY(KPackageKitFactory, registerPlugin<KPackageKit>();)
K_EXPORT_PLUGIN(KPackageKitFactory("kpackagekit"))

KPackageKit::KPackageKit(QWidget *parent, const QVariantList &args)
    : KCModule(KPackageKitFactory::componentData(), parent, args)
{
    KAboutData *about = new KAboutData("kcm_kpk_settings", 0, ki18n("KPackageKit Settings"),"0.1");
    setAboutData(about);
    setupUi(this);

}