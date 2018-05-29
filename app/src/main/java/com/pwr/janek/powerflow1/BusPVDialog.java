package com.pwr.janek.powerflow1;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.design.widget.TextInputLayout;
import android.widget.EditText;

public class BusPVDialog extends DialogFragment {

    public BusPVDialog(){
        this.mListener = null;
    }

    public void setBusDialogListener(BusDialogListener listener){
        this.mListener = listener;
    }

    public interface BusDialogListener {
        public void onDialogPositiveClick(float pg, float v);
        public void onDialogNegativeClick();
    }

    BusDialogListener mListener;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setView(getActivity().getLayoutInflater().inflate(R.layout.popup_bus_pv,null));
        builder.setTitle("Input bus values");
        builder.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                final TextInputLayout busPV_pg_wrapper = (TextInputLayout) getDialog().findViewById(R.id.bus_pv_pg_wrapper);
                final TextInputLayout busPV_v_wrapper = (TextInputLayout) getDialog().findViewById(R.id.bus_pv_v_wrapper);
                 EditText pg = (EditText) getDialog().findViewById(R.id.eddiText_bus_pv_pg);
                 EditText v = (EditText) getDialog().findViewById(R.id.editText_bus_pv_v);
                mListener.onDialogPositiveClick(
                        Float.parseFloat(busPV_pg_wrapper.getEditText().getText().toString()),
                        Float.parseFloat(busPV_v_wrapper.getEditText().getText().toString()));}
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



