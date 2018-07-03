package com.example.database;

import android.database.Cursor;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    DataBaseHelper myDb;
    EditText editName, editSurname, editMarks;
    Button btnAddData;
    Button btnViewAll;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myDb = new DataBaseHelper(this);
        editName = (EditText) findViewById(R.id.editText_name);
        editSurname = (EditText) findViewById(R.id.editText_surname);
        editMarks = (EditText) findViewById(R.id.editText_Marks);
        btnAddData = (Button) findViewById(R.id.button_add);
        btnViewAll = (Button) findViewById(R.id.button_viewAll);

        AddData();
        viewAll();

    }

    public void AddData(){
        btnAddData.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick (View v){
                        boolean isInserted =   myDb.insertData(editName.getText().toString(), editSurname.getText().toString(),editMarks.getText().toString() );
                        if (isInserted = true)
                            Toast.makeText(MainActivity.this,"Data Inserted",Toast.LENGTH_LONG).show();
                        else
                            Toast.makeText(MainActivity.this,"Data Not Inserted",Toast.LENGTH_LONG).show();
                    }
                }
        );
    }

    public void viewAll(){
        btnViewAll.setOnClickListener(
                new View.OnClickListener(){
                    @Override
                    public void onClick (View v){
                        Cursor res = myDb.getAllData();
                        if (res.getCount() == 0)
                        {
                            showMessage("Error","No data found");
                            return;

                        }
                        StringBuffer buffer = new StringBuffer();
                        while( res.moveToNext()){
                            buffer.append("Id:"  + res.getString(0)+ "\n");
                            buffer.append("Name:"  + res.getString(1)+ "\n");
                            buffer.append("Surname:"  + res.getString(2)+ "\n");
                            buffer.append("Marks:"  + res.getString(3)+ "\n\n");

                        }

                        showMessage("Data",buffer.toString());

                    }

                }
        );

    }

    public void showMessage(String title,  String Message){

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setCancelable(true);
        builder.setTitle(title);
        builder.setMessage(Message);
        builder.show();

    }
}
