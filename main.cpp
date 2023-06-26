#include "simulator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication SimulatorApplication(argc, argv);
    Simulator SimulatorWindow;
    SimulatorWindow.show();
    return SimulatorApplication.exec();
}
