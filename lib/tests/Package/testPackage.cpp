#include <QtCore>

#include "../../Package.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	Package p("vim-common;2:7.1.283-1.fc9;x86_64;installed");
	Package q("vim-common;2:7.1.283-1.fc9;x86_64;installed", "info", "summary");
	if(p == q) qDebug() << "both packages are the same";

}
