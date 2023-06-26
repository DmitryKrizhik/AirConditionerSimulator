#include "simulator.h"
#include "ui_simulator.h"

Simulator::Simulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Simulator)
{

    setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);
    TurnOnSimulator();
    SendResponse();
    SetLightTheme();
}

Simulator::~Simulator()
{
    delete ui;
}

void Simulator::on_CloseWindowButton_clicked()
{
    TurnOffSimulator();
    qApp->quit();
}

void Simulator::SetLightTheme()
{
    SimUtils.SetTheme(LIGHTTHEME);

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(Constants::rValueWindowLightTheme, Constants::gValueWindowLightTheme,
                                          Constants::bValueWindowLightTheme));
    pal.setColor(QPalette::Button, QColor(Constants::rValueButtonLightTheme, Constants::gValueButtonLightTheme,
                                          Constants::bValueButtonLightTheme));
    pal.setColor(QPalette::ButtonText, QColor(Constants::rValueWindowText, Constants::gValueWindowText,
                                              Constants::bValueWindowText));
    pal.setColor(QPalette::WindowText, QColor(Constants::rValueButtonText, Constants::gValueButtonText,
                                              Constants::bValueButtonText));
    setPalette(pal);
    SetColorOfThePowerButton();
}

void Simulator::SetDarkTheme()
{
    SimUtils.SetTheme(DARKTHEME);

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(Constants::rValueWindowDarkTheme, Constants::gValueWindowDarkTheme,
                                          Constants::bValueWindowDarkTheme));
    pal.setColor(QPalette::Button, QColor(Constants::rValueButtonDarkTheme, Constants::gValueButtonDarkTheme,
                                          Constants::bValueButtonDarkTheme));
    pal.setColor(QPalette::ButtonText, QColor(Constants::rValueWindowText, Constants::gValueWindowText,
                                              Constants::bValueWindowText));
    pal.setColor(QPalette::WindowText, QColor(Constants::rValueButtonText, Constants::gValueButtonText,
                                              Constants::bValueButtonText));
    setPalette(pal);
    SetColorOfThePowerButton();
}

void Simulator::on_ResolutionSelectionBox_activated(int newResolutionType)
{
    switch(newResolutionType)
    {
        case RESOLUTION800x600:
            setFixedSize(Constants::horizontalSmallResolitionValue,
                         Constants::verticalSmallResolitionValue); break;
        case RESOLUTION1024x768:
            setFixedSize(Constants::horizontalBigResolitionValue,
                         Constants::verticalBigResolitionValue); break;
    }
}

void Simulator::on_ThemeSelectionBox_activated(int newThemeType)
{

    switch(newThemeType)
    {
        case LIGHTTHEME:
            SimUtils.SetTheme(LIGHTTHEME);
            SetLightTheme();
            break;
        case DARKTHEME:
            SimUtils.SetTheme(DARKTHEME);
            SetDarkTheme();
            break;
    }
}

void Simulator::on_TemperatureSelectionSlider_valueChanged(int newTemperatureValue)
{
    switch(SimUtils.GetTemperatureUnit())
    {
        case CELSIUS:
            SimUtils.SetTemperatureValue(newTemperatureValue);
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °C");
            break;
        case FHARENHEIT:
            SimUtils.SetTemperatureValue(newTemperatureValue);
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °F");
            break;
        case KELVIN:
            SimUtils.SetTemperatureValue(newTemperatureValue);
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " K");
            break;
    }
}

