#include "hempicgui.h"
#include "ui_hempicgui.h"

#define CONF_DIR "/.hempicGUI/"
#define DB_NAME "hempicGUI.sqlite"

HempicGUI::HempicGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HempicGUI)
{
    ui->setupUi(this);

    /* Ventana sin resize */
    this->statusBar()->setSizeGripEnabled(false);
    this->setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());

    /* Inicializar fecha */
    fechaActual = QDateTime::currentDateTime();
    asignarFechaGUI();

    /* Inicializar configuraciones*/
    idUsuario = 1; //TODO: Cambiar

    /* Inicializar database*/
    database = QSqlDatabase::addDatabase("QSQLITE");

    if(!existeBaseDato()) {
        qDebug() << "Creando directorio de configuración";
        QDir dir(QDir::homePath()+CONF_DIR);
        dir.mkpath(dir.absolutePath());
        qDebug() << "Copiando base de datos al directorio de configuración";
        QFile::copy(":/db/hempicGUI.sqlite", QDir::homePath()+CONF_DIR+DB_NAME);
        QProcess::execute ("chmod 777 "+QDir::homePath()+CONF_DIR+DB_NAME);
    }

    database.setDatabaseName(QDir::homePath()+CONF_DIR+DB_NAME);
    //database.setConnectOptions("ISC_DPB_LC_CTYPE=Latin1");

    if(database.open())
        qDebug() << "DB OK";

    llenarCombosProyectos();
}

HempicGUI::~HempicGUI()
{
    database.close();
    delete ui;
}

