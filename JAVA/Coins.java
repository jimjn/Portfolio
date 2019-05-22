package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;

import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public class Coins extends Item {
    public Coins(Bitmap coinBitmap, int x, int y) {
        super(coinBitmap,x,y);
    }

    public void onCollide(Mario m) {
        m.addPoints(200);
    }
}
