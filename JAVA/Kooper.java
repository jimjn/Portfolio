package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public class Kooper extends Enemy implements GameObject{
    private final float offsetMultiplier = 1f;

    /*Motion of Kooper
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

    private int last_pixel_moved_horizontally =0;
    private int pixels_moved_horizontally;

    private int min_pixel_view_range;//if the view rectange is in this range then the character will be drawn
    private int max_pixel_view_range;

    private int state;//0 = left, 1= right, 2 is defeated

    public Kooper(Bitmap character,int x, int y){
        //crop out kooper in character bitmap then send to super constructor
        super(Bitmap.createBitmap(character,337,0,47,100),Bitmap.createBitmap(character,480,0,47,100),x,y);

        currentDirection = 0;
        currentFrame = 1;
    }

    @Override
    public void draw(Canvas canvas) {
        //System.out.println("Printing Kooper");
        if(state ==0)//moving left
            canvas.drawBitmap(super.getCharacter(),super.getX(),super.getY(),null);
        else if(state == 1)//moving right
            canvas.drawBitmap(super.getCharacterRight(),super.getX(),super.getY(),null);
        else if(state == 2)
            canvas.drawBitmap(super.getCharacterDefeatState(),super.getX(),super.getY(),null);


        //Test to see the rectangle around bitmap
        /*Paint paint = new Paint();
        paint.setColor(Color.GREEN);
        canvas.drawRect(super.getEnemyRect(),paint);*/
    }

    @Override
    public void update() {
        super.update();

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
        }
    }
    public void setEnemyState(int state){
        this.state = state;
    }
    public int getEnemyState(){
        return state;
    }
}
