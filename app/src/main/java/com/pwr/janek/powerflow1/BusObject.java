package com.pwr.janek.powerflow1;

public class BusObject {

    private float mBusNumber;
    private float mBusType;
    private float mBusVoltage;
    private float mBusAngle;

    public BusObject( float busNumber, float busType, float busVoltage, float busAngle){
        mBusNumber = busNumber;
        mBusType = busType;
        mBusVoltage = busVoltage;
        mBusAngle = busAngle;
    }

    public float getBusNumber() {
        return (int)mBusNumber;
    }

    public String getBusType(){
        String mmBusType = null;
        switch ((int) mBusType){
            case 1:
                mmBusType = "Slack";
                break;
            case 2:
                mmBusType = "PQ";
                break;
            case 3:
                mmBusType = "PV";
        }
        return mmBusType;
    }

    public float getBusVoltage(){
        return mBusVoltage;
    }

    public float getBusAngle(){
        return mBusAngle;
    }
}
