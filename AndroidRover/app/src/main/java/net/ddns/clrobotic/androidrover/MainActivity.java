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
import org.apache.commons.lang3.StringUtils;
import net.ddns.clrobotic.androidrover.enums.CommandEnum;
import net.ddns.clrobotic.androidrover.enums.RoverMoveEnum;
import net.ddns.clrobotic.androidrover.enums.VoiceCmdEnum;
import net.ddns.clrobotic.androidrover.utils.YaiCommandUtil;

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
    protected Boolean laserStatus = Boolean.FALSE;
    private static final Boolean ENABLE_SEND_CMD = Boolean.TRUE;
    private static final String IP_YAI_ROVER = "192.168.0.22";
    private static final String ROVER_TYPE_2WD = "1001";


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
        }
        btnForward = (Button)findViewById(R.id.btn_forward);
        grabar = (TextView) findViewById(R.id.textOutId);
        helloID = (TextView) findViewById(R.id.textHelloId);
        btnForward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i("MainActivity", "isRecord::"+isRecord);
                onClickImgBtnHablar();
                isRecord = Boolean.TRUE;
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        isRecord = Boolean.FALSE;
        switch (requestCode) {
            case RECOGNIZE_SPEECH_ACTIVITY:
                if (resultCode == RESULT_OK && null != data) {
                    ArrayList<String> speech = data
                            .getStringArrayListExtra(RecognizerIntent.
                                    EXTRA_RESULTS);
                    String strSpeech2Text = speech.get(0);

                    helloID.setText(strSpeech2Text);
                    YaiCmd cmd = new YaiCmd();
                    String voiceCmd = strSpeech2Text.toUpperCase();
                    voiceCmd = StringUtils.stripAccents(voiceCmd);
                    if(VoiceCmdEnum.LASER.getCodigo().contains(voiceCmd)){
                        cmd.setCommand(CommandEnum.LASER_ACTION.getCodigo());
                        cmd.setP1(laserStatus.toString().toLowerCase());
                        cmd.setP2("0");
                        laserStatus = laserStatus?Boolean.FALSE:Boolean.TRUE;
                    }
                    if(VoiceCmdEnum.ROVER_STOP.getCodigo().contains(voiceCmd)) {
                        cmd.setCommand(CommandEnum.ROVER_STOP.getCodigo());
                        cmd.setP1(ROVER_TYPE_2WD);
                        cmd.setP2("0");
                        cmd.setP3("0");
                    }
                    if(VoiceCmdEnum.ROVER_LEFT.getCodigo().contains(voiceCmd) ||
                            VoiceCmdEnum.ROVER_RIGHT.getCodigo().contains(voiceCmd) ||
                            VoiceCmdEnum.ROVER_FORWARD.getCodigo().contains(voiceCmd) ||
                            VoiceCmdEnum.ROVER_BACK.getCodigo().contains(voiceCmd)) {
                        cmd.setCommand(CommandEnum.ROVER_MOVE_MANUAL_BODY.getCodigo());
                        cmd.setP1(ROVER_TYPE_2WD);
                        cmd.setP2("0");
                        cmd.setP3("0");
                        if(VoiceCmdEnum.ROVER_LEFT.getCodigo().contains(voiceCmd)) {
                            cmd.setP4(RoverMoveEnum.ROVER_BODY_MOVE_TYPE_LEFT.getCodigo());
                        }
                        if(VoiceCmdEnum.ROVER_RIGHT.getCodigo().contains(voiceCmd)) {
                            cmd.setP4(RoverMoveEnum.ROVER_BODY_MOVE_TYPE_RIGHT.getCodigo());
                        }
                        if(VoiceCmdEnum.ROVER_FORWARD.getCodigo().contains(voiceCmd)) {
                            cmd.setP4(RoverMoveEnum.ROVER_BODY_MOVE_TYPE_FORWARD.getCodigo());
                        }
                        if(VoiceCmdEnum.ROVER_BACK.getCodigo().contains(voiceCmd)) {
                            cmd.setP4(RoverMoveEnum.ROVER_BODY_MOVE_TYPE_BACK.getCodigo());
                        }
                    }
                    grabar.setText(cmd.toString());
                    sendCommand(cmd);
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
        Log.i("sendCommand", cmd.toString());
        String responseStr = null;
        if(ENABLE_SEND_CMD) {
            String url = YaiCommandUtil.getUri(cmd);
            Log.i("sendCommand", "Http client send: "+url);
            HttpGet request = new HttpGet(url);
            //AndroidHttpClient httpclient = AndroidHttpClient.newInstance("Android");
            HttpClient httpclient = new DefaultHttpClient();
            try {
                HttpResponse httpResponse = httpclient.execute(request);
                responseStr = httpResponse.getEntity().getContent().toString();
            } catch (IOException e) {
                e.printStackTrace();
                return null;
            }
            Log.i("sendCommand", responseStr);
        }
        return responseStr;
    }
}