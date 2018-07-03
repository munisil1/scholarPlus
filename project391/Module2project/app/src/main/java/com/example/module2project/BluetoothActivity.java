package com.example.module2project;

//import android.support.v7.app.AppCompatActivity;
import android.Manifest;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.location.Location;
import android.os.Build;
import android.os.Bundle;
import android.os.SystemClock;
//import android.support.design.widget.Snackbar;
import android.support.v4.app.NotificationCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;


import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.UUID;


/**
 * Created by Hassen on 2017-03-10.
 */

public class BluetoothActivity extends AppCompatActivity {

    // A constant that we use to determine if our request to turn on bluetooth worked
    private final static int REQUEST_ENABLE_BT = 1;
    // A handle to the tablet’s bluetooth adapter
    private BluetoothAdapter mBluetoothAdapter;
    private Context context;
    // App-defined int constant used for handling permissions requests
    private static final int BL_PERMISSIONS_REQUEST_BLUETOOTH = 0;
    private static final int BL_PERMISSIONS_REQUEST_BLUETOOTH_ADMIN = 1;
    //step1
    private BluetoothArrayAdaptor PairedArrayAdapter;
    private BluetoothArrayAdaptor DiscoveredArrayAdapter;

    private BroadcastReceiver mReceiver;

    // Store discovered devices(step3)
    // an Array/List to hold discovered Bluetooth devices
    // A bluetooth device contains device Name and Mac Address information which
    // we want to display to the user in a List View so they can choose a device
    // to connect to. We also need that info to actually connect to the device

    private ArrayList<BluetoothDevice> DiscoveredDevices = new ArrayList<BluetoothDevice>();
    // an Array/List to hold string details of the Bluetooth devices, name + MAC address etc.
    // this is displayed in the listview for the user to choose
    private ArrayList<String> DiscoveredDetails = new ArrayList<String>();

    // Store paired devices(step connecting to a paired bD)
    private ArrayList<BluetoothDevice> PairedDevices = new ArrayList<BluetoothDevice>();
    private ArrayList<String> PairedDetails = new ArrayList<String>();

    // Socket and streams to communicate
    private BluetoothSocket mmSocket = null;
    // input/output “streams” with which we can read and write to device
    // Use of “static” important, it means variables can be accessed
    // without an object, this is useful as other activities can use
    // these streams to communicate after they have been opened.

    public static InputStream mmInStream = null;
    public static OutputStream mmOutStream = null;

    // Connection flag
    boolean connected = false;

    private AdapterView.OnItemClickListener mPairedClickedHandler = new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
            String text = "Connecting to: " +
                    PairedDetails.get(position);
            //Toast.makeText(context, text, Toast.LENGTH_LONG).show();

            if (connected) closeConnection(); // Disconnect before connecting again

            // Connect to the geocache
            CreateSerialBluetoothDeviceSocket(PairedDevices.get(position));
            ConnectToSerialBlueToothDevice(); // user defined fn

            // update the view of discovered devices if required
            PairedArrayAdapter.notifyDataSetChanged();
        }
    };

    private AdapterView.OnItemClickListener mDiscoveredClickedHandler = new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
            String text = "Discovered Device: " +
                    DiscoveredDetails.get(position);
            Toast.makeText(context, text, Toast.LENGTH_LONG).show();

            if (connected) closeConnection(); // Disconnect before connecting again

            // Connect to the geocache
            CreateSerialBluetoothDeviceSocket(DiscoveredDevices.get(position));
            ConnectToSerialBlueToothDevice();

            DiscoveredArrayAdapter.notifyDataSetChanged();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bluetooth);
        context = getApplicationContext();
