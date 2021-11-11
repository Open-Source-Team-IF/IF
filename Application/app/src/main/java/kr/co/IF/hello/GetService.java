package kr.co.IF.hello;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;

public class GetService extends Service{
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Timer timer = new Timer();
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                try{
                    String host_url = "http://146.56.166.36:7579/Mobius/app1/status/la";
                    HttpURLConnection conn;

                    URL url = new URL(host_url);
                    conn = (HttpURLConnection)url.openConnection();

                    conn.setRequestMethod("GET");
                    conn.setRequestProperty("Accept", "application/json");
                    conn.setRequestProperty("X-M2M-RI", "1234");
                    conn.setRequestProperty("X-M2M-Origin", "CAE1");

                    conn.setDoOutput(true);
                    conn.setDoInput(true);

                    InputStream is = conn.getInputStream();
                    StringBuilder sb = new StringBuilder();
                    BufferedReader br = new BufferedReader(new InputStreamReader(is, "UTF-8"));
                    String result;
                    while((result = br.readLine())!=null){
                        sb.append(result + "\n");
                    }

                    result = sb.toString();

                    JSONObject jsonObj = new JSONObject(result);
                    JSONObject m2m = jsonObj.getJSONObject("m2m:cin");
                    JSONObject con = m2m.getJSONObject("con");

                    int order = (int)con.get("order");
                    if(order == 1)
                        timer.cancel();
                }catch(IOException ie){
                    ie.printStackTrace();
                }catch(Exception ee){
                    ee.printStackTrace();
                }
            }
        };
        timer.schedule(task, 1000, 5000);


        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        NotificationCompat.Builder builder;

        //Check if Android version is over than Oreo(API26)
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            String channelID = "channel_01";
            String channelName = "MyChannel01";

            NotificationChannel channel = new NotificationChannel(channelID, channelName, NotificationManager.IMPORTANCE_UNSPECIFIED);

            notificationManager.createNotificationChannel(channel);

            builder = new NotificationCompat.Builder(this, channelID);
        }
        else{
            builder = new NotificationCompat.Builder(this, (Notification) null);
        }
        //Setting notification alarm's icon
        builder.setSmallIcon(R.drawable.icon);

        //Setting alarm's title and text
        builder.setContentTitle("Order App");
        builder.setContentText("Your order is completed.");

        //If alarm is clicked, then alarm would be destroyed.
        builder.setAutoCancel(true);
        //Setting alarm vibration
        builder.setVibrate(new long[]{0, 2000, 1000, 3000});

        Notification notification = builder.build();

        notificationManager.notify(1, notification);
    }
}
