package kr.co.IF.hello;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.NumberFormat;
import java.util.Locale;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getSimpleName();

    private final int PRICE_KITKAT = 800;
    private final int PRICE_APOLLO = 1250;

    private int mQuantity = 0;
    private int mQuantity2 = 0;

    private TextView mProductTextView;
    private TextView mProductTextView2;
    private TextView mPriceTextView;
    private TextView mQuantityTextView;
    private TextView mQuantityTextView2;
    private EditText mNameEditText;

    private TextToSpeech tts;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mProductTextView = (TextView) findViewById(R.id.product_text_view);
        mProductTextView2 = (TextView) findViewById(R.id.product_text_view2);
        mPriceTextView = (TextView) findViewById(R.id.price_text_view);
        mQuantityTextView = (TextView) findViewById(R.id.quantity_text_view);
        mQuantityTextView2 = (TextView) findViewById(R.id.quantity_text_view2);
        mNameEditText = (EditText) findViewById(R.id.name_edit_text);

        tts = new TextToSpeech(this, new TextToSpeech.OnInitListener(){
            @Override
            public void onInit(int status){
                if(status != android.speech.tts.TextToSpeech.ERROR){
                    tts.setLanguage(Locale.KOREAN);
                }
            }
        });
    }

    @Override
    protected void onStart(){
        super.onStart();
    }

    @Override
    protected void onResume(){
        super.onResume();
        new Thread(){
            public void run(){
                try{
                    requestAECreation();
                    requestContainerCreation();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

        }.start();

    }

    private void requestAECreation(){
        JSONObject jObj = new JSONObject();
        JSONObject tmp = new JSONObject();

        try{
            tmp.put("rn", "app1");
            tmp.put("api", "application");
            tmp.put("rr", true);
            jObj.put("m2m:ae", tmp);
        } catch(JSONException e1){
            e1.printStackTrace();
        }

        try{
            String host_url = "http://146.56.166.36:7579/Mobius";
            HttpURLConnection conn = null;

            URL url = new URL(host_url);
            conn = (HttpURLConnection)url.openConnection();

            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-type", "application/json; ty=2");
            conn.setRequestProperty("Accept", "application/json");
            conn.setRequestProperty("X-M2M-RI", "1234");
            conn.setRequestProperty("X-M2M-Origin", "CAE1");

            conn.setDoOutput(true);
            conn.setDoInput(true);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(conn.getOutputStream()));

            bw.write(jObj.toString());
            bw.flush();
            bw.close();

            int responseCode = conn.getResponseCode();
        }catch(IOException ie){
            ie.printStackTrace();
        }catch(Exception ee){
            ee.printStackTrace();
        }
    }

    private void requestContainerCreation(){
        JSONObject jObj = new JSONObject();
        JSONObject tmp = new JSONObject();
        try{
            tmp.put("rn", "user1");
            tmp.put("mni", 100);
            jObj.put("m2m:cnt", tmp);
        } catch(JSONException e1){
            e1.printStackTrace();
        }

        try{
            String host_url = "http://146.56.166.36:7579/Mobius/app1";
            HttpURLConnection conn = null;

            URL url = new URL(host_url);
            conn = (HttpURLConnection)url.openConnection();

            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-type", "application/json; ty=3");
            conn.setRequestProperty("Accept", "application/json");
            conn.setRequestProperty("X-M2M-RI", "1234");
            conn.setRequestProperty("X-M2M-Origin", "CAE1");

            conn.setDoOutput(true);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(conn.getOutputStream()));

            bw.write(jObj.toString());
            bw.flush();
            bw.close();

            int responseCode = conn.getResponseCode();
        }catch(IOException ie){
            ie.printStackTrace();
        }catch(Exception ee){
            ee.printStackTrace();
        }

        jObj = new JSONObject();
        tmp = new JSONObject();
        try{
            tmp.put("rn", "product");
            tmp.put("mni", 100);
            jObj.put("m2m:cnt", tmp);
        } catch(JSONException e1){
            e1.printStackTrace();
        }

        try{
            String host_url = "http://146.56.166.36:7579/Mobius/app1/user1";
            HttpURLConnection conn = null;

            URL url = new URL(host_url);
            conn = (HttpURLConnection)url.openConnection();

            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-type", "application/json; ty=3");
            conn.setRequestProperty("Accept", "application/json");
            conn.setRequestProperty("X-M2M-RI", "1234");
            conn.setRequestProperty("X-M2M-Origin", "CAE1");

            conn.setDoOutput(true);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(conn.getOutputStream()));

            bw.write(jObj.toString());
            bw.flush();
            bw.close();

            int responseCode = conn.getResponseCode();
        }catch(IOException ie){
            ie.printStackTrace();
        }catch(Exception ee){
            ee.printStackTrace();
        }

        jObj = new JSONObject();
        tmp = new JSONObject();
        try{
            tmp.put("rn", "order");
            tmp.put("mni", 100);
            jObj.put("m2m:cnt", tmp);
        } catch(JSONException e1){
            e1.printStackTrace();
        }

        try{
            String host_url = "http://146.56.166.36:7579/Mobius/app1/user1";
            HttpURLConnection conn = null;

            URL url = new URL(host_url);
            conn = (HttpURLConnection)url.openConnection();

            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-type", "application/json; ty=3");
            conn.setRequestProperty("Accept", "application/json");
            conn.setRequestProperty("X-M2M-RI", "1234");
            conn.setRequestProperty("X-M2M-Origin", "CAE1");

            conn.setDoOutput(true);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(conn.getOutputStream()));

            bw.write(jObj.toString());
            bw.flush();
            bw.close();

            int responseCode = conn.getResponseCode();
        }catch(IOException ie){
            ie.printStackTrace();
        }catch(Exception ee){
            ee.printStackTrace();
        }
    }

    public void submitOrder(View view) {
        String name = "사용자이름 : " + mNameEditText.getText();
        String product = "품목 : " + mProductTextView.getText();
        String quantity = "수량 : " + mQuantity;
        String product2 = "품목 : " + mProductTextView2.getText();
        String quantity2 = "수량 : " + mQuantity2;

        int price = PRICE_KITKAT * mQuantity + PRICE_APOLLO * mQuantity2;

        String formattedPrice = "총액 : "
                + NumberFormat.getCurrencyInstance(Locale.KOREA).format(price);

        String message = name + "\n"
                + product + "\n"
                + quantity + "\n"
                + product2 + "\n"
                + quantity2 + "\n"
                + formattedPrice + "\n"
                + "감사합니다.";

        displayMessage(message);
        Toast.makeText(this.getApplicationContext(),"주문이 완료되었습니다.", Toast.LENGTH_SHORT).show();

        String text = "사용자님이 주문한 " + mProductTextView.getText() + " " + mQuantity + "개, " +
                mProductTextView2.getText() + " " + mQuantity2 + "개 주문이 완료되었습니다.";
        noti_by_tts(text);

        new Thread(){
            public void run(){
                try{
                    requestCinCreation();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }.start();

        getRequest();

    }

    private void requestCinCreation(){
        String product = mProductTextView.getText().toString();
        String product2 = mProductTextView2.getText().toString();

        JSONObject jObj = new JSONObject();
        JSONObject tmp = new JSONObject();
        JSONObject jObj2 = new JSONObject();
        try{
            tmp.put("product1", product);
            tmp.put("quantity1", mQuantity);
            tmp.put("price1", PRICE_KITKAT);
            tmp.put("product2", product2);
            tmp.put("quantity2", mQuantity2);
            tmp.put("price2", PRICE_APOLLO);
            jObj2.put("con", tmp);
            jObj.put("m2m:cin", jObj2);
        } catch(JSONException e1){
            e1.printStackTrace();
        }

        try{
            String host_url = "http://146.56.166.36:7579/Mobius/app1/user1/product";
            HttpURLConnection conn = null;

            URL url = new URL(host_url);
            conn = (HttpURLConnection)url.openConnection();

            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-type", "application/json; ty=4");
            conn.setRequestProperty("X-M2M-Origin", "CAE1");
            conn.setRequestProperty("X-M2M-RI", "1234");
            conn.setRequestProperty("Accept", "application/json");

            conn.setDoOutput(true);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(conn.getOutputStream()));

            bw.write(jObj.toString());
            bw.flush();
            bw.close();

            int responseCode = conn.getResponseCode();
        }catch(IOException ie){
            ie.printStackTrace();
        }catch(Exception ee){
            ee.printStackTrace();
        }

        jObj = new JSONObject();
        tmp = new JSONObject();
        jObj2 = new JSONObject();
        try{
            tmp.put("order", 0);
            jObj2.put("con", tmp);
            jObj.put("m2m:cin", jObj2);
        } catch(JSONException e1){
            e1.printStackTrace();
        }

        try{
            String host_url = "http://146.56.166.36:7579/Mobius/app1/user1/order";
            HttpURLConnection conn = null;

            URL url = new URL(host_url);
            conn = (HttpURLConnection)url.openConnection();

            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-type", "application/json; ty=4");
            conn.setRequestProperty("X-M2M-Origin", "CAE1");
            conn.setRequestProperty("X-M2M-RI", "1234");
            conn.setRequestProperty("Accept", "application/json");

            conn.setDoOutput(true);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(conn.getOutputStream()));

            bw.write(jObj.toString());
            bw.flush();
            bw.close();

            int responseCode = conn.getResponseCode();
        }catch(IOException ie){
            ie.printStackTrace();
        }catch(Exception ee){
            ee.printStackTrace();
        }
    }

    public void getRequest(){
        Timer timer = new Timer();
        TimerTask task = new TimerTask(){
            @Override
            public void run(){
                new Thread(){
                    public void run(){
                        try{
                            String host_url = "http://146.56.166.36:7579/Mobius/app1/user1/order/la";
                            HttpURLConnection conn;

                            URL url = new URL(host_url);
                            conn = (HttpURLConnection)url.openConnection();

                            conn.setRequestMethod("GET");
                            conn.setRequestProperty("Accept", "application/json");
                            conn.setRequestProperty("X-M2M-RI", "1234");
                            conn.setRequestProperty("X-M2M-Origin", "CAE1");

                            conn.setDoInput(true);

                            int responseCode = conn.getResponseCode();

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
                            if(order == 2){
                                noti_order();
                                noti_by_tts("배달이 완료되었습니다.");
                                timer.cancel();
                            }

                        }catch(IOException ie){
                            ie.printStackTrace();
                        }catch(Exception ee){
                            ee.printStackTrace();
                        }
                    }
                }.start();
            }
        };
        timer.schedule(task, 1000, 5000);
    }

    public void noti_by_tts(String text){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP){
            tts.speak(text, TextToSpeech.QUEUE_FLUSH, null, null);
        }
        else{
            tts.speak(text, TextToSpeech.QUEUE_FLUSH, null);
        }
    }

    public void noti_order(){
        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        NotificationCompat.Builder builder;

        //Check if Android version is over than Oreo(API26)
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            String channelID = "channel_01";
            String channelName = "MyChannel01";

            NotificationChannel channel = new NotificationChannel(channelID, channelName, NotificationManager.IMPORTANCE_DEFAULT);

            notificationManager.createNotificationChannel(channel);

            builder = new NotificationCompat.Builder(this, channelID);
        }
        else{
            builder = new NotificationCompat.Builder(this, "default");
        }
        //Setting notification alarm's icon
        builder.setSmallIcon(R.drawable.ic_launcher_foreground);

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

    public void increment(View view) {
        mQuantity++;

        if (mQuantity > 100) {
            mQuantity = 100;
            Toast.makeText(getApplicationContext(), "100 개 이상 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display(mQuantity);
        displayPrice(PRICE_KITKAT * mQuantity + PRICE_APOLLO * mQuantity2);
    }

    public void decrement(View view) {
        mQuantity--;

        if (mQuantity < 0) {
            mQuantity = 0;
            Toast.makeText(MainActivity.this, "0 개 이하 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display(mQuantity);
        displayPrice(PRICE_KITKAT * mQuantity + PRICE_APOLLO * mQuantity2);
    }

    public void increment2(View view) {
        mQuantity2++;

        if (mQuantity2 > 100) {
            mQuantity2 = 100;
            Toast.makeText(getApplicationContext(), "100 개 이상 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display2(mQuantity2);
        displayPrice(PRICE_KITKAT * mQuantity + PRICE_APOLLO * mQuantity2);
    }

    public void decrement2(View view) {
        mQuantity2--;

        if (mQuantity2 < 0) {
            mQuantity2 = 0;
            Toast.makeText(MainActivity.this, "0 개 이하 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display2(mQuantity2);
        displayPrice(PRICE_KITKAT * mQuantity + PRICE_APOLLO * mQuantity2);
    }

    /**
     * 수량을 화면에 표시
     *
     * @param number 표시 할 수량
     */
    private void display(int number) {
        mQuantityTextView.setText("" + number);
    }
    private void display2(int number) {
        mQuantityTextView2.setText("" + number);
    }

    private void displayPrice(int number) {
        mPriceTextView.setText(NumberFormat.getCurrencyInstance(Locale.KOREA).format(number));
    }

    private void displayMessage(String message) {
        mPriceTextView.setText(message);
    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
        if(tts != null){
            tts.stop();
            tts.shutdown();
            tts = null;
        }
    }

}