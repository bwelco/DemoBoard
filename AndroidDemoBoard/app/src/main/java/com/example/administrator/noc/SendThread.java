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
                while(BlueToothSocket.commanddone == false) {
                    try {
                        Thread.sleep(50);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                BlueToothSocket.out.write(temp);  //阻塞  不能发送消息  要等到指令完成
                BlueToothSocket.out.flush();

                BlueToothSocket.commanddone = false;
            //    BlueToothSocket.queuelength--;
             /*   try {
                    if(temp.startsWith("SETSTEER")) {
                        System.out.println("steer message");
                        Thread.sleep(2000);
                    }
                    if(temp.startsWith("SETMYLED")) {
                        System.out.println("SETMYLED message");
                        Thread.sleep(2000);
                    }
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }*/
                try {
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
