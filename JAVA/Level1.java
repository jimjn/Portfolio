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
import static com.example.jingtaoz.eecs40_lames_hw4.Level.enemyType.koopa;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.enemyType.pkoopa;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.itemType.coin;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.itemType.fireflower;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.itemType.mushroom;

public class Level1 extends Level {
    public Level1(Bitmap fireball1, Bitmap fireball2, Bitmap fireball3, Bitmap fireball4,
                  Bitmap goombaL, Bitmap goombaR, Bitmap goombaF, Bitmap marioBitmap,
                  Bitmap smallMarioBitmap, Bitmap fireMarioBitmap, Bitmap enemiesBitmap,
                  Bitmap itemsBitmap, Bitmap background, Bitmap brickBitmap, Bitmap coinBlockBitmap,
                  Bitmap koopaBitmap, Bitmap koopasBitmap, Bitmap pkoopaBitmap, Bitmap coinBitmap,
                  Bitmap mushroomBitmap, Bitmap fireFlowerBitmap, int height, int width) {

        super(fireball1, fireball2, fireball3, fireball4, goombaL, goombaR, goombaF, marioBitmap,
                smallMarioBitmap, fireMarioBitmap, enemiesBitmap, itemsBitmap, background,
                brickBitmap, coinBlockBitmap, koopaBitmap, koopasBitmap, pkoopaBitmap, coinBitmap,
                mushroomBitmap, fireFlowerBitmap, height, width);

        super.setEndLevelRect(5850);
    }

    public void setFallingRects() {
        super.addFallingRect(new Rect(0, 800, 2000, 802));
    }

    public void populateEnemies() {
        super.addEnemy(goomba, 1400, 780);

        super.addEnemy(goomba, 1400, 780);
        super.addEnemy(goomba, 1450, 780);
        super.addEnemy(goomba, 1500, 780);
        super.addEnemy(goomba, 2500, 780);
        super.addEnemy(goomba, 2550, 780);
        super.addEnemy(goomba, 2600, 780);

        super.addEnemy(koopa, 3500, 450);
        super.addEnemy(koopa, 3600, 450);

        super.addEnemy(pkoopa, 4000, 500);
        super.addEnemy(pkoopa, 4100, 550);
        super.addEnemy(pkoopa, 4200, 600);
        super.addEnemy(pkoopa, 4300, 650);
        super.addEnemy(pkoopa, 4400, 700);
        super.addEnemy(pkoopa, 4500, 750);
        super.addEnemy(pkoopa, 4600, 800);
        super.addEnemy(pkoopa, 4700, 850);
    }

    public void addBlocks() {
        super.addBlock(800, 650);

        super.addBlock(968, 650);
        super.addBlock(1010, 650);
        super.addBlock(1051, 650);
        super.addBlock(1092, 650);
        super.addBlock(1133, 650);

        super.addBlock(1051, 450);

        /*between second and third hole*/
        for (int i = 1; i < 5; i++) {
            super.addBlock(2750 + (42 * (i - 1)), 650);
        }

        for (int i = 1; i < 15; i++) {
            super.addBlock(3000 + (42 * (i - 1)), 550);
        }
    }

    public void addGaps() {
        super.addGap(1770, 1940);
        super.addGap(3130, 3370);
        /*
        super.addGap(1695, 1850);
        super.addGap(3010, 3235);
        */
    }

    public void addItems() {
        super.addItem(coin, 700, 650);
        super.addItem(mushroom, 600, 650);
        super.addItem(fireflower, 500, 650);
        super.addRowOfCoins(4000,650,15);
    }






}
