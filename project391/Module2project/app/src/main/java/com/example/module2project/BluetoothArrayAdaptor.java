package com.example.module2project;

//import android.widget.ArrayAdapter;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Hassen on 2017-03-10.
 */

/*public class BluetoothArrayAdaptor extends ArrayAdapter<String>{

    // my new class variables, copies of constructor params, but add more if required
    private Context context ;
    private ArrayList<String> theStringArray;

    //constructor
    public BluetoothArrayAdaptor(Context _context, int textViewResourceId, ArrayList<String> _theStringArray) {
        super(_context, textViewResourceId, _theStringArray);

        // save the context and the array of strings we were given
        context = _context;
        theStringArray = _theStringArray;


    }
}*/



/**
 * A row on the table of discovered Bluetooth devices.
 */
public class BluetoothArrayAdaptor extends ArrayAdapter<String> {
    // my new class variables, copies of constructor params, but add more if required
    private Context context ;
    private ArrayList<String> theStringArray;



    // constructor
    public BluetoothArrayAdaptor(Context _context,int textViewResourceId,ArrayList<String> _theStringArray) {
        // call base class constructor
        super(_context, textViewResourceId, _theStringArray);
        // save the context and the array of strings we were given
        context = _context;
        theStringArray = _theStringArray;
    }


}