void HempicGUI::llenarCombosProyectos()
{
    QStringList listaProyectos;

    listaProyectos.append("--");
    listaProyectos.append("Almuerzo");

    if(database.isOpen()) {
        QSqlQuery query;

        if(query.exec("select * from proyectos")) {
            while(query.next()) {
                listaProyectos.append(query.value(2).toString());
            }
        }

        ui->periodo1Combo->addItems(listaProyectos);
        ui->periodo2Combo->addItems(listaProyectos);
        ui->periodo3Combo->addItems(listaProyectos);
        ui->periodo4Combo->addItems(listaProyectos);
        ui->periodo5Combo->addItems(listaProyectos);
        ui->periodo6Combo->addItems(listaProyectos);
        ui->periodo7Combo->addItems(listaProyectos);
        ui->periodo8Combo->addItems(listaProyectos);
        ui->periodo9Combo->addItems(listaProyectos);
        ui->periodo10Combo->addItems(listaProyectos);

        if(query.exec("select * from dedicaciones where fecha='" + convertirFecha(fechaActual) + "'")) {
            while(query.next()) {
                switch (query.value(2).toString().toInt()) {
                case 1:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo1Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 2:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo2Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 3:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo3Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 4:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo4Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 5:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo5Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 6:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo6Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 7:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo7Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 8:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo8Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 9:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo9Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                case 10:
                    for(int i = 0; i < listaProyectos.size(); i++) {
                        if(query.value(4).toString() == listaProyectos.at(i)) {
                            ui->periodo10Combo->setCurrentIndex(i);
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void HempicGUI::asignarFechaGUI()
{
    ui->diaIntLabel->setText(QString::number(fechaActual.date().day()));
    ui->diaStringLabel->setText(obtenerDiaSemana(fechaActual.date().dayOfWeek()));
    ui->mesLabel->setText(obtenerMes(fechaActual.date().month()));
    ui->anioLabel->setText(QString::number(fechaActual.date().year()));
}


void HempicGUI::dedicacionInsertarActualizar(QString id, QString proyecto, int bloque)
{
    QString queryString = "select * from dedicaciones where id='" + id + "'";

    if(database.isOpen()) {
        QSqlQuery query;

       if(query.exec(queryString.toLatin1())) {
            if(query.next()) {
                QString actualizar = "update dedicaciones set proyecto='" + proyecto + "' where id='" + id + "'";

                if(query.exec(actualizar.toLatin1())) {
                    this->setStatusTip("Dedicación guadada");
                } else {
                    this->setStatusTip("Error al guardar Dedicación");
                }
            } else {
                QString insertar = "insert into dedicaciones values ('"+
                        id +"', '"+
                        convertirFecha(fechaActual) +"', '"+
                        QString::number(bloque) +"', '"+
                        "" +"', '"+
                        proyecto +"', '"+
                        QString::number(idUsuario) +"')";

                if(query.exec(insertar.toLatin1())) {
                    this->setStatusTip("Dedicación guadada");
                } else {
                    this->setStatusTip("Error al guardar Dedicación");
                }
            }
        }
    }

}

void HempicGUI::insertarActualizarComentario(QString id, QString comentario, int bloque)
{
    QString queryString = "select * from dedicaciones where id='" + id + "'";

    if(database.isOpen()) {
        QSqlQuery query;

       if(query.exec(queryString.toLatin1())) {
            if(query.next()) {
                QString actualizar = "update dedicaciones set comentario='" + comentario + "' where id='" + id + "'";

                if(query.exec(actualizar.toLatin1())) {
                    this->setStatusTip("Dedicación guadada");
                } else {
                    this->setStatusTip("Error al guardar Dedicación");
                }
            } else {
                QString insertar = "insert into dedicaciones values ('"+
                        id +"', '"+
                        convertirFecha(fechaActual) +"', '"+
                        QString::number(bloque) +"', '"+
                        comentario +"', '"+
                        "" +"', '"+
                        QString::number(idUsuario) +"')";

                if(query.exec(insertar.toLatin1())) {
                    this->setStatusTip("Dedicación guadada");
                } else {
                    this->setStatusTip("Error al guardar Dedicación");
                }
            }
        }
    }


}

/*** Utils ***/

bool HempicGUI::existeBaseDato()
{
    QFileInfo verificador(QDir::homePath()+CONF_DIR+DB_NAME);
    if(verificador.isFile()) {
        return true;
    }

    return false;
}

QString HempicGUI::obtenerDiaSemana(int dia)
{
    QString diaString = "";

    switch (dia) {
    case 1:
        diaString = "Lunes";
        break;
    case 2:
        diaString = "Martes";
        break;
    case 3:
        diaString = "Miércoles";
        break;
    case 4:
        diaString = "Jueves";
        break;
    case 5:
        diaString = "Viernes";
        break;
    case 6:
        diaString = "Sábado";
        break;
    case 7:
        diaString = "Domingo";
        break;
    default:
        break;
    }

    return diaString;

}

QString HempicGUI::obtenerMes(int mes)
{
    QString mesString = "";

    switch (mes) {
    case 1:
        mesString = "Enero";
        break;
    case 2:
        mesString = "Febre";
        break;
    case 3:
        mesString = "Marzo";
        break;
    case 4:
        mesString = "Abril";
        break;
    case 5:
        mesString = "Mayo";
        break;
    case 6:
        mesString = "Junio";
        break;
    case 7:
        mesString = "Julio";
        break;
    case 8:
        mesString = "Agosto";
        break;
    case 9:
        mesString = "Sept";
        break;
    case 10:
        mesString = "Octub";
        break;
    case 11:
        mesString = "Nov";
        break;
    case 12:
        mesString = "Dic";
        break;
    default:
        break;
    }

    return mesString;
}

QString HempicGUI::convertirFecha(QDateTime fecha)
{
    return QString::number(fecha.date().day()) + "/" +
            QString::number(fecha.date().month()) + "/" +
            QString::number(fecha.date().year());
}

QString HempicGUI::obtenerComentario(QString id)
{
    QString queryString = "select comentario from dedicaciones where id='" + id + "'";

    if(database.isOpen()) {
        QSqlQuery query;
        if(query.exec(queryString.toLatin1())) {
            if(query.first()) {
                return query.value(0).toString();
            }
        }
    }

    return "";
}

/*** Eventos ***/

void HempicGUI::on_cambiarFechaBoton_clicked()
{
    // Levantar Popup calendario
}

void HempicGUI::on_periodo1Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p1");
    dedicacionInsertarActualizar(id, arg1, 1);
}

void HempicGUI::on_periodo2Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p2");
    dedicacionInsertarActualizar(id, arg1, 2);
}

void HempicGUI::on_periodo3Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p3");
    dedicacionInsertarActualizar(id, arg1, 3);
}

void HempicGUI::on_periodo4Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p4");
    dedicacionInsertarActualizar(id, arg1, 4);
}

void HempicGUI::on_periodo5Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p5");
    dedicacionInsertarActualizar(id, arg1, 5);
}

void HempicGUI::on_periodo6Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p6");
    dedicacionInsertarActualizar(id, arg1, 6);
}

void HempicGUI::on_periodo7Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p7");
    dedicacionInsertarActualizar(id, arg1, 7);
}

void HempicGUI::on_periodo8Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p8");
    dedicacionInsertarActualizar(id, arg1, 8);
}

void HempicGUI::on_periodo9Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p9");
    dedicacionInsertarActualizar(id, arg1, 9);
}

void HempicGUI::on_periodo10Combo_activated(const QString &arg1)
{
    QString id = QString(convertirFecha(fechaActual)+"-p10");
    dedicacionInsertarActualizar(id, arg1, 10);
}

void HempicGUI::on_comentarioP1_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p1");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 1);
}

void HempicGUI::on_comentarioP2_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p2");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 2);
}

void HempicGUI::on_comentarioP3_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p3");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 3);
}

void HempicGUI::on_comentarioP4_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p4");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 4);
}

void HempicGUI::on_toolButton_5_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p5");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 5);
}

void HempicGUI::on_comentarioP6_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p6");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 6);
}

void HempicGUI::on_comentarioP7_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p7");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 7);
}

void HempicGUI::on_comentarioP8_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p8");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 8);
}

void HempicGUI::on_comentarioP9_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p9");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 9);
}

void HempicGUI::on_comentarioP10_clicked()
{
    QString id = QString(convertirFecha(fechaActual)+"-p10");
    bool ok = false;
    QString comentario = QInputDialog::getText(
                this, "Comentario", "Inserte comentario", QLineEdit::Normal, obtenerComentario(id), &ok);
    if(ok && !comentario.isEmpty())
        insertarActualizarComentario(id, comentario, 10);
}