void Simulator::on_TemperatureUnitSelectionBox_activated(int newTemperatureType)
{
    if(newTemperatureType == CELSIUS)
    {
        switch(SimUtils.GetTemperatureUnit())
        {
            case CELSIUS:
                SimUtils.SetTemperatureUnit(CELSIUS);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInCelsius);
                break;
            case FHARENHEIT:
                SimUtils.SetTemperatureUnit(CELSIUS);
                SimUtils.SetTemperatureValue(Converter.ConvertFharenheitToCelsius(SimUtils.GetTemperatureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °C");
                break;
            case KELVIN:
                SimUtils.SetTemperatureUnit(CELSIUS);
                SimUtils.SetTemperatureValue(Converter.ConvertKelvinsToCelsius(SimUtils.GetTemperatureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °C");
                break;
            default:
                SimUtils.SetTemperatureUnit(CELSIUS);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInCelsius);
                break;
        }
    }
    else if(newTemperatureType == FHARENHEIT)
    {
        switch(SimUtils.GetTemperatureUnit())
        {
            case FHARENHEIT:
                SimUtils.SetTemperatureUnit(FHARENHEIT);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInFharenheit);
                break;
            case CELSIUS:
                SimUtils.SetTemperatureUnit(FHARENHEIT);
                SimUtils.SetTemperatureValue(Converter.ConvertCelsiusToFharenheit(SimUtils.GetTemperatureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °F");
                break;
            case KELVIN:
                SimUtils.SetTemperatureUnit(FHARENHEIT);
                SimUtils.SetTemperatureValue(Converter.ConvertKelvinsToFharenheit(SimUtils.GetTemperatureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °F");
                break;
            default:
                SimUtils.SetTemperatureUnit(FHARENHEIT);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInFharenheit);
                break;
        }
    }
    else if(newTemperatureType == KELVIN)
        {
        switch(SimUtils.GetTemperatureUnit())
        {
            case KELVIN:
                SimUtils.SetTemperatureUnit(KELVIN);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInKelvins);
                break;
            case CELSIUS:
                SimUtils.SetTemperatureUnit(KELVIN);
                SimUtils.SetTemperatureValue(Converter.ConvertCelsiusToKelvins(SimUtils.GetTemperatureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " K");
                break;
            case FHARENHEIT:
                SimUtils.SetTemperatureUnit(KELVIN);
                SimUtils.SetTemperatureValue(Converter.ConvertFharenheitToKelvins(SimUtils.GetTemperatureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " K");
                break;
            default:
                SimUtils.SetTemperatureUnit(KELVIN);
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInKelvins);
                break;
            }
        }
}

void Simulator::on_PressureUnitSelectionBox_activated(int newPressureType)
{
    if(newPressureType == KILOPASKALS)
    {
        switch(SimUtils.GetPressureUnit())
        {
            case KILOPASKALS:
                SimUtils.SetPressureUnit(KILOPASKALS);
                ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInKilopaskals);
                ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInKilopaskals);
                break;
            case MMHG:
                SimUtils.SetPressureUnit(KILOPASKALS);
                SimUtils.SetPressureValue(Converter.ConvertMMHGToKilopaskals(SimUtils.GetPressureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetPressureValue());
                ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInKilopaskals);
                ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInKilopaskals);
                ui->PressureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " KPa");
                break;
            default:
                SimUtils.SetPressureUnit(KILOPASKALS);
                ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInKilopaskals);
                ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInKilopaskals);
                break;
        }
    }
    else if(newPressureType == MMHG)
    {
        switch(SimUtils.GetPressureUnit())
        {
            case MMHG:
            SimUtils.SetPressureUnit(MMHG);
            ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInMMHg);
            ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInMMHg);
            break;
            case KILOPASKALS:
                SimUtils.SetPressureUnit(MMHG);
                SimUtils.SetPressureValue(Converter.ConvertKilopaskalsToMMHG(SimUtils.GetPressureValue()));
                SimUtils.SetTemporaryValue(SimUtils.GetPressureValue());
                ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInMMHg);
                ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInMMHg);
                ui->PressureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " mmHg");
                break;
            default:
                SimUtils.SetPressureUnit(MMHG);
                ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInMMHg);
                ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInMMHg);
                break;
        }
    }
}

void Simulator::on_PressureSelectionSlider_valueChanged(int newPressureUnit)
{
    switch(SimUtils.GetPressureUnit())
    {
        case KILOPASKALS:
            SimUtils.SetPressureValue(newPressureUnit);
            ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " KPa");
            break;
        case MMHG:
            SimUtils.SetPressureValue(newPressureUnit);
            ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " mmHg");
            break;
    }
}

