package net.ddns.clrobotic.androidrover;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.net.http.AndroidHttpClient;
import android.net.http.HttpResponseCache;
import android.os.StrictMode;
import android.speech.RecognizerIntent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private static final int RECOGNIZE_SPEECH_ACTIVITY = 1;
    private Button btnForward;
    private TextView grabar;
    private TextView helloID;
    protected Boolean isRecord;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.i("MainActivity", "onCreate...");
        isRecord = Boolean.TRUE;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        int SDK_INT = android.os.Build.VERSION.SDK_INT;
        if (SDK_INT > 8){
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
                    .permitAll().build();
            StrictMode.setThreadPolicy(policy);
            //your codes here

        }
        btnForward = (Button)findViewById(R.id.btn_forward);
        grabar = (TextView) findViewById(R.id.textOutId);
        helloID = (TextView) findViewById(R.id.textHelloId);
        btnForward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i("MainActivity", "isRecord::"+isRecord);
                if(isRecord){
                    YaiCmd cmd = new YaiCmd();
                    sendCommand(cmd);
                    //onClickImgBtnHablar();
                    grabar.setText("GRABANDO VOZ");
                    btnForward.setText("DETENER");
                    isRecord = Boolean.FALSE;
                }else{
                    btnForward.setText("GRABAR");
                    grabar.setText("OUT");
                    isRecord = Boolean.TRUE;
                }
            }
        });

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case RECOGNIZE_SPEECH_ACTIVITY:
                if (resultCode == RESULT_OK && null != data) {
                    ArrayList<String> speech = data
                            .getStringArrayListExtra(RecognizerIntent.
                                    EXTRA_RESULTS);
                    String strSpeech2Text = speech.get(0);

                    helloID.setText(strSpeech2Text);
                }

                break;
            default:

                break;
        }
    }

    public void onClickImgBtnHablar() {

        Intent intentActionRecognizeSpeech = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);

        // Configura el Lenguaje (Español-México)
        intentActionRecognizeSpeech.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, "es-MX");
        try {
            startActivityForResult(intentActionRecognizeSpeech, RECOGNIZE_SPEECH_ACTIVITY);
        } catch (ActivityNotFoundException a) {
            Toast.makeText(getApplicationContext(),
                    "Tú dispositivo no soporta el reconocimiento por voz",
                    Toast.LENGTH_SHORT).show();
        }
    }

    public String sendCommand(YaiCmd cmd){
        Log.i("sendCommand", "Http client send");
        String responseStr = null;
        HttpGet request = new HttpGet("http://192.168.100.104/cmd?COMMAND=100001&P1=1001&P2=0&P3=0&P4=10001&P5=None&P6=None&P7=None");
        //AndroidHttpClient httpclient = AndroidHttpClient.newInstance("Android");
        HttpClient httpclient = new DefaultHttpClient();
        try {
            HttpResponse httpResponse = httpclient.execute(request);
            responseStr = httpResponse.getEntity().getContent().toString();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
        //finally {
        //    httpclient.close();
        //}
        Log.i("sendCommand", responseStr);
        return responseStr;
    }
}