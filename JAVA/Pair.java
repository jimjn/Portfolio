package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Paint;

public class Pair {
    private int a;
    private int b;

    public Pair(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public int getA() {
        return a;
    }

    public int getB() {
        return b;
    }

    public boolean inRange(int i) {
        if (i >= a && i <= b) {
            return true;
        } else {
            return false;
        }
    }

    @Override
    public String toString() {
        return "a:" + a + ", b:" + b;
    }
}
