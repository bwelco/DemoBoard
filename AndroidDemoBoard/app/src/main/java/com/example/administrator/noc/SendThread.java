package com.example.administrator.noc;

import java.io.PrintWriter;

/**
 *
 * Created by Administrator on 2015/8/15.
 */
public class SendThread implements Runnable {
    PrintWriter out;

    @Override
    public synchronized void run() {
        while(true) {
            while (BlueToothSocket.queue.size() > 0) {
                String temp = BlueToothSocket.queue.poll()+"";
                if(temp.equals(""))
                    continue;
                BlueToothSocket.out.write(temp);
                BlueToothSocket.out.flush();
            //    BlueToothSocket.queuelength--;
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
