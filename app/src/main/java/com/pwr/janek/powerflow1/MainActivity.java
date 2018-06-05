package com.pwr.janek.powerflow1;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import medusa.theone.waterdroplistview.view.WaterDropListView;

public class MainActivity extends Activity implements WaterDropListView.IWaterDropListViewListener {

    //TODO wyczyścić CustomListView by nie isntalowala sie SecondActiity

    public String TAG = "MainActivity";
    public float[] output = new float[16];
    public float defaultInput[] = {318, 1.02f, 200, 123.94f, 170, 105.35f, 1, 0, 3.81f, -19.07f, 0.051f, 5.16f, -25.84f, 0.038f, 5.16f, -25.84f, 0.038f, 3.02f, -15.11f, 0.063f};
    public float[] input = new float[20];
    float line34_b, line34_g, line34_ss, line24_b, line24_g, line24_ss, line13_b, line13_g, line13_ss, line12_b, line12_g, line12_ss;
    float busPV_pg, busPV_v;
    float busPQ1_pl, busPQ1_ql;
    float busPQ2_pl, busPQ2_ql;
    float busSlack_v, busSlack_angle;
    private WaterDropListView downListView;
    private ListView upListView;
    private TextView header;
    private View busImageView;
    private View spaceView;
    CustomAdapter adapter;
    private ArrayList<BusObject> busArray;

    static {
        System.loadLibrary("Algorithm");
    }

    private native float[] nMain(float[] args);

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        busArray = new ArrayList<BusObject>();
        busArray.add(new BusObject(1, 0, 0, 0));
        busArray.add(new BusObject(2, 0, 0, 0));
        busArray.add(new BusObject(3, 0, 0, 0));
        busArray.add(new BusObject(4, 0, 0, 0));

        downListView = (WaterDropListView) findViewById(R.id.listView_layout);
        adapter = new CustomAdapter(this, busArray);
        downListView.setAdapter(adapter);
        downListView.setWaterDropListViewListener(this);
        downListView.setPullLoadEnable(true);

        upListView = (ListView) findViewById(R.id.busValues_listView);
        busImageView = findViewById(R.id.bus_imageView);
        header = (TextView) findViewById(R.id.header_textview);

        LayoutInflater inflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View listHeader = inflater.inflate(R.layout.header_layout, null);
        spaceView = listHeader.findViewById(R.id.stickyViewPlaceholder);

        upListView.addHeaderView(listHeader);
        upListView.setOnScrollListener(new AbsListView.OnScrollListener() {
            @Override
            public void onScrollStateChanged(AbsListView absListView, int i) {

            }

            @Override
            public void onScroll(AbsListView absListView, int i, int i1, int i2) {
                if (upListView.getFirstVisiblePosition() == 0) {
                    View firstChild = upListView.getChildAt(0);
                    int topY = 0;
                    if (firstChild != null) {
                        topY = firstChild.getTop();
                    }

                    int heroTopY = spaceView.getTop();
                    header.setY(Math.max(0, heroTopY + topY));

                    busImageView.setY(topY * 0.5f);
                }

            }
        });

        List<String> valuesList = new ArrayList<>();
        valuesList.add("Slack Bus no.1");
        valuesList.add("PQ Bus no. 2");
        valuesList.add("PQ Bus no.3");
        valuesList.add("PV Bus no.4");
        valuesList.add("Line 1-2");
        valuesList.add("Line 1-3");
        valuesList.add("Line 2-4");
        valuesList.add("Line 3-4");

        ArrayAdapter adapter = new ArrayAdapter(this, R.layout.single_row_input, valuesList);
        upListView.setAdapter(adapter);
        upListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                switch (i) {

                    case 1:
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
                        busSlackDialog.show(getFragmentManager(), "tag_bus_slack");
                        break;

                    case 2:
                        BusPQDialog busPQDialog1 = new BusPQDialog();
                        busPQDialog1.setBusDialogListener(new BusPQDialog.BusDialogListener() {
                            @Override
                            public void onDialogPositiveClick(float pl, float ql) {
                                busPQ1_pl = pl;
                                busPQ1_ql = ql;
                            }

                            @Override
                            public void onDialogNegativeClick() {

                            }
                        });
                        busPQDialog1.show(getFragmentManager(), "tag_bus_pq1");
                        break;

                    case 3:
                        BusPQDialog busPQDialog2 = new BusPQDialog();
                        busPQDialog2.setBusDialogListener(new BusPQDialog.BusDialogListener() {
                            @Override
                            public void onDialogPositiveClick(float pl, float ql) {
                                busPQ2_pl = pl;
                                busPQ2_ql = ql;
                            }

                            @Override
                            public void onDialogNegativeClick() {

                            }
                        });
                        busPQDialog2.show(getFragmentManager(), "tag_bus_pq2");
                        break;

                    case 4:
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
                        busPVDialog.show(getFragmentManager(), "tag_bus_pv");
                        break;

                    case 5:
                        LineDialog lineDialog12 = new LineDialog();
                        lineDialog12.setLineDialogListener(new LineDialog.LineDialogListener() {
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
                        lineDialog12.show(getFragmentManager(), "tag_line_34");
                        break;

                    case 6:
                        LineDialog lineDialog13 = new LineDialog();
                        lineDialog13.setLineDialogListener(new LineDialog.LineDialogListener() {
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
                        lineDialog13.show(getFragmentManager(), "tag_line_34");
                        break;

                    case 7:
                        LineDialog lineDialog24 = new LineDialog();
                        lineDialog24.setLineDialogListener(new LineDialog.LineDialogListener() {
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
                        lineDialog24.show(getFragmentManager(), "tag_line_24");
                        break;

                    case 8:
                        LineDialog lineDialog34 = new LineDialog();
                        lineDialog34.setLineDialogListener(new LineDialog.LineDialogListener() {
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
                        lineDialog34.show(getFragmentManager(), "tag_line_34");
                }
            }
        });


    }

    private void prepareInput() {
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

    private void prepareOutput() {
        busArray.clear();
        busArray.add(new BusObject(output[0], output[4], output[8], output[12]));
        busArray.add(new BusObject(output[1], output[5], output[9], output[13]));
        busArray.add(new BusObject(output[2], output[6], output[10], output[14]));
        busArray.add(new BusObject(output[3], output[7], output[11], output[15]));
        adapter.notifyDataSetChanged();
    }

    @Override
    public void onRefresh() {
        prepareInput();
        output = nMain(input);
        prepareOutput();
        downListView.stopRefresh();
    }

    @Override
    public void onLoadMore() {
        downListView.stopLoadMore();
        output = nMain(defaultInput);
        prepareOutput();
    }
}

