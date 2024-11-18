package com.example.lab_2

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val recyclerView: RecyclerView = findViewById(R.id.recyclerView)

        val animals = listOf(
            Animal("Lion", R.drawable.lion),
            Animal("Tiger", R.drawable.tiger),
            Animal("Elephant", R.drawable.elephant),
            Animal("Giraffe", R.drawable.giraffe),
            Animal("Panda", R.drawable.panda),
            Animal("Kangaroo", R.drawable.kangaroo),
            Animal("Zebra", R.drawable.zebra),
            Animal("Penguin", R.drawable.penguin),
            Animal("Koala", R.drawable.koala),
            Animal("Dolphin", R.drawable.dolphin)
        )

        recyclerView.layoutManager = LinearLayoutManager(this)
        recyclerView.adapter = AnimalAdapter(animals)
    }
}
