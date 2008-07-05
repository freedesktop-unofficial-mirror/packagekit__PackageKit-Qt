/*  This file is part of the KDE project
 *  Copyright (C) 2008 Daniel Nicoletti <dantti85-pk@yahoo.com.br>
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

#include <KGenericFactory>
#include <KAboutData>

#include "kpk-addrm.h"

K_PLUGIN_FACTORY(KPackageKitFactory, registerPlugin<KPackageKit>(); )
K_EXPORT_PLUGIN(KPackageKitFactory("kcm_kpk_addrm"))

KPackageKit::KPackageKit(QWidget *parent, const QVariantList &args)
    : KCModule(KPackageKitFactory::componentData(), parent, args)
{
    KAboutData *about = new KAboutData("kcm_kpk_addrm", 0, ki18n("Add and Remove Software"),"0.1");
    setAboutData(about);
    setButtons(Apply);
    m_grid = new QGridLayout(this);
    view = new PkAddRm(this);
    connect(this, SIGNAL(s_load()), view, SLOT(load()) );
    connect(this, SIGNAL(s_save()), view, SLOT(save()) );
    connect(view, SIGNAL(changed(bool)), this, SIGNAL(changed(bool)) );
    m_grid->addWidget(view);
}
