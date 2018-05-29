package com.pwr.janek.powerflow1;

import android.app.Activity;
import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.text.DecimalFormat;
import java.util.ArrayList;


public class CustomAdapter extends ArrayAdapter<BusObject> {

    private final Context context;
    private ArrayList<BusObject> events;

    public CustomAdapter(Activity context, ArrayList<BusObject> busObjects){
        super(context,0, busObjects);
        this.context = context;
        this.events = busObjects;

    }


    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {

        DecimalFormat dec = new DecimalFormat();
        dec.setMaximumFractionDigits(2);
        dec.setMinimumFractionDigits(2);

       View listItemView = convertView;
       if(listItemView ==null){
           listItemView = LayoutInflater.from(getContext()).inflate(R.layout.single_row,parent,false);
       }

        BusObject currentBus = getItem(position);

        TextView busNumber = (TextView) listItemView.findViewById(R.id.textView_row_busumber);
        busNumber.setText(String.valueOf((int)currentBus.getBusNumber()));

        TextView busType = (TextView) listItemView.findViewById(R.id.textView_row_bustype);
        busType.setText(currentBus.getBusType());

        TextView busVoltege = (TextView) listItemView.findViewById(R.id.textView_row_volage);
        busVoltege.setText(String.valueOf(dec.format(currentBus.getBusVoltage())));

        TextView busAngle = (TextView) listItemView.findViewById(R.id.textView_row_angle);
        busAngle.setText(String.valueOf(dec.format(currentBus.getBusAngle())));

        return listItemView;
    }
}

