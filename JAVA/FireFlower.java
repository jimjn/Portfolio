package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;

public class FireFlower extends Item {

    public FireFlower(Bitmap fireFlowerBitmap, int x, int y) {
        super(fireFlowerBitmap, x, y);
    }

    @Override
    public void onCollide(Mario m) {
        m.setMarioForm(2);
        m.addPoints(1000);
    }
}
