package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;

public class Beetle extends Enemy implements GameObject{

    private int state;
    public Beetle(Bitmap character,int x, int y){

    }

    @Override
    public void draw(Canvas canvas) {

    }

    @Override
    public void update() {

    }
    public void setEnemyState(int state){
        this.state = state;
    }
    public int getEnemyState(){
        return state;
    }
}
