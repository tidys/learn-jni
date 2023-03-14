package com.example.learnndk;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = (TextView) findViewById(R.id.text);
        tv.setText(stringFromJNI());

        findViewById(R.id.testFFMpeg).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(testFFMpeg());
            }
        });
        Button btn = (Button) findViewById(R.id.test);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i("f", "click");
                try {
                    // 打开asset里面的文件
                    AssetManager assetManager = getResources().getAssets();
                    InputStream inputStream = assetManager.open("1.txt");
                    InputStreamReader inputReader = new InputStreamReader(inputStream);
                    BufferedReader bufReader = new BufferedReader(inputReader);
                    String line = "";
                    String result = "";
                    while ((line = bufReader.readLine()) != null) {
                        result += line;
                    }
                    tv.setText(result);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        });
        getCacheDir().getAbsolutePath();
    }

    public native String stringFromJNI();

    public native String testFFMpeg();

    public native String testOpenAL();
}