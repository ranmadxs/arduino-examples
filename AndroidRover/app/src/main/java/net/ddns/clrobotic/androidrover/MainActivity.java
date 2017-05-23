package net.ddns.clrobotic.androidrover;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.speech.RecognizerIntent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

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
        btnForward = (Button)findViewById(R.id.btn_forward);
        grabar = (TextView) findViewById(R.id.textOutId);
        helloID = (TextView) findViewById(R.id.textHelloId);
        btnForward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i("MainActivity", "isRecord::"+isRecord);
                if(isRecord){
                    onClickImgBtnHablar();
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
}