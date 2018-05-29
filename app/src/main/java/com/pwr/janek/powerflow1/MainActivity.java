package com.pwr.janek.powerflow1;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.util.ArrayList;

import medusa.theone.waterdroplistview.view.WaterDropListView;

public class MainActivity extends Activity implements WaterDropListView.IWaterDropListViewListener{
    //TODO wyczyścić CustomListView by nie isntalowala sie SecondActiity
    public String TAG = "MainActivity";
    public float[] output = new float[16];
    public float defaultInput[] = {9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    public float[] input = new float[20];
    float line34_b,line34_g,line34_ss,line24_b,line24_g,line24_ss,line13_b,line13_g,line13_ss,line12_b,line12_g,line12_ss;
    float busPV_pg, busPV_v;
    float busPQ1_pl, busPQ1_ql;
    float busPQ2_pl, busPQ2_ql;
    float busSlack_v,busSlack_angle;
    private WaterDropListView listView;

    CustomAdapter adapter;
    private ArrayList<BusObject> busArray;

    static{
        System.loadLibrary("Algorithm");
    }

    private native float[] nMain(float[] args);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        busArray = new ArrayList<BusObject>();
        busArray.add(new BusObject(1,0,0,0));
        busArray.add(new BusObject(2,0,0,0));
        busArray.add(new BusObject(3,0,0,0));
        busArray.add(new BusObject(4,0,0,0));

        Button bus_slack = (Button) findViewById(R.id.button_bus_slack);
        bus_slack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                BusSlackDialog busSlackDialog = new BusSlackDialog();
                busSlackDialog.setBusDialogListener(new BusSlackDialog.BusDialogListener() {
                    @Override
                    public void onDialogPositiveClick(float v, float angle) {
                        busSlack_v = v;
                        busSlack_angle = angle;
                    }

                    @Override
                    public void onDialogNegativeClick() {

                    }
                });
                busSlackDialog.show(getFragmentManager(),"tag_bus_slack");
            }
        });



        Button bus_pq1 = (Button) findViewById(R.id.button_bus_pq1);
        bus_pq1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                BusPQDialog busPQDialog = new BusPQDialog();
                busPQDialog.setBusDialogListener(new BusPQDialog.BusDialogListener() {
                    @Override
                    public void onDialogPositiveClick(float pl, float ql) {
                        busPQ1_pl = pl;
                        busPQ1_ql = ql;
                    }

                    @Override
                    public void onDialogNegativeClick() {

                    }
                });
                busPQDialog.show(getFragmentManager(),"tag_bus_pq1");
            }
        });
        Button bus_pq2 = (Button) findViewById(R.id.button_bus_pq2);
        bus_pq2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                BusPQDialog busPQDialog = new BusPQDialog();
                busPQDialog.setBusDialogListener(new BusPQDialog.BusDialogListener() {
                    @Override
                    public void onDialogPositiveClick(float pl, float ql) {
                        busPQ2_pl = pl;
                        busPQ2_ql = ql;
                    }

                    @Override
                    public void onDialogNegativeClick() {

                    }
                });
                busPQDialog.show(getFragmentManager(),"tag_bus_pq2");
            }
        });
        Button bus_pv = (Button) findViewById(R.id.button_bus_pv);
        bus_pv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
               BusPVDialog busPVDialog = new BusPVDialog();
               busPVDialog.setBusDialogListener(new BusPVDialog.BusDialogListener() {
                   @Override
                   public void onDialogPositiveClick(float pg, float v) {
                       busPV_pg = pg;
                       busPV_v = v;
                   }

                   @Override
                   public void onDialogNegativeClick() {

                   }
               });
               busPVDialog.show(getFragmentManager(),"tag_bus_pv");
            }
        });

        Button line_12 = (Button) findViewById(R.id.button_line12);
        line_12.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                LineDialog lineDialog = new LineDialog();
                lineDialog.setLineDialogListener(new LineDialog.LineDialogListener() {
                    @Override
                    public void onDialogPositiveClick(float g, float b, float ss) {
                        line12_b = b;
                        line12_g = g;
                        line12_ss = ss;
                    }

                    @Override
                    public void onDialogNegativeClick() {

                    }
                });
                lineDialog.show(getFragmentManager(),"tag_line_34");
            }
        });
        Button line_13 = (Button) findViewById(R.id.button_line13);
        line_13.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                LineDialog lineDialog = new LineDialog();
                lineDialog.setLineDialogListener(new LineDialog.LineDialogListener() {
                    @Override
                    public void onDialogPositiveClick(float g, float b, float ss) {
                        line13_b = b;
                        line13_g = g;
                        line13_ss = ss;

                    }

                    @Override
                    public void onDialogNegativeClick() {

                    }
                });
                lineDialog.show(getFragmentManager(),"tag_line_34");
            }
        });
        Button line_24 = (Button) findViewById(R.id.button_line24);
        line_24.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                LineDialog lineDialog = new LineDialog();
                lineDialog.setLineDialogListener(new LineDialog.LineDialogListener() {
                    @Override
                    public void onDialogPositiveClick(float g, float b, float ss) {
                        line24_b = b;
                        line24_g = g;
                        line24_ss = ss;
                    }

                    @Override
                    public void onDialogNegativeClick() {

                    }
                });
                lineDialog.show(getFragmentManager(),"tag_line_24");
            }
        });
        Button line_34 = (Button) findViewById(R.id.button_line34);
        line_34.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                LineDialog lineDialog = new LineDialog();
                lineDialog.setLineDialogListener(new LineDialog.LineDialogListener() {
                    @Override
                    public void onDialogPositiveClick(float g, float b, float ss) {
                        line34_g = g;
                        line34_b = b;
                        line34_ss = ss;
                    }

                    @Override
                    public void onDialogNegativeClick() {

                    }
                });
                lineDialog.show(getFragmentManager(),"tag_line_34");
            }
        });

        listView = (WaterDropListView) findViewById(R.id.listView_layout);
        adapter = new CustomAdapter(this,busArray);
        listView.setAdapter(adapter);
        listView.setWaterDropListViewListener(this);
        listView.setPullLoadEnable(true);

    }

    private void prepareInput(){
        input[0] = busPV_pg;
        input[1] = busPV_v;
        input[2] = busPQ2_pl;
        input[3] = busPQ2_ql;
        input[4] = busPQ1_pl;
        input[5] = busPQ1_ql;
        input[6] = busSlack_v;
        input[7] = busSlack_angle;
        input[8] = line12_g;
        input[9] = line12_b;
        input[10] = line12_ss;
        input[11] = line13_g;
        input[12] = line13_b;
        input[13] = line13_ss;
        input[14] = line24_g;
        input[15] = line24_b;
        input[16] = line24_ss;
        input[17] = line34_g;
        input[18] = line34_b;
        input[19] = line34_ss;
    }

    private void prepareOutput(){
        busArray.clear();
        busArray.add(new BusObject(output[0],output[4],output[8],output[12]));
        busArray.add(new BusObject(output[1],output[5],output[9],output[13]));
        busArray.add(new BusObject(output[2],output[6],output[10],output[14]));
        busArray.add(new BusObject(output[3],output[7],output[11],output[15]));
        adapter.notifyDataSetChanged();
    }

    @Override
    public void onRefresh() {
        prepareInput();
        output = nMain(input);
        prepareOutput();
        listView.stopRefresh();
    }

    @Override
    public void onLoadMore() {
        listView.stopLoadMore();
        output = nMain(defaultInput);
        prepareOutput();
    }
}