void Simulator::on_HumiditySelectionSlider_valueChanged(int newHumidityValue)
{
    SimUtils.SetHumidityValue(newHumidityValue);
    ui->HumidityActualParametersLabel->setText(QString::number(SimUtils.GetHumidityValue()) + "%");
}

void Simulator::on_AngleSelectionSlider_valueChanged(int newAngleOfRotationValue)
{
    SimUtils.SetAngleValue(newAngleOfRotationValue);
    if(newAngleOfRotationValue < ZERO){ ui->AngleActualParametersLabel->setText(QString::number(-newAngleOfRotationValue) + "° left"); }
    else if(newAngleOfRotationValue > ZERO){ ui->AngleActualParametersLabel->setText(QString::number(newAngleOfRotationValue) + "° right"); }
    else{ ui->AngleActualParametersLabel->setText(QString::number(ZERO) + "°"); }
}

void Simulator::on_TemperatureIncreaseButton_clicked()
{
    switch(SimUtils.GetTemperatureUnit())
    {
        case CELSIUS:
            SimUtils.SetTemperatureValue(SimUtils.GetTemperatureValue()+ONE);
            SimUtils.CheckPossibleTemperatureValue();
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °C");
            ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemperatureValue());
            break;
        case FHARENHEIT:
            SimUtils.SetTemperatureValue(SimUtils.GetTemperatureValue()+ONE);
            SimUtils.CheckPossibleTemperatureValue();
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °F");
            ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemperatureValue());
            break;
        case KELVIN:
            SimUtils.SetTemperatureValue(SimUtils.GetTemperatureValue()+ONE);
            SimUtils.CheckPossibleTemperatureValue();
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " K");
            ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemperatureValue());
            break;
    }
}

void Simulator::on_TemperatureDecreaseButton_clicked()
{
    switch(SimUtils.GetTemperatureUnit())
    {
        case CELSIUS:
            SimUtils.SetTemperatureValue(SimUtils.GetTemperatureValue()-ONE);
            SimUtils.CheckPossibleTemperatureValue();
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °C");
            ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemperatureValue());
            break;
        case FHARENHEIT:
            SimUtils.SetTemperatureValue(SimUtils.GetTemperatureValue()-ONE);
            SimUtils.CheckPossibleTemperatureValue();
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " °F");
            ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemperatureValue());
            break;
        case KELVIN:
            SimUtils.SetTemperatureValue(SimUtils.GetTemperatureValue()-ONE);
            SimUtils.CheckPossibleTemperatureValue();
            ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " K");
            ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemperatureValue());
            break;
    }
}

void Simulator::on_PressureIncreaseButton_clicked()
{
    switch(SimUtils.GetPressureUnit())
    {
    case KILOPASKALS:
        SimUtils.SetPressureValue(SimUtils.GetPressureValue()+ONE);
        SimUtils.CheckPossiblePressureValue();
        ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " KPa");
        ui->PressureSelectionSlider->setValue(SimUtils.GetPressureValue());
        break;
    case MMHG:
        SimUtils.SetPressureValue(SimUtils.GetPressureValue()+ONE);
        SimUtils.CheckPossiblePressureValue();
        ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " mmHg");
        ui->PressureSelectionSlider->setValue(SimUtils.GetPressureValue());
        break;
    }
}

void Simulator::on_PressureDecreaseButton_clicked()
{
    switch(SimUtils.GetPressureUnit())
    {
    case KILOPASKALS:
        SimUtils.SetPressureValue(SimUtils.GetPressureValue()-ONE);
        SimUtils.CheckPossiblePressureValue();
        ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " KPa");
        ui->PressureSelectionSlider->setValue(SimUtils.GetPressureValue());
        break;
    case MMHG:
        SimUtils.SetPressureValue(SimUtils.GetPressureValue()-ONE);
        SimUtils.CheckPossiblePressureValue();
        ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " mmHg");
        ui->PressureSelectionSlider->setValue(SimUtils.GetPressureValue());
        break;
    }
}

