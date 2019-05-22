clear all;
a = arduino('COM32', 'Micro', 'Libraries', 'I2C')
pinLED1 = 'D7';
pinLED2 = 'D8';
app = i2cTestApp1();
app.buttonPressed = 0;

topLeftPad= i2cdev(a,'0x8');
topMiddlePad= i2cdev(a,'0x9' );
topRightPad = i2cdev(a,'0xA');
middleLeftPad = i2cdev(a,'0xB');
middleRightPad = i2cdev(a,'0xC');
bottomLeftPad = i2cdev(a,'0xD');
bottomMiddlePad = i2cdev(a,'0x0E');
bottomRightPad = i2cdev(a,'0x08');

while(1)
    try
   addrs = scanI2CBus(a);
    catch ME
        disp("Error Scanning I2C bus");
    end
  app.x08Lamp.Color = 'red';
  app.x09Lamp.Color = 'red';
  app.x0ALamp.Color = 'red';
  app.x0BLamp.Color = 'red';
  app.x0CLamp.Color = 'red';
  app.x0DLamp.Color = 'red';
  app.x0ELamp.Color = 'red';
  app.x0FLamp.Color = 'red';

   for(i=1:length(addrs))
       if(strcmp(addrs{i},"0x8"))
        app.x0CLamp.Color = 'green';
   
        elseif(strcmp(addrs{i},"0x9"))
        app.x08Lamp.Color = 'green';
   
        elseif(strcmp(addrs{i},"0xA"))
        app.x0ALamp.Color = 'green';
   
        elseif(strcmp(addrs{i},"0xB"))
        app.x0BLamp.Color = 'green';
   
       elseif(strcmp(addrs{i},"0xC"))
        app.x09Lamp.Color = 'green';
   
       elseif(strcmp(addrs{i},"0xD"))
        app.x0DLamp.Color = 'green';
   
       elseif(strcmp(addrs{i},"0xE"))
        app.x0FLamp.Color = 'green';
   
       elseif(strcmp(addrs{i},"0xF"))
        app.x0ELamp.Color = 'green';
        end
   end
   if(app.buttonPressed==1)
      switch app.ButtonGroup.SelectedObject.Text
            case '0x08'
                recipient = topLeftPad;
            case '0x09'
                recipient = topMiddlePad;
            case '0x0A'
                recipient = topRightPad;
            case '0x0B'
                recipient = middleLeftPad;
            case '0x0C'
                recipient = middleRightPad;
            case '0x0D'
                recipient = bottomLeftPad;
            case '0x0E'
                recipient = bottomMiddlePad;
            case '0x0F'
                recipient = bottomRightPad;
          otherwise
              recipient = topRightPad;

      end
      write(recipient,dec2hex(app.AnalogThresholdEditField.Value));
      app.buttonPressed =0;
   end
   pause(.1);
        try
            if(read(topMiddlePad, 1, 'uint8') == 121)
                app.pad2.Color = 'green';
            else
                app.pad2.Color = 'red';
            end
            catch ME
                disp("Error reading topMiddlePad ");
        end
        try
            if(read(middleRightPad, 1, 'uint8') == 121)
                app.pad5.Color = 'green';
            else
                app.pad5.Color = 'red';
            end
            catch ME
                disp("Error reading topMiddlePad ");
        end
        try
            if(read(bottomMiddlePad, 1, 'uint8') == 121)
                app.pad7.Color = 'green';
            else
                app.pad7.Color = 'red';
            end
            catch ME
                disp("Error reading bottomMiddlePad ");
        end
        try
            if(read(middleLeftPad, 1, 'uint8') == 121)
                app.pad4.Color = 'green';
            else
                app.pad4.Color = 'red';
            end
            catch ME
                disp("Error reading middleLeftPad ");
        end
        try
            if(read(topLeftPad, 1, 'uint8') == 121)
                app.pad1.Color = 'green';
            else
                app.pad1.Color = 'red';
            end
            catch ME
                disp("Error reading topLeftPad ");
        end
        try
            if(read(topRightPad, 1, 'uint8') == 121)
                app.pad3.Color = 'green';
            else
                app.pad3.Color = 'red';
            end
            catch ME
                disp("Error reading topRightPad ");
        end
        try
            if(read(bottomLeftPad, 1, 'uint8') == 121)
                app.pad6.Color = 'green';
            else
                app.pad6.Color = 'red';
            end
            catch ME
                disp("Error reading bottomLeftPad ");
        end
        try
            if(read(bottomRightPad, 1, 'uint8') == 121)
                app.pad8.Color = 'green';
            else
                app.pad8.Color = 'red';
            end

            catch ME
                disp("Error reading bottomRightPad ");
        end
   pause(.1); 
   
end
%addrs = scanI2CBus(a)
%disp(addrs);
%{
%writeDigitalPin(a,'D7',1);
mspSlave1= i2cdev(a,'0xA');%device(a,'I2CAddress','0xA');%'0x48'
%mspSlave2 = i2cdev(a,'0xB');
while(1)
    data1 = read(mspSlave1, 1, 'uint8');
    %data2 = read(mspSlave2, 1, 'uint8');
    if(data1 == 121)
        disp("pressed");
    else
        writeDigitalPin(a,pinLED1,0)
    end
    %{
    if(data2 == 121)
        writeDigitalPin(a,pinLED2,1)
    else
        writeDigitalPin(a,pinLED2,0)
    end
    %}
    %disp(data1);
    %disp(data2);
    pause(.1);
end
%}
%{
%write(mspSlave, 0, 'uint8');
while(1)
    %write(mspSlave,[0x90 0x00 0x01],'uint8');
    pause(.1);
    %write(mspSlave,144,'uint8');
    %write(mspSlave,0,'uint8');
    %write(mspSlave,2,'uint8');
    %write(mspSlave,[0x90 0x00 0x00],'uint8');
    data = read(mspSlave, 2, 'uint8')
    pause(.1);
end
%}

