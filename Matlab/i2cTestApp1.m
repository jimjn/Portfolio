classdef i2cTestApp1 < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        UIFigure                       matlab.ui.Figure
        PadI2CLabel                    matlab.ui.control.Label
        x0DLampLabel                   matlab.ui.control.Label
        x0ALampLabel                   matlab.ui.control.Label
        x0DLamp                        matlab.ui.control.Lamp
        x08LampLabel                   matlab.ui.control.Label
        x08Lamp                        matlab.ui.control.Lamp
        x0ELampLabel                   matlab.ui.control.Label
        x0ELamp                        matlab.ui.control.Lamp
        x09LampLabel                   matlab.ui.control.Label
        x09Lamp                        matlab.ui.control.Lamp
        x0FLampLabel                   matlab.ui.control.Label
        x0FLamp                        matlab.ui.control.Lamp
        x0BLampLabel                   matlab.ui.control.Label
        x0BLamp                        matlab.ui.control.Lamp
        x0CLampLabel                   matlab.ui.control.Label
        x0CLamp                        matlab.ui.control.Lamp
        x0ALamp                        matlab.ui.control.Lamp
        ButtonGroup                    matlab.ui.container.ButtonGroup
        x0DButton                      matlab.ui.control.RadioButton
        x0AButton                      matlab.ui.control.RadioButton
        x08Button                      matlab.ui.control.RadioButton
        x0EButton                      matlab.ui.control.RadioButton
        x09Button                      matlab.ui.control.RadioButton
        x0FButton                      matlab.ui.control.RadioButton
        x0BButton                      matlab.ui.control.RadioButton
        x0CButton                      matlab.ui.control.RadioButton
        AnalogThresholdEditFieldLabel  matlab.ui.control.Label
        AnalogThresholdEditField       matlab.ui.control.NumericEditField
        ProgramButton                  matlab.ui.control.Button
        pad1                           matlab.ui.control.Lamp
        pad5                           matlab.ui.control.Lamp
        pad4                           matlab.ui.control.Lamp
        pad2                           matlab.ui.control.Lamp
        pad3                           matlab.ui.control.Lamp
        pad7                           matlab.ui.control.Lamp
        pad8                           matlab.ui.control.Lamp
        pad6                           matlab.ui.control.Lamp
        PadStateLabel                  matlab.ui.control.Label
    end
    properties (Access = public)
       buttonPressed 
    end
    methods (Access = private)

        % Button pushed function: ProgramButton
        function ProgramButtonPushed(app, event)
            app.buttonPressed = 1;
            disp(app.AnalogThresholdEditField.Value);
            disp(dec2hex(app.AnalogThresholdEditField.Value));
        end
    end

    % App initialization and construction
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)
            app.buttonPressed = 0;
            % Create UIFigure
            app.UIFigure = uifigure;
            app.UIFigure.Position = [100 100 640 480];
            app.UIFigure.Name = 'UI Figure';

            % Create PadI2CLabel
            app.PadI2CLabel = uilabel(app.UIFigure);
            app.PadI2CLabel.Position = [270 394 49 22];
            app.PadI2CLabel.Text = 'Pad I2C';

            % Create x0DLampLabel
            app.x0DLampLabel = uilabel(app.UIFigure);
            app.x0DLampLabel.HorizontalAlignment = 'right';
            app.x0DLampLabel.Position = [153 344 34 22];
            app.x0DLampLabel.Text = '0x0D';

            % Create x0DLamp
            app.x0DLamp = uilamp(app.UIFigure);
            app.x0DLamp.Position = [202 344 20 20];

            % Create x0ALampLabel
            app.x0ALampLabel = uilabel(app.UIFigure);
            app.x0ALampLabel.HorizontalAlignment = 'right';
            app.x0ALampLabel.Position = [251 344 33 22];
            app.x0ALampLabel.Text = '0x0A';

            % Create x0ALamp
            app.x0ALamp = uilamp(app.UIFigure);
            app.x0ALamp.Position = [299 344 20 20];

            % Create x08LampLabel
            app.x08LampLabel = uilabel(app.UIFigure);
            app.x08LampLabel.HorizontalAlignment = 'right';
            app.x08LampLabel.Position = [359 343 32 22];
            app.x08LampLabel.Text = '0x09';

            % Create x08Lamp
            app.x08Lamp = uilamp(app.UIFigure);
            app.x08Lamp.Position = [406 343 20 20];
            app.x08Lamp.Color = 'red';

            % Create x0ELampLabel
            app.x0ELampLabel = uilabel(app.UIFigure);
            app.x0ELampLabel.HorizontalAlignment = 'right';
            app.x0ELampLabel.Position = [153 291 33 22];
            app.x0ELampLabel.Text = '0x0F';

            % Create x0ELamp
            app.x0ELamp = uilamp(app.UIFigure);
            app.x0ELamp.Position = [201 291 20 20];

            % Create x09LampLabel
            app.x09LampLabel = uilabel(app.UIFigure);
            app.x09LampLabel.HorizontalAlignment = 'right';
            app.x09LampLabel.Position = [357 291 32 22];
            app.x09LampLabel.Text = '0x0C';

            % Create x09Lamp
            app.x09Lamp = uilamp(app.UIFigure);
            app.x09Lamp.Position = [404 291 20 20];

            % Create x0FLampLabel
            app.x0FLampLabel = uilabel(app.UIFigure);
            app.x0FLampLabel.HorizontalAlignment = 'right';
            app.x0FLampLabel.Position = [154 241 32 22];
            app.x0FLampLabel.Text = '0x0E';

            % Create x0FLamp
            app.x0FLamp = uilamp(app.UIFigure);
            app.x0FLamp.Position = [201 241 20 20];

            % Create x0BLampLabel
            app.x0BLampLabel = uilabel(app.UIFigure);
            app.x0BLampLabel.HorizontalAlignment = 'right';
            app.x0BLampLabel.Position = [253 241 33 22];
            app.x0BLampLabel.Text = '0x0B';

            % Create x0BLamp
            app.x0BLamp = uilamp(app.UIFigure);
            app.x0BLamp.Position = [301 241 20 20];

            % Create x0CLampLabel
            app.x0CLampLabel = uilabel(app.UIFigure);
            app.x0CLampLabel.HorizontalAlignment = 'right';
            app.x0CLampLabel.Position = [356 241 34 22];
            app.x0CLampLabel.Text = '0x08';

            % Create x0CLamp
            app.x0CLamp = uilamp(app.UIFigure);
            app.x0CLamp.Position = [405 241 20 20];

            % Create ButtonGroup
            app.ButtonGroup = uibuttongroup(app.UIFigure);
            app.ButtonGroup.Title = 'Button Group';
            app.ButtonGroup.Position = [31 10 123 210];

            % Create x0DButton
            app.x0DButton = uiradiobutton(app.ButtonGroup);
            app.x0DButton.Text = '0x0D';
            app.x0DButton.Position = [11 164 58 22];
            app.x0DButton.Value = true;

            % Create x0AButton
            app.x0AButton = uiradiobutton(app.ButtonGroup);
            app.x0AButton.Text = '0x0A';
            app.x0AButton.Position = [11 142 65 22];

            % Create x08Button
            app.x08Button = uiradiobutton(app.ButtonGroup);
            app.x08Button.Text = '0x08';
            app.x08Button.Position = [11 120 65 22];

            % Create x0EButton
            app.x0EButton = uiradiobutton(app.ButtonGroup);
            app.x0EButton.Text = '0x0E';
            app.x0EButton.Position = [11 100 58 22];

            % Create x09Button
            app.x09Button = uiradiobutton(app.ButtonGroup);
            app.x09Button.Text = '0x09';
            app.x09Button.Position = [11 78 65 22];

            % Create x0FButton
            app.x0FButton = uiradiobutton(app.ButtonGroup);
            app.x0FButton.Text = '0x0F';
            app.x0FButton.Position = [11 56 65 22];

            % Create x0BButton
            app.x0BButton = uiradiobutton(app.ButtonGroup);
            app.x0BButton.Text = '0x0B';
            app.x0BButton.Position = [11 38 58 22];

            % Create x0CButton
            app.x0CButton = uiradiobutton(app.ButtonGroup);
            app.x0CButton.Text = '0x0C';
            app.x0CButton.Position = [11 16 65 22];

            % Create AnalogThresholdEditFieldLabel
            app.AnalogThresholdEditFieldLabel = uilabel(app.UIFigure);
            app.AnalogThresholdEditFieldLabel.HorizontalAlignment = 'right';
            app.AnalogThresholdEditFieldLabel.Position = [175 143 100 22];
            app.AnalogThresholdEditFieldLabel.Text = 'Analog Threshold';

            % Create AnalogThresholdEditField
            app.AnalogThresholdEditField = uieditfield(app.UIFigure, 'numeric');
            app.AnalogThresholdEditField.Position = [290 143 100 22];

            % Create ProgramButton
            app.ProgramButton = uibutton(app.UIFigure, 'push');
            app.ProgramButton.ButtonPushedFcn = createCallbackFcn(app, @ProgramButtonPushed, true);
            app.ProgramButton.Position = [291 109 100 22];
            app.ProgramButton.Text = 'Program';

            % Create pad1
            app.pad1 = uilamp(app.UIFigure);
            app.pad1.Position = [492 354 20 20];

            % Create pad5
            app.pad5 = uilamp(app.UIFigure);
            app.pad5.Position = [559 320 20 20];

            % Create pad4
            app.pad4 = uilamp(app.UIFigure);
            app.pad4.Position = [492 320 20 20];

            % Create pad2
            app.pad2 = uilamp(app.UIFigure);
            app.pad2.Position = [525 354 20 20];

            % Create pad3
            app.pad3 = uilamp(app.UIFigure);
            app.pad3.Position = [559 354 20 20];

            % Create pad7
            app.pad7 = uilamp(app.UIFigure);
            app.pad7.Position = [525 291 20 20];

            % Create pad8
            app.pad8 = uilamp(app.UIFigure);
            app.pad8.Position = [559 291 20 20];

            % Create pad6
            app.pad6 = uilamp(app.UIFigure);
            app.pad6.Position = [492 291 20 20];

            % Create PadStateLabel
            app.PadStateLabel = uilabel(app.UIFigure);
            app.PadStateLabel.Position = [511 394 58 22];
            app.PadStateLabel.Text = 'Pad State';
        end
    end

    methods (Access = public)

        % Construct app
        function app = i2cTestApp1

            % Create and configure components
            createComponents(app)
            app.buttonPressed = 0;
            % Register the app with App Designer
            registerApp(app, app.UIFigure)

            if nargout == 0
                clear app
            end
        end

        % Code that executes before app deletion
        function delete(app)

            % Delete UIFigure when app is deleted
            delete(app.UIFigure)
        end
    end
end