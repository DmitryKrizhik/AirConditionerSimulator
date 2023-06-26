#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QMainWindow>
#include "simulatorutils.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Simulator; }
QT_END_NAMESPACE

class Simulator : public QMainWindow
{
    Q_OBJECT

public:
    Simulator(QWidget *parent = nullptr);
    ~Simulator();


private slots:
    /**
     * @brief Event handler for the "Resolution Selection Box" value change.
     * @param newResolutionType The new resolution selected by the user from the resolution selection box.
     */
    void on_ResolutionSelectionBox_activated(int newResolutionType);

    /**
     * @brief Event handler for the "Theme Selection Box" value change.
     * @param newThemeType The new theme selected by the user from the theme selection box.
     */
    void on_ThemeSelectionBox_activated(int newThemeType);

    /**
     * @brief Event handler for the "Temperature Unit Selection Box" value change.
     * @param newTemperatureType The new temperature unit selected by the user from the temperature unit selection box.
     */
    void on_TemperatureUnitSelectionBox_activated(int newTemperatureUnit);

    /**
     * @brief Event handler for the "Pressure Unit Selection Box" value change.
     * @param newPressureType The new pressure unit selected by the user from the pressure unit selection box.
     */
    void on_PressureUnitSelectionBox_activated(int newPressureInit);

    /**
     * @brief Event handler for the "Temperature Selection Slider" value change.
     * @param newTemperatureValue The new temperature value selected by the user using the temperature selection slider.
     */
    void on_TemperatureSelectionSlider_valueChanged(int newTemperatureValue);

    /**
     * @brief Event handler for the "Pressure Selection Slider" value change.
     * @param newPressureUnit The new pressure value selected by the user using the pressure selection slider.
     */
    void on_PressureSelectionSlider_valueChanged(int newPressureValue);

    /**
     * @brief Event handler for the "Humidity Selection Slider" value change.
     * @param newHumidityValue The new humidity value selected by the user using the humidity selection slider.
     */
    void on_HumiditySelectionSlider_valueChanged(int newHumidityValue);

    /**
     * @brief Event handler for the "Angle Selection Slider" value change.
     * @param newAngleOfRotationValue The new angle of rotation value selected by the user using the angle selection slider.
     */
    void on_AngleSelectionSlider_valueChanged(int newAngleValue);

    /**
     * @brief Event handler for the "Close Window" button click.
     * This method calls the TurnOffSimulator() function and stop the simulator and terminates the application.
     * @see TurnOffSimulator()
     */
    void on_CloseWindowButton_clicked();

    /**
     * @brief Event handler for the "Temperature Increase Button" click.
     * Increases the temperature value by 1
     */
    void on_TemperatureIncreaseButton_clicked();

    /**
     * @brief Event handler for the "Temperature Decrease Button" click.
     * Decreases the temperature value by 1
     */
    void on_TemperatureDecreaseButton_clicked();

    /**
     * @brief Event handler for the "Pressure Increase Button" click.
     * Increases the pressure value by 1
     */
    void on_PressureIncreaseButton_clicked();

    /**
     * @brief Event handler for the "Pressure Decrease Button" click.
     * Increases the pressure value by 1
     */
    void on_PressureDecreaseButton_clicked();

    /**
     * @brief Event handler for the "Humidity Increase Button" click.
     * Increases the humidity value by 1
     */
    void on_HumidityIncreaseButton_clicked();

    /**
     * @brief Event handler for the "Humidity Decrease Button" click.
     * Decreases the humidity value by 1
     */
    void on_HumidityDecreaseButton_clicked();

    /**
     * @brief Event handler for the "Angle Increase Button" click.
     * Increases the angle value by 1
     */
    void on_AngleIncreaseButton_clicked();

    /**
     * @brief Event handler for the "Angle Increase Button" click.
     * Decreases the Angle value by 1
     */
    void on_AngleDecreaseButton_clicked();

    /**
     * @brief Event handler for the "Power Button" click.
     *
     * This method checks the current power state of the simulator using the SimUtils class method GetPowerState().
     * If the simulator is currently on, the method calls TurnOffSimulator() to turn it off. If the simulator is currently off,
     * the method calls TurnOnSimulator() to turn it on. The application's user interface is updated to reflect the new power state.
     */
    void on_PowerButton_clicked();

    /**
     * @brief Turns on the simulator and updates the user interface accordingly.
     * @see ReadParametersFromFile(), SetParametersToLabels(), SetPowerState(), SetColorOfThePowerButton(),
     * ReadTCPSettingsFromFile(), SetEnabledTrue()
     */
    void TurnOnSimulator();

    /**
     * @brief Turns off the simulator and updates the user interface accordingly.
     * @see WriteParametersInFile(), SetEnabledFalse(), SetParametersToLabels(), SetPowerButtonText(),
     * SetColorOfThePowerButton(), SetPowerState()
     */
    void TurnOffSimulator();

    /**
     * @brief Enables the simulator and updates the user interface accordingly.
     * @see UnhideText()
     */
    void SetEnabledTrue();

    /**
     * @brief Disables the simulator and updates the user interface accordingly.
     * @see HideText()
     */
    void SetEnabledFalse();


    /**
     * @brief Sets the user interface to the light theme and updates the color scheme accordingly.
     * @see SetColorOfThePowerButton()
     */
    void SetLightTheme();

    /**
     * @brief Sets the user interface to the dark theme and updates the color scheme accordingly.
     * @see SetColorOfThePowerButton()
     */
    void SetDarkTheme();

    /**
     * @brief Sets the actual parameters labels to display the current values of the simulation parameters.
     */
    void SetParametersToLabels();

    /**
     * @brief Sets the color of the power button based on the current power state and theme.
     */
    void SetColorOfThePowerButton();

    /**
     * @brief Sets the text of the power button based on the current power state.
     */
    void SetPowerButtonText();

    /**
     * @brief Starts a TCP server to send response data to incoming requests.
     */
    void SendResponse();

    /**
     * @brief Changes the color of text back to default.
     */
    void UnhideText();

    /**
     * @brief Changes the color of text to match the current theme.
     * Hide the text
     */
    void HideText();


public:
    qint16 tempTemperatureValue;
    QTcpSocket* socket;
private:
    Ui::Simulator *ui;
};



#endif // SIMULATOR_H