/////////////////////////////////////////////////
        // Check if the user has set the necessary permissions to use Bluetooth.
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH)
                != PackageManager.PERMISSION_GRANTED) {
            // Permission has not been granted; just exit the app for now
            Toast.makeText(context, "Please enable Bluetooth permissions",
                    Toast.LENGTH_LONG).show();
            finish();
        } else {
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_ADMIN)
                    != PackageManager.PERMISSION_GRANTED) {
                // Permission has not been granted; just exit the app for now
                Toast.makeText(context, "Please enable Bluetooth permissions",
                        Toast.LENGTH_LONG).show();
                finish();
            } else {
                // This call returns a handle to the one bluetooth device within your Android device
                mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
            }
        }

        // Do we have a bluetooth device?(step 1)
        if (mBluetoothAdapter == null) {
            Toast toast = Toast.makeText(context, "No Bluetooth adapter found", Toast.LENGTH_LONG);
            toast.show();
            finish();
            return;
        }

        // Create adapters(step 1)
        PairedArrayAdapter = new BluetoothArrayAdaptor(this,
                android.R.layout.simple_list_item_1, PairedDetails);
        DiscoveredArrayAdapter = new BluetoothArrayAdaptor(this,
                android.R.layout.simple_list_item_1, DiscoveredDetails);


        // Create views(step1)
        // for bluetooth devices
        ListView PairedlistView = (ListView) findViewById(R.id.listView2);
        ListView DiscoveredlistView = (ListView) findViewById(R.id.listView3);
        PairedlistView.setOnItemClickListener(mPairedClickedHandler);
        DiscoveredlistView.setOnItemClickListener(mDiscoveredClickedHandler);
        PairedlistView.setAdapter(PairedArrayAdapter);
        DiscoveredlistView.setAdapter(DiscoveredArrayAdapter);
