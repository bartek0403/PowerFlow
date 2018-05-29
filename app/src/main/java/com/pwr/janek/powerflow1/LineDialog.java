package com.pwr.janek.powerflow1;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.design.widget.TextInputLayout;
import android.widget.EditText;

/**
 * Created by Janusz Tracz on 19.05.2018.
 */

public class LineDialog extends DialogFragment{
    public LineDialog(){
        this.mListener = null;
    }

    public interface LineDialogListener {
        public void onDialogPositiveClick(float g, float b, float ss);
        public void onDialogNegativeClick();
    }

    private LineDialogListener mListener;

    public void setLineDialogListener(LineDialogListener listener){
        this.mListener = listener;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setView(getActivity().getLayoutInflater().inflate(R.layout.popup_line,null));
        builder.setTitle("Input bus values");
        builder.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                final TextInputLayout line_g_wrapper = (TextInputLayout) getDialog().findViewById(R.id.line_g_wrapper);
                final TextInputLayout line_b_wrapper = (TextInputLayout) getDialog().findViewById(R.id.line_b_wrapper);
                final TextInputLayout line_ss_wrapper = (TextInputLayout) getDialog().findViewById(R.id.line_ss_wrapper);
                EditText g = (EditText) getDialog().findViewById(R.id.editText_line_g);
                EditText b = (EditText) getDialog().findViewById(R.id.editText_line_b);
                EditText ss = (EditText) getDialog().findViewById(R.id.editText_line_ss);
                mListener.onDialogPositiveClick
                        (Float.parseFloat(line_g_wrapper.getEditText().getText().toString()),
                        Float.parseFloat(line_b_wrapper.getEditText().getText().toString()),
                        Float.parseFloat(line_ss_wrapper.getEditText().getText().toString()));;
            }
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
