package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;

public class Bloober extends Enemy implements GameObject{
/*WILL BE A GOOMA INSTEAD BECAUSE THAT IS MUCH EASIER*/
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

    private int last_pixel_moved_horizontally =0;
    private int pixels_moved_horizontally;

    private int min_pixel_view_range;//if the view rectange is in this range then the character will be drawn
    private int max_pixel_view_range;

    private int state;//0 = left, 1= right, 2 is defeated


    public Bloober(Bitmap character,int x, int y){

    }

    @Override
    public void update() {

    }

    @Override
    public void draw(Canvas canvas) {
        //System.out.println("Printing Gooma");
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

    public void setEnemyState(int state){
        this.state = state;
    }
    public int getEnemyState(){
        return state;
    }
}
