package com.example.lab_1;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class SecondActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        TextView greetingTextView = findViewById(R.id.greetingTextView);
        EditText nameEditText = findViewById(R.id.nameEditText);
        Button backButton = findViewById(R.id.backButton);

        String greeting = getIntent().getStringExtra("GREETING_TEXT");
        greetingTextView.setText(greeting);

        backButton.setOnClickListener(v -> {
            String name = nameEditText.getText().toString();

            Intent resultIntent = new Intent();
            resultIntent.putExtra("USER_NAME", name);
            setResult(RESULT_OK, resultIntent);
            finish();
        });
    }
}
