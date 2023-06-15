package com.example.learnndk;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    public String getAssetsFilePath(String file) {
        AssetManager assetManager = this.getAssets();
        try {
            BufferedInputStream inputStream = new BufferedInputStream(assetManager.open(file));
            byte[] data = new byte[inputStream.available()];
            inputStream.read(data);
            inputStream.close();

            File outFile = new File(this.getFilesDir(), file);
            FileOutputStream outputStream = new FileOutputStream(outFile);
            outputStream.write(data);
            outputStream.close();

            Log.d("filepath", outFile.getAbsolutePath());
            return outFile.getAbsolutePath();
        } catch (IOException e) {

        }
        return "";
    }

    public void requestLogPermission() {
        // 动态申请权限
        String permission = Manifest.permission.WRITE_EXTERNAL_STORAGE;
        int ret = ContextCompat.checkSelfPermission(this, permission);
        if (ret != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{permission}, 0);
        }

    }

    private String logFilePath = null;

    public String ensureLogFile() {
        if (this.logFilePath == null) {
            File[] dirs = getExternalFilesDirs(Environment.DIRECTORY_DOCUMENTS);
            String dir = null;
            if (dirs.length > 0) {
                dir = dirs[0].getAbsolutePath();
            } else {
                return null;
            }

            File file = new File(dir, "leak_report.txt");
            String filePath = file.getAbsolutePath();
            Log.d("log file path: ", filePath);
            if (!file.exists()) {
                try {
                    file.createNewFile();
                    Log.d("", "创建日志文件成功");
                } catch (IOException e) {
                    Log.d("", "创建日志文件失败");
                    throw new RuntimeException(e);
                }
            }
            this.logFilePath = filePath;
        }
        return this.logFilePath;
    }

    public void showLogContent() {
        String filePath = this.ensureLogFile();
        try {
            File file = new File(filePath);
            InputStream inputStream = new FileInputStream(file);
            byte[] bytes = new byte[(int) file.length()];
            inputStream.read(bytes);
            String content = new String(bytes);
            inputStream.close();
            Log.d("", "File content: \n" + content);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.requestLogPermission();

        TextView tv = (TextView) findViewById(R.id.text);
        tv.setText(stringFromJNI());
        AssetManager assetManager = this.getAssets();
        findViewById(R.id.testVMPath).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String vmPath = assetManager.open("gaga.mp4").toString();
                    tv.setText(testVMPath(vmPath));
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        });
        findViewById(R.id.leakTest).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(leakTest());
            }
        });

        findViewById(R.id.leakStartMonitor).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                leakStartMonitor();
            }
        });
        findViewById(R.id.leakStopMonitor).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                leakStopMonitor();
            }
        });
        findViewById(R.id.leakReport).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String filePath = MainActivity.this.ensureLogFile();
                leakStopMonitor();
                leakReport(filePath);
                Toast.makeText(MainActivity.this, "文件写入成功", Toast.LENGTH_SHORT).show();
                MainActivity.this.showLogContent();
            }
        });
        findViewById(R.id.leakFree).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(leakFree());
            }
        });
        findViewById(R.id.testOpenAL).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(testOpenAL());
            }
        });
        findViewById(R.id.testFileAPI).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(testFileApi());
            }
        });
        findViewById(R.id.testFFMpegJNI).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(testFFMpegJNI(assetManager));
            }
        });


        String mp4File = this.getAssetsFilePath("gaga.mp4");
        findViewById(R.id.testFFMpeg).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(testFFMpeg(mp4File));
            }
        });
        findViewById(R.id.readAssets_txt).setOnClickListener(new View.OnClickListener() {
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

    public native String leakTest();

    public native String leakFree();

    public native void leakStartMonitor();

    public native void leakStopMonitor();

    public native void leakReport(String path);

    public native String testFFMpeg(String mp4File);

    public native String testVMPath(String vmpath);

    public native String testFFMpegJNI(AssetManager assetManager);

    public native String testOpenAL();

    public native String testFileApi();
}