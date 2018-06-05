package com.pwr.janek.powerflow1;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.design.widget.TextInputLayout;
import android.widget.EditText;

public class BusPQDialog extends DialogFragment {

    public BusPQDialog(){
        this.mListener = null;
    }

    public void setBusDialogListener(BusDialogListener listener){
        this.mListener = listener;
    }

    public interface BusDialogListener {
        public void onDialogPositiveClick(float pl, float ql);
        public void onDialogNegativeClick();
    }

    BusDialogListener mListener;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setView(getActivity().getLayoutInflater().inflate(R.layout.popup_bus_pq,null));
        builder.setTitle("Input bus values");
        builder.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                final TextInputLayout busPQ_pl_wrapper = (TextInputLayout) getDialog().findViewById(R.id.bus_pq_pl_wrapper);
                final TextInputLayout busPQ_ql_wrapper = (TextInputLayout) getDialog().findViewById(R.id.bus_pq_ql_wrapper);
                busPQ_ql_wrapper.setHint("QL");
                busPQ_pl_wrapper.setHint("PL");
                EditText pl = (EditText) getDialog().findViewById(R.id.eddiText_bus_pq_pl);
                EditText ql = (EditText) getDialog().findViewById(R.id.editText_bus_pq_ql);
                mListener.onDialogPositiveClick(
                        Float.parseFloat(busPQ_pl_wrapper.getEditText().getText().toString()),
                        Float.parseFloat(busPQ_ql_wrapper.getEditText().getText().toString()));}
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



