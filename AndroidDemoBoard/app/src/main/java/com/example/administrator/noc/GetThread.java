package com.example.administrator.noc;

import java.io.IOException;

/**
 * Created by Administrator on 2015/8/15.
 */

public class GetThread implements Runnable{
    boolean first;
    GetThread()
    {

        first = true;

    }
    @Override
    public void run() {
        try {
            BlueToothSocket.handle_mes("GETALLFLAGINIT*");
            Thread.sleep(5000);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }


        while(true) {

            try {
                BlueToothSocket.handle_mes("GETTEMPERATURE*");
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                if(first == false)
                    Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            try {
                BlueToothSocket.handle_mes("GETHUNIDITY*");
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                if(first == false)
                    Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            try {
                BlueToothSocket.handle_mes("GETLIGHT*");
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                if(first == false)
                    Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            first = false;
        }
    }
}


