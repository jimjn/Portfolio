classdef Arrow
    properties
        posX
        posY
        xCoords
        yCoords
        arrowNum
    end

    methods
        function obj = Arrow(xCoordsIn,yCoordsIn,arrowNumIn,posXin,posYin)
            obj.xCoords = xCoordsIn;
            obj.yCoords = yCoordsIn;
            %obj.posX = randi([40,600]);
            %obj.posY = randi([300,460]);
            obj.posX = posXin;
            obj.posY = posYin;
            obj.arrowNum = arrowNumIn;
        end
        function obj = update(obj,yVel)
            obj.posY = obj.posY + yVel;
        end
        function draw(fig)
            figure(fig)
            patch(obj.xCoords+obj.posX, obj.yCoords+obj.posY,'blue');
        end
    end
end
