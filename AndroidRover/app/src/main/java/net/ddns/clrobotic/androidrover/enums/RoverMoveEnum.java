package net.ddns.clrobotic.androidrover.enums;

/**
 * Created by instala on 30-05-2017.
 */

public enum RoverMoveEnum {

    ROVER_BODY_MOVE_TYPE_LEFT          ("10001"),
    ROVER_BODY_MOVE_TYPE_RIGHT         ("10002"),
    ROVER_BODY_MOVE_TYPE_FORWARD       ("10003"),
    ROVER_BODY_MOVE_TYPE_BACK          ("10004"),
            ;

    private final String codigo;

    RoverMoveEnum(String codigo) {
        this.codigo = codigo;
    }

    public String getCodigo() {
        return this.codigo;
    }
}
