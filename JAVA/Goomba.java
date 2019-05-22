package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;

import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public class Goomba extends Enemy implements GameObject{
    /*Motion of Gooma
     * Moves horizontally left a certain amount of pixels
     * then moves right horizontally a cerntain amount of pixels
     *
     * */
    private final int framesPerMove = 120;//one move is one direction (left or right)
    /*We probably want one direction to take about 4 seconds
     * At 30 frames per seconds that's 120 frames per move
     * */
    private final int pixelsPerFrame = 4;//
    private int currentDirection;//0 Left, 1 Right
    private int currentFrame;
    private int walkingFrame;

    private int last_pixel_moved_horizontally =0;
    private int pixels_moved_horizontally;

    private int min_pixel_view_range;//if the view rectange is in this range then the character will be drawn
    private int max_pixel_view_range;

    private int state;//0 = left, 1= right, 2 is defeated

    private Bitmap goombaL;
    private Bitmap goombaR;
    private Bitmap goombaF;

    private int defeated;

    public Goomba(Bitmap goombaL,Bitmap goombaR,Bitmap goombaF, int x, int y){
        super(goombaL,goombaF,x,y);
        this.goombaL = goombaL;
        this.goombaR = goombaR;
        this.goombaF = goombaF;

        currentDirection = 0;
        currentFrame = 1;
        walkingFrame = 1;
        defeated = 0;
    }

    @Override
    public void update() {
        super.update();
        pixels_moved_horizontally = getPixels_moved_horizontally();

        //dont know why but u have to scale it by 1.9 to work better (not good but not very noticeable)
        /*
        int moveAmt = (int) ((last_pixel_moved_horizontally - pixels_moved_horizontally) * Constants.offsetMultiplier);
        if (last_pixel_moved_horizontally > pixels_moved_horizontally) {//old > new -> mario moved left
            super.setX(super.getX() + moveAmt);
            super.updateRect(moveAmt,0);
        } else {//mario moved right
            super.setX(super.getX() + moveAmt);
            super.updateRect(moveAmt, 0);
        }
        */

        if(state != 2) {
            if (currentFrame == 121) {
                //switch direction
                if (currentDirection == 0)
                    currentDirection = 1;
                else
                    currentDirection = 0;
                //reset frame count
                currentFrame = 1;
            }

            if (currentDirection == 0) {//moving left
                super.setX(super.getX() - pixelsPerFrame);
                super.updateRect((pixelsPerFrame * (-1)), 0);
                state = 0;
            } else {//moving right
                super.setX(super.getX() + pixelsPerFrame);
                super.updateRect(pixelsPerFrame, 0);
                state = 1;
            }

            currentFrame++;
            walkingFrame++;
        }
    }

    @Override
    public void draw(Canvas canvas) {

            if(defeated == 0) {
                if(walkingFrame <= 9)
                    canvas.drawBitmap(goombaL, super.getX(), super.getY(), null);
                else if(walkingFrame > 9 && walkingFrame <18)
                    canvas.drawBitmap(goombaR, super.getX(), super.getY(), null);
                else {
                    walkingFrame = 1;
                    canvas.drawBitmap(goombaR, super.getX(), super.getY(), null);
                }


                if (getEnemyState() == 2) {
                    canvas.drawBitmap(super.getCharacterDefeatState(), super.getX(), super.getY(), null);
                    defeated = 1;
                }
            }
            else if(defeated >=1 && defeated <=60)//keep drawing defeated state for 2 seconds
            {
                canvas.drawBitmap(super.getCharacterDefeatState(), super.getX(), super.getY(), null);
                defeated ++;
            }

        //Test to see the rectangle around bitmap
        /*Paint paint = new Paint();
        paint.setColor(Color.GREEN);
        canvas.drawRect(super.getEnemyRect(),paint);*/
    }

    public void setEnemyState(int state){
        this.state = state;
    }
    public int getEnemyState(){
        return state;
    }
}

