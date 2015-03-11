package com.u17webplib;

/**
 * Created by Administrator on 2015/3/7.
 */
public class webplib {
    static {
        System.loadLibrary("u17webp");
    }
    public native static int getVersion();
    public native static byte[] getWebPDecodeRGB(byte[] bytes, long l, int[] ints, int[] ints1);

    public final native static byte[] getAdvancedDecode(byte[] bytes, int w,int h, int[] width, int[] heigth);
}