void Simulator::on_HumidityIncreaseButton_clicked()
{
    SimUtils.SetHumidityValue(SimUtils.GetHumidityValue()+ONE);
    SimUtils.CheckPossibleHumidityValue();
    ui->HumidityActualParametersLabel->setText(QString::number(SimUtils.GetHumidityValue()) + "%");
    ui->HumiditySelectionSlider->setValue(SimUtils.GetHumidityValue());
}

void Simulator::on_HumidityDecreaseButton_clicked()
{
    SimUtils.SetHumidityValue(SimUtils.GetHumidityValue()-ONE);
    SimUtils.CheckPossibleHumidityValue();
    ui->HumidityActualParametersLabel->setText(QString::number(SimUtils.GetHumidityValue()) + "%");
    ui->HumiditySelectionSlider->setValue(SimUtils.GetHumidityValue());
}

void Simulator::on_AngleIncreaseButton_clicked()
{
    SimUtils.SetAngleValue(SimUtils.GetAngleValue()+ONE);
    SimUtils.CheckPossibleAngleValue();
    if(SimUtils.GetAngleValue() < ZERO){ ui->AngleActualParametersLabel->setText(QString::number(-SimUtils.GetAngleValue()) + "° left"); }
    else if(SimUtils.GetAngleValue() > ZERO){ ui->AngleActualParametersLabel->setText(QString::number(SimUtils.GetAngleValue()) + "° right"); }
    else{ ui->AngleActualParametersLabel->setText(QString::number(ZERO) + "°"); }
    ui->AngleSelectionSlider->setValue(SimUtils.GetAngleValue());
}

void Simulator::on_AngleDecreaseButton_clicked()
{
    SimUtils.SetAngleValue(SimUtils.GetAngleValue()-ONE);
    SimUtils.CheckPossibleAngleValue();
    if(SimUtils.GetAngleValue() < ZERO){ ui->AngleActualParametersLabel->setText(QString::number(-SimUtils.GetAngleValue()) + "° left"); }
    else if(SimUtils.GetAngleValue() > ZERO){ ui->AngleActualParametersLabel->setText(QString::number(SimUtils.GetAngleValue()) + "° right"); }
    else{ ui->AngleActualParametersLabel->setText(QString::number(ZERO) + "°"); }
    ui->AngleSelectionSlider->setValue(SimUtils.GetAngleValue());
}

void Simulator::on_PowerButton_clicked()
{
    if(SimUtils.GetPowerState() == ON){ TurnOffSimulator(); }
    else{ TurnOnSimulator(); }
}

void Simulator::TurnOnSimulator()
{
    SimUtils.ReadParametersFromFile();
    Controller.ReadTCPSettingsFromFile();
    qDebug() << Controller.GetHOST();
    qDebug() << Controller.GetPORT();
    qDebug() << Controller.GetRequestInterval();
    SetEnabledTrue();
    SetParametersToLabels();
    SimUtils.SetPowerState(ON);
    SetColorOfThePowerButton();
    SetPowerButtonText();
}

void Simulator::TurnOffSimulator()
{
    SimUtils.WriteParametersInFile();
    SetEnabledFalse();
    SetParametersToLabels();
    SimUtils.SetPowerState(OFF);
    SetColorOfThePowerButton();
    SetPowerButtonText();
}

void Simulator::SetEnabledFalse()
{
    ui->AngleDecreaseButton->setEnabled(false);
    ui->AngleIncreaseButton->setEnabled(false);
    ui->AngleSelectionSlider->setEnabled(false);
    ui->HumidityDecreaseButton->setEnabled(false);
    ui->HumidityIncreaseButton->setEnabled(false);
    ui->HumiditySelectionSlider->setEnabled(false);
    ui->PressureDecreaseButton->setEnabled(false);
    ui->PressureIncreaseButton->setEnabled(false);
    ui->PressureSelectionSlider->setEnabled(false);
    ui->PressureUnitSelectionBox->setEnabled(false);
    ui->TemperatureDecreaseButton->setEnabled(false);
    ui->TemperatureIncreaseButton->setEnabled(false);
    ui->TemperatureUnitSelectionBox->setEnabled(false);
    ui->TemperatureSelectionSlider->setEnabled(false);
    ui->ResolutionSelectionBox->setEnabled(false);
    ui->ThemeSelectionBox->setEnabled(false);
    HideText();
}

