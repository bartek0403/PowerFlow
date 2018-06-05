package com.pwr.janek.powerflow1;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.design.widget.TextInputLayout;
import android.widget.EditText;

public class BusSlackDialog extends DialogFragment {

    public BusSlackDialog(){
        this.mListener = null;
    }

    public void setBusDialogListener(BusDialogListener listener){
        this.mListener = listener;
    }

    public interface BusDialogListener {
        public void onDialogPositiveClick(float v, float angle);
        public void onDialogNegativeClick();
    }

    BusDialogListener mListener;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setView(getActivity().getLayoutInflater().inflate(R.layout.popup_bus_slack,null));
        builder.setTitle("Input bus values");
        builder.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                final TextInputLayout busSlack_v_wrapper = (TextInputLayout) getDialog().findViewById(R.id.bus_slack_v_wrapper);
                final TextInputLayout busSlack_angle_wrapper = (TextInputLayout) getDialog().findViewById(R.id.bus_slack_angle_wrapper);
                EditText v = (EditText) getDialog().findViewById(R.id.eddiText_bus_slack_v);
                EditText angle = (EditText) getDialog().findViewById(R.id.editText_bus_slack_angle);
                mListener.onDialogPositiveClick(
                        Float.parseFloat(busSlack_v_wrapper.getEditText().getText().toString()),
                        Float.parseFloat(busSlack_angle_wrapper.getEditText().getText().toString()));}
        });
        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                mListener.onDialogNegativeClick();
                dialogInterface.dismiss();
            }
        });
        return builder.create();
    }
}



