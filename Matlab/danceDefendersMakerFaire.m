% Dance Defenders
% EE-Emerge 2019 UC DAVIS
% James Nelson
clear;
clc;
close all;
clear all
%[audio,Fs] = audioread('C:\Users\James Nelson\Desktop\laserSound.wav');

%serial start
if ~isempty(instrfind)
     fclose(instrfind);
      delete(instrfind);
end
s = serial('COM6')
set(s,'BaudRate',9600)
fopen(s)

screenSize = get(0,'screensize');
%Initialize figure
fig = figure('units','normalized','outerposition',[0 0 1 1]);%figure();
hold on
axis tight
%Initialize Game Variables
yVel = -3;%Variable to change with potentiometer
pauseDelay = .005;
addArrowCounter = 0;%Counter for when to add arrow
addArrowNow = 5;%Variable to change with potentiometer,how long to wait to add arrow
startingArrows = 3;
guess = 0;
health = 3; %Initialize health to 3
score = 0; %Initialize score to 0; 10 points for every arrow
N = 20;%number of stars
starsX = randi([1,640],N);
starsY = randi([150,480],N);
%Initialize game
[xCoords,yCoords,arrowNum] = getRandomArrow();
objArrows(1,1) = Arrow(xCoords,yCoords,arrowNum,randi([40,600]),randi([300,460]));
for(i = 2:startingArrows)
    [xCoords,yCoords,arrowNum] = getRandomArrow();
    [posX,posY] = createNewLocation(objArrows);
    objArrows(1,i) = Arrow(xCoords,yCoords,arrowNum,posX,posY);
end
plotScene(fig,objArrows,screenSize,health,score,starsX,starsY);

%Wait for pad input from top row to begin
while(1)
    dataRead =fgets(s);
    size = length(dataRead);
    padding = repmat('3',1,8-size+2);
    padRead = [padding,dataRead];

    if(padRead(1) == '1' || padRead(2) == '1' || padRead(3) == '1')
      break;
   end
   pause(.1);
end

%---------------------------------------------------------------
%Main Game loop
%---------------------------------------------------------------
while(1)
    addArrowCounter = addArrowCounter +1;
    plotScene(fig,objArrows,screenSize,health,score,starsX,starsY);
    objArrows = update(objArrows,yVel);


    %Read arduino input and delete
    [objArrows,score] = readArduinoPins(s,objArrows,score);

    %Check if Arrow has passed line;
    [objArrows,health] = healthCheck(objArrows,health);

    passed = 0;
    %add a new arrow
    if(addArrowCounter >= addArrowNow)
       addArrowCounter = 0;
       [xCoords,yCoords,arrowNum] = getRandomArrow();
       [posX,posY] = createNewLocation(objArrows);
       objArrows(1,length(objArrows)+1) = Arrow(xCoords,yCoords,arrowNum,posX,posY);
    end


    if(health == 0)
        figure(fig);
        plotScene(fig,objArrows,screenSize,health,score,starsX,starsY);
        %Game Title Text
        t1 = text(200,390,"Game Over");
        t1.FontSize = 40;
        t1.Color = 'white';
        health =3;
        score = 0;
        clear objArrows;
        [xCoords,yCoords,arrowNum] = getRandomArrow();
        objArrows(1,1) = Arrow(xCoords,yCoords,arrowNum,randi([40,600]),randi([300,460]));
        for(i = 2:startingArrows)
            [xCoords,yCoords,arrowNum] = getRandomArrow();
            [posX,posY] = createNewLocation(objArrows);
            objArrows(1,i) = Arrow(xCoords,yCoords,arrowNum,posX,posY);
        end
        pause(2);
        %wwait for input from top row pad to continue
        while(1)
            dataRead =fgets(s);
            size = length(dataRead);
            padding = repmat('3',1,8-size+2);
            padRead = [padding,dataRead];

             if(padRead(1) == '1' || padRead(2) == '1' || padRead(3) == '1')
                break;
             end
            pause(.1);
        end
    end%end of if(health==0)

    %pause(pauseDelay);
end%End of while
%----------------------------------------------------------------
%End of Main Loop
%----------------------------------------------------------------
function [objArrowsOut,healthOut] = healthCheck(objArrows,health)
      healthOut = health;
      objArrowsOut = objArrows;

      for(i =1:length(objArrows))
        if(objArrows(1,i).posY < 140)
            healthOut = healthOut -1;
            arrayIndex = ones(1,length(objArrows));
            %arrayIndex(i) = [];
            objArrowsOut(i) = []; %= objArrows(arrayIndex);
            break;
        end
      end


end


function [posX,posY] = createNewLocation(objArrows)
    passed = 0;
    posX = randi([40,600]);
    posY = randi([300,460]);
    if(length(objArrows) > 1)
    while(passed == 0)
          posX = randi([40,600]);
          posY = randi([300,460]);
          for(i =1:length(objArrows))
              obj = objArrows(1,i);
              if(posX > obj.posX-40 && posX < obj.posX+40 && posY > obj.posY-40 && posY < obj.posY+40)
                 passed = 0;
              else
                  passed =1;
              end
          end
    end
    end
