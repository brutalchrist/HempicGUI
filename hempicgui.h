#ifndef HEMPICGUI_H
#define HEMPICGUI_H

#include <QMainWindow>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QtSql>
#include <QSqlDatabase>
#include <QFile>
#include <QInputDialog>

namespace Ui {
class HempicGUI;
}

class HempicGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit HempicGUI(QWidget *parent = 0);
    ~HempicGUI();
    QDateTime fechaActual;
    QSqlDatabase database;
    int idUsuario;
    QString comentario;

private slots:
    void dedicacionInsertarActualizar(QString id, QString proyecto, int bloque);
    void insertarActualizarComentario(QString id, QString comentario, int bloque);
    void llenarCombosProyectos();
    void asignarFechaGUI();

    /*Utils*/
    QString obtenerMes(int mes);
    QString obtenerDiaSemana(int dia);
    bool existeBaseDato();
    QString convertirFecha(QDateTime fecha);
    QString obtenerComentario(QString id);

    /* Eventos */
    void on_cambiarFechaBoton_clicked();
    void on_periodo1Combo_activated(const QString &arg1);
    void on_periodo2Combo_activated(const QString &arg1);
    void on_periodo3Combo_activated(const QString &arg1);
    void on_periodo4Combo_activated(const QString &arg1);
    void on_periodo5Combo_activated(const QString &arg1);
    void on_periodo6Combo_activated(const QString &arg1);
    void on_periodo7Combo_activated(const QString &arg1);
    void on_periodo8Combo_activated(const QString &arg1);
    void on_periodo9Combo_activated(const QString &arg1);
    void on_periodo10Combo_activated(const QString &arg1);

    void on_comentarioP1_clicked();
    void on_comentarioP2_clicked();
    void on_comentarioP3_clicked();
    void on_comentarioP4_clicked();
    void on_toolButton_5_clicked();
    void on_comentarioP6_clicked();
    void on_comentarioP7_clicked();
    void on_comentarioP8_clicked();
    void on_comentarioP9_clicked();
    void on_comentarioP10_clicked();

private:
    Ui::HempicGUI *ui;
};

#endif // HEMPICGUI_H
