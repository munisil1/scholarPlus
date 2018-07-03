package com.example.testingbluetooth;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.bluetooth.BluetoothAdapter;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter == null){
            //device not support bluetooth inforom user we are done
        }

        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("text/plain");
   intent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(file_to_trasnfer));

    startActivity(intent);