end
function plotScene(fig,objArrows,screenSize,health,score,starsX,starsY)

    figure(fig)
    cla;
    %figure('units','normalized','outerposition',[0 0 1 1]);
    xMax = screenSize(3);
    yMax = screenSize(4);
    x = [0,0,xMax,xMax];
    y = [0,yMax,yMax,0];
    %plot Background
    x = [0,0,640,640];
    y = [0,480,480,0];
    %x = [0,0,400,400];
    %y = [0,800,800,0];
    patch(x,y,'black');

    %plot City
    y=[1,1,2,2,2,3,1,1,1,1,3,3,2,2,4,4,3,3,2,2,1,1,3,3,1,1,1,1,2,2,1,1,4,4,3,3,2,2,2,2];
    x=[0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20];
    x = x * 32;
    y = (y * 25)+40;
    plot(x,y,'w');

    %Plot Stars
    plot(starsX,starsY,'w.');

    %Plot Health hearts
    %x
    %y
    t = linspace(-pi,pi, 350);
    x =      t .* sin( pi * .872*sin(t)./t);
    y = -abs(t) .* cos(pi * sin(t)./t);
    x1 = x*10 + 480;
    y1 = y*10 + 40;
    x2 = x*10 + 530;
    y2 = y*10 + 40;
    x3 = x*10 + 580;
    y3 = y*10 + 40;
    if(health == 3)
        patch(x1,y1,'r');
        patch(x2,y2,'r');
        patch(x3,y3,'r');
    elseif(health ==2)
        plot(x1,y1,'r');
        patch(x2,y2,'r');
        patch(x3,y3,'r');
    elseif(health == 1)
        plot(x1,y1,'r');
        plot(x2,y2,'r');
        patch(x3,y3,'r');
    else
        plot(x1,y1,'r');
        plot(x2,y2,'r');
        plot(x3,y3,'r');
    end
    %Plot Score
    txt = strcat("Score: ",num2str(score));
    scoreTxt = text(10,30,txt);
    scoreTxt.Color = 'white';
    scoreTxt.FontSize = 25;
    %Plot Arrows
    for(i =1:length(objArrows))
        obj = objArrows(1,i);
        patch(obj.xCoords+obj.posX, obj.yCoords+obj.posY,'green');
    end

end

function objArrowsReturn = update(objArrows,yVel)
    for(i =1:length(objArrows))
        objArrows(1,i) = objArrows(1,i).update(yVel);
    end

    objArrowsReturn = objArrows;
end

function [xCoords,yCoords,arrowNum] = getRandomArrow()

    randNum = randi([1,8]);
    switch(randNum)
        %{
        case 1
            xCoords = [17,20,8,10,0,0,3];
            yCoords = [0,3,15,20,20,10,12];
        %}
        case 2
            xCoords = [8,12,12,20,10,0,8];
            yCoords = [0,0,10,10,20,10,10];

        case 3
            xCoords = [10,20,20,17,3,0,12];
            yCoords = [20,20,10,12,0,3,15];
        %{
        case 4
            xCoords = [10,10,20,20,10,10,0];
            yCoords = [20,12,12,8,8,0,10];
          %}
        case 5
            xCoords = [10,20,10,10,0,0,10];
            yCoords = [20,10,0,8,8,12,12];


        case 6
            xCoords = [17,20,8,10,0,0,3];
            yCoords = [20,17,3,0,0,10,8];

        case 7
            xCoords = [10,20,12,12,8,8,0];
            yCoords = [0,10,10,20,20,10,10];

        case 8
            xCoords = [3,17,20,20,10,12,0];
            yCoords = [20,8,10,0,0,3,17];
        otherwise
            xCoords = [3,17,20,20,10,12,0];
            yCoords = [20,8,10,0,0,3,17];
            randNum = 8;
    end
    arrowNum = randNum;
end

function [objArrows,deleteCounter] = deleteGuess(guess,arrows)
        %length arrows must be greater than 1 in order to delet it
        deleteCounter = 0;
        for(i =1:length(arrows))
            arrowNum = arrows(1,i).arrowNum;
            if(guess == arrowNum)
                correctguess(i) = 1;
                deleteCounter = deleteCounter+1;
            else
                correctguess(i) = 0;
            end
        end
       % correctGuessLocation = (arrows(1,:).arrowNum == guess);
        objArrows = arrows(~correctguess);
end
function [objArrows,scoreOut] = readArduinoPins(s,arrows,score)
        objArrows = arrows;
        scoreOut = score;
        deleteCounter = 0;
        guess = 0;
        try
            dataRead =fgets(s);
            size = length(dataRead);
            padding = repmat('3',1,8-size+2);
            padRead = [padding,dataRead];
            if(padRead(1) == '1')%bit 7,bottomRightPad
                guess = 8;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(padRead(2) == '1')%bit 6,bottomMiddlePad
                guess = 7;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(padRead(3) == '1')%bit 5,bottomLeftPad
                guess = 6;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(padRead(4) == '1')%bit 4,middleRightPad
                guess = 5;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(padRead(5) == '1')%bit3,middleLeftPad
                guess = 4;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(padRead(6) == '1')%bit2,topRightPad
                guess = 3;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(padRead(7) == '1')%bit1,topMiddlePad
                guess = 2;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(padRead(8) == '1')%bit0,topRightPad
                guess = 1;
                [objArrows,deleteCounter] = deleteGuess(guess,objArrows);
            end
            if(guess ~=0)
               %play sound
               %sound(audio,Fs);
            end
        catch ME
            padRead = dec2bin(0,8);
            disp("UART Error");
        end


        scoreOut = score + (deleteCounter *10);%each arrow is 10 points

end
