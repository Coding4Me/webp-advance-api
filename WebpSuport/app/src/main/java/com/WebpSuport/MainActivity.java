package com.WebpSuport;

import android.graphics.Bitmap;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;

import com.u17webplib.webplib;

import java.io.ByteArrayOutputStream;
import java.io.Console;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import android.graphics.Bitmap;
import android.widget.ImageView;

public class MainActivity extends ActionBarActivity {

    ImageView imageView;

    //WindowManager wm = this.getWindowManager();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //int nVersion = webplib.getVersion();

        imageView = (ImageView) findViewById(R.id.imageView);


        try {
            InputStream is = getAssets().open("2.webp");
            byte[] bytes = streamToBytes(is);

            int[] width = new int[] { 0 };
            int[] height = new int[] { 0 };

            int sw = this.getWindowManager().getDefaultDisplay().getWidth();
            int sh = this.getWindowManager().getDefaultDisplay().getHeight();

            byte[] decoded = webplib.getAdvancedDecode(bytes,sw,sh, width, height);
            if(decoded == null) return;
            int[] pixels = new int[decoded.length / 4];
            ByteBuffer.wrap(decoded).asIntBuffer().get(pixels);

            Bitmap bitmap =  Bitmap.createBitmap(pixels, width[0], height[0],Bitmap.Config.RGB_565);

            imageView.setImageBitmap(bitmap);

        } catch (IOException e) {
            e.printStackTrace();
        }


    }


    public byte[] streamToBytes(InputStream in) {
        ByteArrayOutputStream out = new ByteArrayOutputStream(1024);
        byte[] buffer = new byte[1024];
        int len = -1;
        try {
            while ((len = in.read(buffer)) >= 0) {
                out.write(buffer, 0, len);
                out.flush();
            }
        } catch (java.io.IOException e) {
            e.printStackTrace();
        } finally {
            try {
                in.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return out.toByteArray();
    }

}
