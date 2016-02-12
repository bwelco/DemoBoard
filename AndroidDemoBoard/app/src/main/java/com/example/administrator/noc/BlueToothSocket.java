package com.example.administrator.noc;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Queue;
import java.util.UUID;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.Telephony.Mms.Outbox;
import android.support.annotation.NonNull;
import android.view.inputmethod.InputBinding;

public class BlueToothSocket implements Runnable {

    static private BluetoothSocket cwjSocket = null;
    static private BluetoothDevice cwjDevice = null;
    static Queue<String> queue;
    static boolean commanddone = true;


   // static int queuelength = 0;
    Handler handler;


    static BufferedReader in = null;
    static PrintWriter out = null;

    public BlueToothSocket(BluetoothDevice device, Handler handler2) {
        queue = new LinkedList<String>();
        BluetoothSocket tmp = null;
        cwjDevice = device;
        this.handler = handler2;

        UUID uuid = UUID.fromString(MainActivity.SPP_UUID); // SPP协议
        try {
            tmp = device.createRfcommSocketToServiceRecord(uuid); // 客户端创建
        } catch (IOException e) {
        }
        cwjSocket = tmp;
    }


     public static synchronized   void handle_mes(String mes) throws IOException {

        queue.add(mes);

     }

    public void run() {
        String readbuff;
        try {
            cwjSocket.connect();
            in = new BufferedReader(new InputStreamReader(
                    cwjSocket.getInputStream()));
            out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(
                    cwjSocket.getOutputStream())), true);

            while (true) {
                out.write("test*");
                System.out.println("connecting");
                out.flush();
                Thread.sleep(50);
                out.write("test*");
                out.flush();

                readbuff = in.readLine();
                if (readbuff.startsWith("*return")) {

                    Message message = new Message();
                    message.what = Finalint.RETURN_OK;
                    handler.sendMessage(message);

                    Thread t = new Thread(new SendThread());
                    t.start();

                    Thread t2 = new Thread(new GetThread());
                    t2.start();

                    break;
                }
                Thread.sleep(1000);
            }

            while(true)
            {
                handle_message();
            }
        } catch (IOException connectException) {
            try {
                cwjSocket.close();
                Message message = new Message();
                message.what = Finalint.CONNECT_FAIL; // 客户端连接失败
                handler.sendMessage(message);
            } catch (IOException closeException) {
            }
            return;
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    /**
     * Will cancel the listening socket, and cause the thread to finish
     */
    public void cancel() {
        try {
            cwjSocket.close();
        } catch (IOException e) {
        }
    }

    public void handle_message() throws IOException, InterruptedException {
        String readbuff;
        readbuff = in.readLine();
        readbuff = readbuff.substring(1, readbuff.length() - 1);
        System.out.println(readbuff);
        if(readbuff.startsWith("card id"))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.CARD_ID;
        }
        if(readbuff.startsWith("T ="))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.BUTTON1_RET;
        }

        if(readbuff.startsWith("R ="))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.BUTTON2_RET;
        }

        if(readbuff.startsWith("light = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.BUTTON3_RET;
        }

        if(readbuff.startsWith("out1 = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.OUT1;
        }

        if(readbuff.startsWith("out2 = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.OUT2;
        }

        if(readbuff.startsWith("out3 = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.OUT3;
        }

        if(readbuff.startsWith("sound = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.SOUND;
        }

        if(readbuff.startsWith("redlight = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.REDLIGHT;
        }

        if(readbuff.startsWith("REFRESHOK"))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.REFRESH;
        }
/*
        if(readbuff.startsWith("bpm = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.BPM;
        }
*/
        if(readbuff.startsWith("EXITOK"))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.EXITOK;
        }

        if(readbuff.startsWith("bpm = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.BPMSTATE;
        }
        if(readbuff.startsWith("RGB = "))
        {
            Message message = new Message();
            Bundle bundle=new Bundle();
            bundle.putString("readbuff", readbuff);
            message.setData(bundle);//bundle传值，耗时，效率低
            handler.sendMessage(message);
            message.what = Finalint.RGB;
        }

        if(readbuff.startsWith("Command Done"))
        {
            this.commanddone = true;
        }

        Thread.sleep(10);
    }

}