///////////////////////////////////////
        // Enable bluetooth if necessary(turn on bluetooth Step2)
        if (!mBluetoothAdapter.isEnabled()) {
            // create a new intent that will ask the bluetooth adaptor to “enable” itself.
            // A dialog box will appear asking if you want turn on the bluetooth device
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);

            // REQUEST_ENABLE_BT below is a constant (defined as '1 - but could be anything)
            // When the “activity” is run and finishes, Android will run your onActivityResult()
            // function (see next page) where you can determine if it was successful or not
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
        //DISCOVERY STEP
        //receive info about each device through egistering a broadcastReceiver
        mReceiver = new BroadcastReceiver() {
            public void onReceive(Context context, Intent intent) {
                String action = intent.getAction();
                BluetoothDevice newDevice;

                if (action.equals(BluetoothDevice.ACTION_FOUND)) {
                    // Discovery has found a device. Get the BluetoothDevice
                    // object and its info from the Intent.
                    newDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

                    // Show details of found device
                    String theDevice = new String(newDevice.getName() +
                            "\nMAC Address = " + newDevice.getAddress());

                    Toast.makeText(context, theDevice, Toast.LENGTH_LONG).show();

                    // Add to devices
                    DiscoveredDevices.add(newDevice);
                    DiscoveredDetails.add(theDevice);
                    // notify array adaptor that the contents of String Array have changed
                    DiscoveredArrayAdapter.notifyDataSetChanged();
                } else if (action.equals(BluetoothAdapter.ACTION_DISCOVERY_STARTED)) {
                    Toast.makeText(context, "Discovery Started", Toast.LENGTH_LONG).show();
                } else if (action.equals(BluetoothAdapter.ACTION_DISCOVERY_FINISHED)) {
                    Toast.makeText(context, "Discovery Finished", Toast.LENGTH_LONG).show();
                }
            }
        };

        // create 3 separate IntentFilters that are tuned to listen to certain Android notifications
        // 1) when new Bluetooth devices are discovered,
        // 2) when discovery of devices starts (not essential but give useful feedback)
        // 3) When discovery ends (not essential but give useful feedback)
        IntentFilter filterFound = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        IntentFilter filterStart = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        IntentFilter filterStop = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        // register our broadcast receiver using the filters defined above
        // our broadcast receiver will have it’s “onReceive()” function called
        // so it gets called every time a notification is broadcast by Android that matches one of
        //the
        // 3 filters, e.g.
        // a new bluetooth device is found or discovery starts or finishes
        // we should unregister it again when the app ends in onDestroy() - see later
        registerReceiver(mReceiver, filterFound);
        registerReceiver(mReceiver, filterStart);
        registerReceiver(mReceiver, filterStop);

        Set<BluetoothDevice> thePairedDevices = mBluetoothAdapter.getBondedDevices();
        // If there are devices that have already been paired
        // get an iterator for the set of devices and iterate 1 device at a time
        if (thePairedDevices.size() > 0) {
            Iterator<BluetoothDevice> iter = thePairedDevices.iterator();
            BluetoothDevice aNewdevice;
            while (iter.hasNext()) {
                aNewdevice = iter.next();
                // Show details of paired device
                String PairedDevice = new String(aNewdevice.getName()
                        + "\nMAC Address = " + aNewdevice.getAddress());
                // Add the new device details to the array
                PairedDevices.add(aNewdevice);
                PairedDetails.add(PairedDevice);
                PairedArrayAdapter.notifyDataSetChanged();//update list on screen
            }

        }

        // Before starting discovery make sure discovery is cancelled
        if (mBluetoothAdapter.isDiscovering())
            mBluetoothAdapter.cancelDiscovery();
        // now start scanning for new devices. The broadcast receiver
        // we wrote earlier will be called each time we discover a new device
        // don't make this call if you only want to show paired devices

        mBluetoothAdapter.startDiscovery();


    }//end of on  create

    // make sure we unregister
    // our broadcast receiver at end
    public void onDestroy() {
        unregisterReceiver(mReceiver);
        super.onDestroy();
    }

    //step2 following
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_ENABLE_BT) {
            if (resultCode != RESULT_OK) {
                Toast toast = Toast.makeText(context, "Bluetooth failed to start",
                        Toast.LENGTH_LONG);
                toast.show();
                finish();
                return;
            }
        }
    }

    void closeConnection() {
        try {
            mmInStream.close();
            mmInStream = null;
        } catch (IOException e) {
        }
        try {
            mmOutStream.close();
            mmOutStream = null;
        } catch (IOException e) {
        }
        try {
            mmSocket.close();
            mmSocket = null;
        } catch (IOException e) {
        }

        //from slides
        connected = false;
    }

    public void CreateSerialBluetoothDeviceSocket(BluetoothDevice device) {
        mmSocket = null;

        // UUID
        UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
        try {
            mmSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
        } catch (IOException e) {
            Toast.makeText(context, "Socket Creation Failed", Toast.LENGTH_LONG).show();
        }
    }

    // It tries to open a socket to the selected bluetooth device.
    public void ConnectToSerialBlueToothDevice() {
        // Cancel discovery because it will slow down the connection
        mBluetoothAdapter.cancelDiscovery();
        try {
            mmSocket.connect();
            // System.out.println("Connected");
            Toast.makeText(context, "Connection Made", Toast.LENGTH_LONG).show();
            // connected = true;
            // CommunicateWithDE2();
        } catch (IOException connectException) {
            Toast.makeText(context, "Connection Failed", Toast.LENGTH_LONG).show();
            return;
        }

        //create the input/output stream and record fact we have made a connection
        GetInputOutputStreamsForSocket(); // see page 26
        connected = true;

    }

    // gets the input/output stream associated with the current socket
    public void GetInputOutputStreamsForSocket() {
        try {
            mmInStream = mmSocket.getInputStream();
            mmOutStream = mmSocket.getOutputStream();
        } catch (IOException e) {
        }
    }


    //
// This function write a line of text (in the form of an array of bytes)
// to the Bluetooth device and then sends the string “\r\n”
// (required by the bluetooth dongle)
//
    public void WriteToBTDevice(String message) {
        String s = new String("\r\n");
        byte[] msgBuffer = message.getBytes();
        byte[] newline = s.getBytes();

        try {
            mmOutStream.write(msgBuffer);
            mmOutStream.write(newline);
        } catch (IOException e) {
        }
    }

    // This function reads a line of text from the Bluetooth device
    public String ReadFromBTDevice() {
        byte c;
        String s = new String("");

        try { // Read from the InputStream using polling and timeout
            for (int i = 0; i < 200; i++) { // try to read for 2 seconds max
                SystemClock.sleep(10);
                if (mmInStream.available() > 0) {
                    if ((c = (byte) mmInStream.read()) != '\r') // '\r' terminator
                        s += (char) c; // build up string 1 byte by byte
                    else
                        return s;
                }
            }
        } catch (IOException e) {
            return new String("-- No Response --");
        }

        return s;
    }















}


