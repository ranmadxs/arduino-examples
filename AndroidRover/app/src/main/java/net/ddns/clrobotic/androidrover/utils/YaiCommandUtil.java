package net.ddns.clrobotic.androidrover.utils;

import net.ddns.clrobotic.androidrover.YaiCmd;

/**
 * Created by esanchez on 30-05-2017.
 */

public class YaiCommandUtil {

    private static final String IP_YAI_ROVER = "192.168.0.22";
    private static final String TIPO_CALL = "SERIAL";

    public static String getUri(YaiCmd yaiCmd){
        String url = "http://"+IP_YAI_ROVER+"/cmd?TIPO_CALL="+TIPO_CALL+"&COMMAND="+yaiCmd.getCommand()
                +"&P1="+yaiCmd.getP1()+"&P2="+yaiCmd.getP2()+"&P3="+yaiCmd.getP3()+"&P4="+yaiCmd.getP4()
                +"&P5="+yaiCmd.getP5()+"&P6="+yaiCmd.getP6()+"&P7="+yaiCmd.getP7();
        return url;
    }
}
