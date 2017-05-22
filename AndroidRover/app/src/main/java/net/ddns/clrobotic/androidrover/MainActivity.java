package net.ddns.clrobotic.androidrover;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button btnForward;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.i("MainActivity", "onCreate...");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btnForward = (Button)findViewById(R.id.btn_forward);
        btnForward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i("MainActivity", "apretaste btn forward");
            }
        });

    }
}