void Simulator::SetEnabledTrue()
{
    ui->AngleDecreaseButton->setEnabled(true);
    ui->AngleIncreaseButton->setEnabled(true);
    ui->AngleSelectionSlider->setEnabled(true);
    ui->HumidityDecreaseButton->setEnabled(true);
    ui->HumidityIncreaseButton->setEnabled(true);
    ui->HumiditySelectionSlider->setEnabled(true);
    ui->PressureDecreaseButton->setEnabled(true);
    ui->PressureIncreaseButton->setEnabled(true);
    ui->PressureSelectionSlider->setEnabled(true);
    ui->PressureUnitSelectionBox->setEnabled(true);
    ui->TemperatureDecreaseButton->setEnabled(true);
    ui->TemperatureIncreaseButton->setEnabled(true);
    ui->TemperatureUnitSelectionBox->setEnabled(true);
    ui->TemperatureSelectionSlider->setEnabled(true);
    ui->ResolutionSelectionBox->setEnabled(true);
    ui->ThemeSelectionBox->setEnabled(true);
    UnhideText();
}

void Simulator::SetParametersToLabels()
{
    if(SimUtils.GetPowerState() == ON)
    {
        ui->AngleActualParametersLabel->setText("Angle");
        ui->HumidityActualParametersLabel->setText("Humidity");
        ui->PressureActualParametersLabel->setText("Pressure");
        ui->TemperatureActualParametersLabel->setText("Temperature");
    }
    else
    {
        switch(SimUtils.GetTemperatureUnit())
        {
            case CELSIUS:
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInCelsius);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureUnitSelectionBox->setCurrentIndex(CELSIUS);
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + "° C");
                break;
            case KELVIN:
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInKelvins);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureUnitSelectionBox->setCurrentIndex(KELVIN);
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + " K");
                break;
            case FHARENHEIT:
                SimUtils.SetTemporaryValue(SimUtils.GetTemperatureValue());
                ui->TemperatureSelectionSlider->setMinimum(Constants::minimumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setMaximum(Constants::maximumTemperatureInFharenheit);
                ui->TemperatureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->TemperatureUnitSelectionBox->setCurrentIndex(FHARENHEIT);
                ui->TemperatureActualParametersLabel->setText(QString::number(SimUtils.GetTemperatureValue()) + "° F");
                break;
        }
        switch(SimUtils.GetPressureUnit())
        {
            case MMHG:
                SimUtils.SetTemporaryValue(SimUtils.GetPressureValue());
                ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInMMHg);
                ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInMMHg);
                ui->PressureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->PressureUnitSelectionBox->setCurrentIndex(MMHG);
                ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " mmHg");
                break;
            case KILOPASKALS:
                SimUtils.SetTemporaryValue(SimUtils.GetPressureValue());
                ui->PressureSelectionSlider->setMinimum(Constants::minimumPressureInKilopaskals);
                ui->PressureSelectionSlider->setMaximum(Constants::maximumPressureInKilopaskals);
                ui->PressureUnitSelectionBox->setCurrentIndex(KILOPASKALS);
                ui->PressureSelectionSlider->setValue(SimUtils.GetTemporaryValue());
                ui->PressureActualParametersLabel->setText(QString::number(SimUtils.GetPressureValue()) + " KPa");
                break;
        }
        if(SimUtils.GetAngleValue() > ZERO){ ui->AngleActualParametersLabel->setText(QString::number(SimUtils.GetAngleValue()) + "° right"); }
        else{ ui->AngleActualParametersLabel->setText(QString::number(-SimUtils.GetAngleValue()) + "° left"); }
        ui->AngleSelectionSlider->setValue(SimUtils.GetAngleValue());
        ui->HumiditySelectionSlider->setValue(SimUtils.GetHumidityValue());
        ui->HumidityActualParametersLabel->setText(QString::number(SimUtils.GetHumidityValue()) + "%");
    }
}

