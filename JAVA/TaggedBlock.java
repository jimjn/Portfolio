package com.example.jingtaoz.eecs40_lames_hw4;

public class TaggedBlock {
    private Block b;
    private int tag;

    public TaggedBlock(Block b, int tag) {
        this.b = b;
        this.tag = tag;
    }

    public Block getB() {
        return b;
    }

    public int getTag() {
        return tag;
    }
}
