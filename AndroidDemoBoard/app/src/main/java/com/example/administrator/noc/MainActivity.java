package com.example.administrator.noc;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.media.SoundPool;
import android.os.Message;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.PopupWindow;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.Iterator;
import java.util.Set;
import java.util.logging.Handler;
import java.util.logging.LogRecord;

/*
* 安卓端：截至2015年8月15日 22:07:04 926行;
*        截至2015年8月19日 17:43:36 1623行;
* Author: MoreFree
*
* */
public class MainActivity extends AppCompatActivity implements SwipeRefreshLayout.OnRefreshListener {

    Button button1;    //温度
    Button button2;    //湿度
    Button button3;    //光照

    Button setled;
    Button showmore;
    Button bpmbutton;
   // Button aboutme;
   // Button exitprogramme;
    Button out1;
    Button out2;
    Button out3;
    boolean bpm_state;
    EditText steerint;
    EditText cardint;
    Button setall;
    Button redlight;
    Button sound;
    Button exit;
    Button setliandong;
    boolean canrefreshflag = true;
    View view;
    PopupWindow pop;
    boolean refreshflag = false;
    boolean redlightflag = false;
    boolean soundflag = false;
    public TextView cardid;
    public TextView progressc;
    private SwipeRefreshLayout swipeRefreshLayout;
    BlueToothSocket mysocket;
    SeekBar steer;
    private Context mContext = null;
    static BluetoothDevice device;
    public static final String SPP_UUID = "00001101-0000-1000-8000-00805F9B34FB";
    ProgressDialog dialog;
    private static final String[] ledstring = {"无色", "红色", "绿色", "蓝色", "青色", "黄色", "品红", "白色"};


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //  this.requestWindowFeature(Window.FEATURE_NO_TITLE);//去掉标题栏
        //getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        //       WindowManager.LayoutParams.FLAG_FULLSCREEN);
        if (android.os.Build.VERSION.SDK_INT > 18) {
            Window window = getWindow();
            window.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS,
                    WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
            window.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION,
                    WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
        }
       // initPopupWindow();
        mContext = this;
        device = null;
        ScrollView mScrollView = (ScrollView) findViewById(R.id.scrollContent);
        mScrollView.setVerticalScrollBarEnabled(false);
        mScrollView.setHorizontalScrollBarEnabled(false);
        swipeRefreshLayout = (SwipeRefreshLayout) findViewById(R.id.swipeRefreshLayout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(android.R.color.holo_blue_light,
                android.R.color.holo_red_light,
                android.R.color.holo_orange_light,
                android.R.color.holo_green_light);

        bpm_state = false;
        button1 = (Button) findViewById(R.id.button1);
        button2 = (Button) findViewById(R.id.button2);
        button3 = (Button) findViewById(R.id.button3);

        setled = (Button) findViewById(R.id.setled);
        bpmbutton = (Button) findViewById(R.id.bpm);
        steerint = (EditText) findViewById(R.id.steerint);
        cardint = (EditText) findViewById(R.id.cardint);
        setall = (Button) findViewById(R.id.setallbutton);
        out1 = (Button) findViewById(R.id.out1);
        out2 = (Button) findViewById(R.id.out2);
        out3 = (Button) findViewById(R.id.out3);
        redlight = (Button) findViewById(R.id.redlightset);
        sound = (Button) findViewById(R.id.soundset);
        setliandong = (Button) findViewById(R.id.setliandong);
       // exit = (Button) findViewById(R.id.exit2);
        showmore = (Button) findViewById(R.id.showmore);



        cardid = (TextView) findViewById(R.id.cardid);
        steer = (SeekBar) findViewById(R.id.steer);
        steer.setMax(180);
        steer.setProgress(90);
        progressc = (TextView) findViewById(R.id.progressc);

        button1.setTextSize(25);
        button1.setTextColor((Color.parseColor("#FFFFFF")));
        button2.setTextSize(25);
        button2.setTextColor((Color.parseColor("#FFFFFF")));
        button3.setTextSize(25);
        button3.setTextColor((Color.parseColor("#FFFFFF")));

        out1.setTextSize(25);
        out1.setTextColor((Color.parseColor("#FFFFFF")));
        out2.setTextSize(25);
        out2.setTextColor((Color.parseColor("#FFFFFF")));
        out3.setTextSize(25);
        out3.setTextColor((Color.parseColor("#FFFFFF")));

        cardid.setTextColor((Color.parseColor("#FFFFFF")));
        cardid.setTextSize(15);

        progressc.setTextColor((Color.parseColor("#FFFFFF")));
        progressc.setTextSize(15);

        dialog = ProgressDialog.show(MainActivity.this, null, "正在连接中...");

       // final Thread canrefresh =  new Thread(new ThreadShow());

        Thread t = new Thread(new Bluetoothrun());
        t.start();
        //Bluetoothopen();
       // BloothInit();

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    mysocket.handle_mes("GETTEMPERATURE*");


                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    mysocket.handle_mes("GETHUNIDITY*");

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    mysocket.handle_mes("GETLIGHT*");

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        steer.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progresstemp = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progresstemp = progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // progress.setText(seekBar.getProgress());
                progressc.setText("舵机角度值:" + progresstemp + "");
            }


            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                progressc.setText("舵机角度值:" + progresstemp + "");
                try {
                    mysocket.handle_mes("SETSTEER" + progresstemp + "*");

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        showmore.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showwindow(v);
            }
        });

        setled.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setTitle("选择一个颜色");
                builder.setItems(ledstring, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        //Toast.makeText(MainActivity.this, "选择的颜色：" + ledstring[which], Toast.LENGTH_SHORT).show();
                        switch (which) {
                            case 0: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "111" + "*");
                                    mysocket.handle_mes("SETRGB" + "111" + "*");

                                   // setled.setBackgroundColor(Color.parseColor("#00000000"));
                                    // setled.setAlpha(1);
                                    //setled.setBackground(getDrawable(R.drawable.mybutton));
                                  //  setled.setTextColor(Color.parseColor("#FFFFFF"));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }
                            case 1: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "011" + "*");
                                    mysocket.handle_mes("SETRGB" + "011" + "*");

                                   // setled.setBackgroundColor(Color.rgb(255, 0, 0));
                                  //  setled.setTextColor(Color.rgb(0, 255, 255));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }
                            case 2: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "101" + "*");
                                    mysocket.handle_mes("SETRGB" + "101" + "*");

                                  //  setled.setBackgroundColor(Color.rgb(0, 255, 0));
                                   // setled.setTextColor(Color.rgb(255, 0, 255));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }
                            case 3: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "110" + "*");

                                    mysocket.handle_mes("SETRGB" + "110" + "*");

                                   // setled.setBackgroundColor(Color.rgb(0, 0, 255));
                                   // setled.setTextColor(Color.rgb(255, 255, 0));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }
                            case 4: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "100" + "*");

                                    mysocket.handle_mes("SETRGB" + "100" + "*");

                                  //  setled.setBackgroundColor(Color.rgb(0, 255, 255));
                                  //  setled.setTextColor(Color.rgb(255, 0, 0));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }
                            case 5: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "001" + "*");

                                    mysocket.handle_mes("SETRGB" + "001" + "*");

                                  //  setled.setBackgroundColor(Color.rgb(255, 255, 0));
                                   // setled.setTextColor(Color.rgb(0, 0, 255));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }
                            case 6: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "010" + "*");

                                    mysocket.handle_mes("SETRGB" + "010" + "*");

                                   // setled.setBackgroundColor(Color.rgb(255, 0, 255));
                                   // setled.setTextColor(Color.rgb(0, 255, 0));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }

                            case 7: {
                                try {
                                    mysocket.handle_mes("SETMYLED" + "000" + "*");
                                    Thread.sleep(200);
                                    mysocket.handle_mes("SETRGB" + "000" + "*");

                                   // setled.setBackgroundColor(Color.rgb(255, 255, 255));
                                  //  setled.setTextColor(Color.rgb(0, 0, 0));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                } catch (InterruptedException e) {
                                    e.printStackTrace();
                                }
                                break;
                            }
                        }
                    }
                });
                builder.show();

            }
        });

        bpmbutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                try {
                    if (bpm_state == false) {
                        mysocket.handle_mes("BPMON*");
                        bpmbutton.setText("蜂鸣器:ON");
                        bpmbutton.setBackgroundColor(Color.rgb(255, 195, 0));
                        bpm_state = true;
                    } else {
                        mysocket.handle_mes("BPMOFF*");
                        bpmbutton.setText("蜂鸣器:OFF");
                        bpmbutton.setBackgroundColor(Color.parseColor("#00000000"));
                        bpm_state = false;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        redlight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (redlightflag == false) {
                    try {
                        mysocket.handle_mes("LIGHTFLAG1*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    redlightflag = true;
                    redlight.setText("红外联动:ON");
                } else {
                    try {
                        mysocket.handle_mes("LIGHTFLAG0*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    redlight.setText("红外联动:OFF");
                    redlightflag = false;
                }
            }
        });

        sound.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (soundflag == false) {
                    try {
                        mysocket.handle_mes("SOUNDFLAG1*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    soundflag = true;
                    sound.setText("声音联动:ON");
                } else {
                    try {
                        mysocket.handle_mes("SOUNDFLAG0*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    soundflag = false;
                    sound.setText("声音联动:OFF");
                }
            }
        });

        setall.setOnClickListener(new View.OnClickListener() {
            String card;
            String steer;

            @Override
            public void onClick(View v) {
                card = cardint.getText().toString();
                steer = steerint.getText().toString();
                if (card.equals("") || steer.equals("")) {
                    Toast.makeText(getApplicationContext(), "请输入卡号和舵机值",
                            Toast.LENGTH_SHORT).show();
                } else {
                    try {
                        mysocket.handle_mes("CARDSET" + card + "*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                    try {
                        mysocket.handle_mes("STEERSET" + steer + "*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                    Toast.makeText(getApplicationContext(), "设置成功！",
                            Toast.LENGTH_SHORT).show();
                }
            }
        });

        out1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (out1.getText().toString().equals("OFF")) {
                    try {
                        mysocket.handle_mes("OUT1ON*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    out1.setText("ON");
                } else {
                    try {
                        mysocket.handle_mes("OUT1OFF*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    out1.setText("OFF");
                }
            }
        });

        out2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (out2.getText().toString().equals("OFF")) {
                    try {
                        mysocket.handle_mes("OUT2ON*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    out2.setText("ON");
                } else {
                    try {
                        mysocket.handle_mes("OUT2OFF*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    out2.setText("OFF");
                }
            }
        });

        out3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (out3.getText().toString().equals("OFF")) {
                    try {
                        mysocket.handle_mes("OUT3ON*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    out3.setText("ON");
                } else {
                    try {
                        mysocket.handle_mes("OUT3OFF*");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    out3.setText("OFF");
                }
            }
        });

        setliandong.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String tempmaxc;
                String tempminc;
                String humimaxc;
                String humiminc;
                String lightmaxc;
                String lightminc;

                tempmaxc = (((TextView) findViewById(R.id.tempmax)).getText()).toString();
                tempminc = (((TextView) findViewById(R.id.tempmin)).getText()).toString();
                humimaxc = (((TextView) findViewById(R.id.humimax)).getText()).toString();
                humiminc = (((TextView) findViewById(R.id.humimin)).getText()).toString();
                lightmaxc = (((TextView) findViewById(R.id.lightmax)).getText()).toString();
                lightminc = (((TextView) findViewById(R.id.lightmin)).getText()).toString();

                try {
                    mysocket.handle_mes("SETMAXTEMP" + tempmaxc + "*");
                    mysocket.handle_mes("SETMAXHUMI" + humimaxc + "*");
                    mysocket.handle_mes("SETMAXLIGHT" + lightmaxc + "*");
                    mysocket.handle_mes("SETMINTEMP" + tempminc + "*");
                    mysocket.handle_mes("SETMINHUMI" + humiminc + "*");
                    mysocket.handle_mes("SETMINLIGHT" + lightminc + "*");
                   // Toast.makeText(getApplicationContext(), "SETMINLIGHT" + lightminc + "*",
                    //        Toast.LENGTH_SHORT).show();

                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        });


    }

    public class Bluetoothrun implements Runnable{

        @Override
        public void run() {
            BluetoothAdapter adapter = BluetoothAdapter.getDefaultAdapter();
            if (adapter == null) {
                return;
            }
            if(!adapter.isEnabled()){	//蓝牙未开启，则开启蓝牙
                adapter.enable();

                try {
                    while(true) {
                        Thread.sleep(1000);
                        if(adapter.isEnabled())
                            break;
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            BluetoothAdapter adapter2 = BluetoothAdapter.getDefaultAdapter();
            Set<BluetoothDevice> devices = adapter2.getBondedDevices();
            Iterator<BluetoothDevice> iterator = devices.iterator();

            while (iterator.hasNext()) {

                BluetoothDevice dev = iterator.next();

                if (dev.getName().contains("HC-05")) {
                    device = dev;
                    System.out.println("asd");
                    break;
                }
            }

            if (device == null) {
                Message message = new Message();
                handler.sendMessage(message);
                message.what = Finalint.OPEN_BLUETOOTH;
                return;
            }

            //Toast.makeText(getApplicationContext(), device.getName(),
            //         Toast.LENGTH_SHORT).show();

            mysocket = new BlueToothSocket(device, MainActivity.this.handler);
            Thread t = new Thread(mysocket);
            t.start();
        }
    }
/*
    public void Bluetoothopen() {
        BluetoothAdapter adapter = BluetoothAdapter.getDefaultAdapter();
        if (adapter == null) {
            return;
        }
        if (!adapter.isEnabled()) {
            adapter.enable();
            //Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            //startActivityForResult(intent, 0x1);
            // dialog = ProgressDialog.show(MainActivity.this, null, "打开蓝牙中...");
        }

    }

    public void BloothInit() {
        BluetoothAdapter adapter = BluetoothAdapter.getDefaultAdapter();
        Set<BluetoothDevice> devices = adapter.getBondedDevices();
        Iterator<BluetoothDevice> iterator = devices.iterator();

        while (iterator.hasNext()) {

            BluetoothDevice dev = iterator.next();

            if (dev.getName().contains("HC-05")) {
                device = dev;
                break;
            }
        }

        if (device == null) {
           // return;
        }

        mysocket = new BlueToothSocket(device, this.handler);
        Thread t = new Thread(mysocket);
        t.start();
    }

*/
    private android.os.Handler handler = new android.os.Handler() {

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case Finalint.CLIENT_INIT_OK: {
                    //Toast.makeText(getApplicationContext(), "客户端启动成功!", Toast.LENGTH_SHORT).show();
                    break;
                }
                case Finalint.SOCKET_CONNECT_OK: {
                    dialog.cancel();
                    break;
                }
                case Finalint.OPEN_BLUETOOTH: {
                    AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                    builder.setMessage("请连接到\"HC-05\"，pin码为1234");
                    builder.setTitle("提示");
                    builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            //    dialog.dismiss();
                            // MainActivity.this.finish();
                            Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                            startActivityForResult(intent, 0x1);
                            finish();
                            System.exit(0);
                        }
                    });
                    builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                        }
                    });
                    builder.create().show();
                    builder.setCancelable(false);
                    break;
                }
                case Finalint.CONNECT_FAIL: {

                    AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                    builder.setMessage("连接失败，确定退出");
                    builder.setTitle("提示");
                    builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                            // MainActivity.this.finish();
                            dialog = ProgressDialog.show(MainActivity.this, null, "程序退出中...");
                            finish();
                            System.exit(0);

                        }
                    });
                    builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                           // Thread t = new Thread(new Bluetoothrun());
                           // t.start();
                        }
                    });
                    builder.setCancelable(false);
                    builder.create().show();
                    //dialog.cancel();
                    ////finish();
                    //System.exit(0);
                  //  Thread t = new Thread(new Bluetoothrun());
                  //  t.start();
                    break;

                }
                case Finalint.RETURN_OK: {
                    Toast.makeText(getApplicationContext(), "连接成功",
                            Toast.LENGTH_SHORT).show();
                    dialog.cancel();
                break;
            }

                case Finalint.BUTTON1_RET: {
                    String temp = msg.getData().getString("readbuff").substring(4);
                    System.out.println(temp);
                    float T = Float.parseFloat(temp);
                    if(T > 200)
                        button1.setText("OFF");
                    else
                    button1.setText(temp);
                    break;
                }

                case Finalint.BUTTON2_RET: {
                    String temp = msg.getData().getString("readbuff").substring(4);
                    float R = Float.parseFloat(temp);
                    if(R > 200)
                        button2.setText("OFF");
                    else
                        button2.setText(temp);
                    break;
                }

                case Finalint.BUTTON3_RET: {
                    String temp = msg.getData().getString("readbuff").substring(8);
                    button3.setText(temp);
                    break;
                }

                case Finalint.CARD_ID: {
                    String temp = msg.getData().getString("readbuff").substring(10);
                    cardid.setText("卡号  " + temp);
                    cardint.setText(temp);
                    break;
                }

                case Finalint.OUT1: {
                    String temp = msg.getData().getString("readbuff").substring(7);
                    if (temp.equals("1"))
                        out1.setText("OFF");
                    else
                        out1.setText("on");
                    break;
                }

                case Finalint.OUT2: {
                    String temp = msg.getData().getString("readbuff").substring(7);
                    if (temp.equals("1"))
                        out2.setText("OFF");
                    else
                        out2.setText("on");
                    break;
                }

                case Finalint.OUT3: {
                    String temp = msg.getData().getString("readbuff").substring(7);
                    if (temp.equals("1"))
                        out3.setText("OFF");
                    else
                        out3.setText("on");
                    break;
                }

                case Finalint.SOUND: {
                    String temp = msg.getData().getString("readbuff").substring(8);
                    sound.setText(temp);
                    if ((temp.charAt(0)) == '0') {
                        soundflag = false;
                        sound.setText("声音联动:OFF");
                    }
                    if ((temp.charAt(0)) == '1') {
                        soundflag = true;
                        sound.setText("声音联动:ON");
                    }
                    break;
                }

                case Finalint.REDLIGHT: {
                    String temp = msg.getData().getString("readbuff").substring(11);
                    if (temp.equals("0")) {
                        redlight.setText("红外联动:OFF");
                        redlightflag = false;
                    }
                    if (temp.equals("1")) {
                        redlight.setText("红外联动:ON");
                        redlightflag = true;
                    }
                    break;
                }

                case Finalint.BPM: {
                    String temp = msg.getData().getString("readbuff").substring(6);
                    if (temp.equals("1")) {
                        bpmbutton.setText("关蜂鸣器");
                        bpmbutton.setBackgroundColor(Color.rgb(255, 195, 0));
                        bpm_state = true;
                    }
                    if (temp.equals("0")) {
                        bpmbutton.setText("开蜂鸣器");
                        bpmbutton.setBackgroundColor(Color.parseColor("#00000000"));
                        bpm_state = false;
                    }
                }

                case Finalint.EXITOK: {
                    dialog.cancel();
                    finish();
                    System.exit(0);
                }

                case Finalint.RGB: {
                    /* RGB = 121*/
                    System.out.println("im here");
                    String temp = msg.getData().getString("readbuff");
                    char a = temp.charAt(6);
                    char b = temp.charAt(7);
                    char c = temp.charAt(8);
                    System.out.println("rgb:"+a+b+c);
                    if(a == '1' && b == '1' && c == '1')
                    {
                        setled.setText("LED:未设置");
                    }
                    if(a == '0' && b == '1' && c == '1')
                    {
                        setled.setText("LED:红色");
                    }
                    if(a == '1' && b == '0' && c == '1')
                    {
                        setled.setText("LED:绿色");
                    }
                    if(a == '1' && b == '1' && c == '0')
                    {
                        setled.setText("LED:蓝色");
                    }
                    if(a == '1' && b == '0' && c == '0')
                    {
                        setled.setText("LED:青色");
                    }
                    if(a == '0' && b == '0' && c == '1')
                    {
                        setled.setText("LED:黄色");
                    }
                    if(a == '0' && b == '1' && c == '0')
                    {
                        setled.setText("LED:品红");
                    }
                    if(a == '0' && b == '0' && c == '0')
                    {
                        setled.setText("LED:白色");
                    }
                }

                case Finalint.REFRESH: {
                    if (refreshflag == true) {
                        swipeRefreshLayout.setRefreshing(false);
                        Toast.makeText(getApplicationContext(), "数据刷新成功！",
                                Toast.LENGTH_SHORT).show();
                    }
                    refreshflag = false;
                }

                case Finalint.BPMSTATE: {
                    if(msg.getData().getString("readbuff") == "bpm = 1")
                    {
                        bpmbutton.setText("蜂鸣器:ON");
                        bpmbutton.setBackgroundColor(Color.rgb(255, 195, 0));
                    }
                    if(msg.getData().getString("readbuff") == "bpm = 0")
                    {
                        bpmbutton.setText("蜂鸣器:OFF");
                        bpmbutton.setBackgroundColor(Color.rgb(255, 195, 0));
                    }
                }
            }

        }

    };

    private void initPopupWindow() {

        view = this.getLayoutInflater().inflate(R.layout.popup, null);
        pop = new PopupWindow(view, ViewGroup.LayoutParams.FILL_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT);
        pop.setOutsideTouchable(true);
        view.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                pop.dismiss();
            }
        });
        pop.setFocusable(true);

    }
    private void showwindow(View view)
    {
        View contentView = LayoutInflater.from(mContext).inflate(
                R.layout.popup, null);

        Button aboutme = (Button) contentView.findViewById(R.id.aboutme);
        //aboutme = (Button) findViewById(R.id.aboutme);
        Button exitprogramme = (Button) contentView.findViewById(R.id.exit2);


        final PopupWindow popupWindow = new PopupWindow(contentView,
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT, true);
        popupWindow.setTouchable(true);


        // 如果不设置PopupWindow的背景，无论是点击外部区域还是Back键都无法dismiss弹框
        // 我觉得这里是API的一个bug

        popupWindow.setBackgroundDrawable(getResources().getDrawable(
                R.drawable.backone));

        // 设置好参数之后再show
        popupWindow.showAsDropDown(view);
        aboutme.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                popupWindow.dismiss();
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setMessage("Powered by MoreFree" + '\n' + "www.bwelco.com");
                builder.setTitle("南师学正教育");
                builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        ;
                    }
                });
                builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        ;
                    }
                });
                builder.setCancelable(false);
                builder.create().show();
            }
        });

        exitprogramme.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                popupWindow.dismiss();
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setMessage("确认退出吗？");
                builder.setTitle("提示");
                builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        // MainActivity.this.finish();
                        dialog = ProgressDialog.show(MainActivity.this, null, "程序退出中...");
                        try {
                            mysocket.handle_mes("EXIT*");
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                });
                builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
                builder.setCancelable(false);
                builder.create().show();
            }
        });
    }

    @Override
    public void onRefresh() {
        try {
            BlueToothSocket.handle_mes("GETALLFLAGINIT*");
        } catch (IOException e) {
            e.printStackTrace();
        }

        refreshflag = true;
    }
}
