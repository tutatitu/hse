package com.example.lab_1;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private EditText greetingEditText;
    private TextView resultTextView;
    private static final int REQUEST_CODE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        greetingEditText = findViewById(R.id.greetingEditText);
        resultTextView = findViewById(R.id.resultTextView);
        Button goToSecondButton = findViewById(R.id.goToSecondButton);

        goToSecondButton.setOnClickListener(v -> {
            String greeting = greetingEditText.getText().toString();

            Intent intent = new Intent(MainActivity.this, SecondActivity.class);
            intent.putExtra("GREETING_TEXT", greeting);
            startActivityForResult(intent, REQUEST_CODE);
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE && resultCode == RESULT_OK) {
            String name = data.getStringExtra("USER_NAME");
            String greeting = greetingEditText.getText().toString();
            resultTextView.setText(greeting + ", " + name);
        }
    }
}
