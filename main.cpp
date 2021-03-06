/*
 * Copyright (C) 2020  Your FullName
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * ubuntu-calculator-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QGuiApplication>
#include <QCoreApplication>
#include <QUrl>
#include <QString>
#include <QQuickView>
#include <libguile.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    SCM func;
    char cwd[PATH_MAX];

    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/share/guile/2.0");

    setenv("GUILE_LOAD_PATH", cwd, 1);

    scm_init_guile();
    scm_c_primitive_load("script.scm");

    func = scm_variable_ref(scm_c_lookup("simple-script"));
    scm_call_0(func);

    QGuiApplication *app = new QGuiApplication(argc, (char**)argv);
    app->setApplicationName("appname4.yourname");

    qDebug() << "Starting app from main.cpp";

    QQuickView *view = new QQuickView();
    view->setSource(QUrl(QStringLiteral("qml/Main.qml")));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->show();

    return app->exec();
}
