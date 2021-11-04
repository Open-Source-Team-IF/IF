package kr.co.IF.hello;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.text.NumberFormat;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getSimpleName();

    private final int PRICE_CARROT = 800;
    private final int PRICE_COCACOLA = 1250;

    private int mQuantity = 0;
    private int mQuantity2 = 0;

    private TextView mProductTextView;
    private TextView mProductTextView2;
    private TextView mPriceTextView;
    private TextView mQuantityTextView;
    private TextView mQuantityTextView2;
    private EditText mNameEditText;

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
    }

    /**
     * 주문 버튼 이벤트 처리
     *
     * @param view 이벤트 처리 할 view
     */

    public void submitOrder(View view) {
        String name = "Name : " + mNameEditText.getText();
        String product = "Product : " + mProductTextView.getText();
        String quantity = "Quantity : " + mQuantity;
        String product2 = "Product : " + mProductTextView2.getText();
        String quantity2 = "Quantity : " + mQuantity2;

        int price = PRICE_CARROT * mQuantity + PRICE_COCACOLA * mQuantity2;

        String formattedPrice = "Total : "
                + NumberFormat.getCurrencyInstance(Locale.KOREA).format(price);

        String message = name + "\n"
                + product + "\n"
                + quantity + "\n"
                + product2 + "\n"
                + quantity2 + "\n"
                + formattedPrice + "\n"
                + "Thank you!";

        displayMessage(message);
        Toast.makeText(this.getApplicationContext(),"Order is completed.", Toast.LENGTH_SHORT).show();

        sendJsonDataToServer();
    }

    private String sendJsonDataToServer(){
        String URL = "http://146.56.166.36:7579/Mobius";
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        httpPost.setHeader("Content-type", "application/json; charset=utf-8");

        String name = mNameEditText.getText().toString();
        String product = mProductTextView.getText().toString();
        String quantity = String.valueOf(mQuantity);
        String product2 = mProductTextView2.getText().toString();
        String quantity2 = String.valueOf(mQuantity2);
        String price = String.valueOf(PRICE_CARROT * mQuantity + PRICE_COCACOLA * mQuantity2);

        JSONObject jObj = new JSONObject();
        JSONObject tmp = new JSONObject();
        JSONArray jsonArray = new JSONArray();
        try{
            tmp.put("product", product);
            tmp.put("quantity", quantity);
            jsonArray.put(tmp);
            tmp = new JSONObject();
            tmp.put("product", product2);
            tmp.put("quantity", quantity2);
            jsonArray.put(tmp);
            jObj.put("order", jsonArray);
            jObj.put("name", name);
            jObj.put("price", price);
        } catch(JSONException e1){
            e1.printStackTrace();
        }

        try{
            StringEntity se;
            se = new StringEntity(jObj.toString());
            HttpEntity he = se;
            httpPost.setEntity(he);
        } catch(UnsupportedEncodingException e1){
            e1.printStackTrace();
        }

        try{
            HttpResponse response = httpClient.execute(httpPost);
            BufferedReader bufReader =
                    new BufferedReader(new InputStreamReader(
                            response.getEntity().getContent(),
                            "utf-8"
                    ));

            String line = null;
            String result = "";

            while((line = bufReader.readLine())!=null){
                result += line;
            }
            return result;
        } catch(ClientProtocolException e){
            e.printStackTrace();
            return "Error" + e.toString();
        } catch(IOException e){
            e.printStackTrace();
            return "Error" + e.toString();
        }
    }

    public void increment(View view) {
        mQuantity++;

        if (mQuantity > 100) {
            mQuantity = 100;
            Toast.makeText(getApplicationContext(), "100 개 이상 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display(mQuantity);
        displayPrice(PRICE_CARROT * mQuantity + PRICE_COCACOLA * mQuantity2);
    }

    public void decrement(View view) {
        mQuantity--;

        if (mQuantity < 0) {
            mQuantity = 0;
            Toast.makeText(MainActivity.this, "0 개 이하 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display(mQuantity);
        displayPrice(PRICE_CARROT * mQuantity + PRICE_COCACOLA * mQuantity2);
    }

    public void increment2(View view) {
        mQuantity2++;

        if (mQuantity2 > 100) {
            mQuantity2 = 100;
            Toast.makeText(getApplicationContext(), "100 개 이상 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display2(mQuantity2);
        displayPrice(PRICE_CARROT * mQuantity + PRICE_COCACOLA * mQuantity2);
    }

    public void decrement2(View view) {
        mQuantity2--;

        if (mQuantity2 < 0) {
            mQuantity2 = 0;
            Toast.makeText(MainActivity.this, "0 개 이하 주문 안 되요", Toast.LENGTH_SHORT).show();
        }

        display2(mQuantity2);
        displayPrice(PRICE_CARROT * mQuantity + PRICE_COCACOLA * mQuantity2);
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

}