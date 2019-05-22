package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.Rect;
import android.icu.text.SymbolTable;
import android.util.Log;

import java.util.ArrayList;

import static com.example.jingtaoz.eecs40_lames_hw4.Level.enemyType.goomba;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.enemyType.pkoopa;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.itemType.coin;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.itemType.fireflower;

public class Level2 extends Level {

    public Level2(Bitmap fireball1, Bitmap fireball2, Bitmap fireball3, Bitmap fireball4,
                  Bitmap goombaL, Bitmap goombaR, Bitmap goombaF, Bitmap marioBitmap,
                  Bitmap smallMarioBitmap, Bitmap fireMarioBitmap, Bitmap enemiesBitmap,
                  Bitmap itemsBitmap, Bitmap background, Bitmap brickBitmap, Bitmap coinBlockBitmap,
                  Bitmap koopaBitmap, Bitmap koopasBitmap, Bitmap pkoopaBitmap, Bitmap coinBitmap,
                  Bitmap mushroomBitmap, Bitmap fireFlowerBitmap, int height, int width) {

        super(fireball1, fireball2, fireball3, fireball4, goombaL, goombaR, goombaF, marioBitmap,
                smallMarioBitmap, fireMarioBitmap, enemiesBitmap, itemsBitmap, background,
                brickBitmap, coinBlockBitmap, koopaBitmap, koopasBitmap, pkoopaBitmap, coinBitmap,
                mushroomBitmap, fireFlowerBitmap, height, width);

        super.setEndLevelRect(6850);
    }

    public void setFallingRects() {

        addFallingRect(new Rect(0, 800, 2000, 802));
    }

    public void populateEnemies() {
        addEnemy(goomba, 4500, 740 + 40);
        addEnemy(goomba, 4550, 740 + 40);
        addEnemy(goomba, 4600, 740 + 40);
        addEnemy(pkoopa, 2400, 600);
        addEnemy(goomba, 7500, 740 + 40);
    }

    public void addBlocks() {
        super.addStaircase(2000, 1);
        super.addStaircase(2500, -1);
        super.addStaircase(4700, 1);

        super.addRowOfBricks(5200, 650, 6);

        super.addStaircase(5800, 1);

        super.addRowOfBricks(6300, 650, 8);

    }

    public void addGaps() {
        super.addGap(1050, 1290);
        super.addGap(3160, 3310);
        super.addGap(3480,3630);
        super.addGap(4600, 5150);
        super.addGap(5790, 6350);
        /*
        super.addGap(1000, 1230);
        super.addGap(3020, 3180);
        super.addGap(3330, 3490);
        super.addGap(4410, 4940);
        super.addGap(5565, 6105);
        */
    }

    @Override
    public void addItems() {
        super.addItem(fireflower, 500, 650);
        super.addRowOfCoins(2400,550,2);
        super.addRowOfCoins(6326,550,8);
    }
}
