package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;

public class Mushroom extends Item {

    public Mushroom(Bitmap mushroomBitmap, int x, int y) {
        super(mushroomBitmap, x, y);
    }

    public void onCollide(Mario m) {
        if (!(m.getMarioForm() == 2)){
            m.setMarioForm(1);
        }
        m.addPoints(1000);
    }
}
