package net.ddns.clrobotic.androidrover.enums;

/**
 * Created by instala on 30-05-2017.
 */

public enum CommandEnum {

    ROVER_MOVE_MANUAL_BODY          ("100001"),
    ROVER_STOP                      ("100002"),
    LASER_ACTION                    ("100004"),
    ;

    private final String codigo;

    CommandEnum(String codigo) {
        this.codigo = codigo;
    }

    public String getCodigo() {
        return this.codigo;
    }

}