void Simulator::SendResponse()
{
    if (!Controller.server.isListening())
    {
        if (!Controller.server.listen(QHostAddress::Any, Controller.GetPORT())) {
            qDebug() << "Error: " << Controller.server.errorString();
            return;
        }
        else { qDebug() << "Server started on port " << Controller.GetPORT(); }
    }
    else { qDebug() << "Server is already listening"; }
        connect(&Controller.server, &QTcpServer::newConnection, [&]()
        {
            socket = Controller.server.nextPendingConnection();
            if (socket->waitForReadyRead())
            {
                QString request = socket->readAll();
                if (request == "GETDATA")
                {
                    QByteArray response;
                    QDataStream out(&response, QIODevice::WriteOnly);
                    out << SimUtils.GetTemperatureValue() << SimUtils.GetTemperatureUnit() << SimUtils.GetPressureValue()
                        << SimUtils.GetPressureUnit() << SimUtils.GetAngleValue() << SimUtils.GetHumidityValue();
                    socket->write(response);
                    socket->flush();
                    socket->waitForBytesWritten();
                }
            }
            socket->close();
        });
}

void Simulator::SetColorOfThePowerButton()
{
    if(SimUtils.GetPowerState() == ON && SimUtils.GetTheme() == LIGHTTHEME)
    {
        ui->PowerButton->setStyleSheet(QString("background-color: rgb(168, 180, 224)"));
    }
    else if(SimUtils.GetPowerState() == ON && SimUtils.GetTheme() == DARKTHEME)
    {
        ui->PowerButton->setStyleSheet(QString("background-color: rgb(132, 143, 181)"));
    }
    else if(SimUtils.GetPowerState() == OFF && SimUtils.GetTheme() == LIGHTTHEME)
    {
        ui->PowerButton->setStyleSheet(QString("background-color: rgb(214, 66, 66)"));
    }
    else if(SimUtils.GetPowerState() == OFF && SimUtils.GetTheme() == DARKTHEME)
    {
        ui->PowerButton->setStyleSheet(QString("background-color: rgb(189, 58, 58)"));
    }
}

void Simulator::SetPowerButtonText()
{
    if(SimUtils.GetPowerState() == ON){ ui->PowerButton->setText("Turn OFF"); }
    else{ ui->PowerButton->setText("Turn ON"); }
}

void Simulator::HideText()
{
    if(SimUtils.GetTheme() == LIGHTTHEME)
    {
        QPalette textPalette = palette();
        textPalette.setColor(QPalette::ButtonText, QColor(Constants::rValueButtonLightTheme, Constants::gValueButtonLightTheme,
                                                  Constants::bValueButtonLightTheme));
        textPalette.setColor(QPalette::WindowText, QColor(Constants::rValueWindowLightTheme, Constants::gValueWindowLightTheme,
                                                  Constants::bValueWindowLightTheme));
        setPalette(textPalette);
    }
    else if(SimUtils.GetTheme() == DARKTHEME)
    {
        QPalette textPalette = palette();
        textPalette.setColor(QPalette::ButtonText, QColor(Constants::rValueButtonDarkTheme, Constants::gValueButtonDarkTheme,
                                                  Constants::bValueButtonDarkTheme));
        textPalette.setColor(QPalette::WindowText, QColor(Constants::rValueWindowDarkTheme, Constants::gValueWindowDarkTheme,
                                                  Constants::bValueWindowDarkTheme));
        setPalette(textPalette);
    }
}
void Simulator::UnhideText()
{
    QPalette textPalette = palette();
    textPalette.setColor(QPalette::ButtonText, QColor(Constants::rValueWindowText, Constants::gValueWindowText,
                                              Constants::bValueWindowText));
    textPalette.setColor(QPalette::WindowText, QColor(Constants::rValueButtonText, Constants::gValueButtonText,
                                              Constants::bValueButtonText));
    setPalette(textPalette);
}



