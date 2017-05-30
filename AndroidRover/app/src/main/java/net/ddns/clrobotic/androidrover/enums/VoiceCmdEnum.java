package net.ddns.clrobotic.androidrover.enums;

/**
 * Created by instala on 30-05-2017.
 */

public enum VoiceCmdEnum {

    LASER                        ("LASER"),
    ROVER_STOP                   ("STOP, DETENERSE, ALTO"),
    ROVER_LEFT                   ("LEFT, IZQUIERDA"),
    ROVER_RIGHT                  ("RIGHT, DERECHA"),
    ROVER_FORWARD                ("FORWARD, ADELANTE"),
    ROVER_BACK                   ("BACK, ATRAS"),
            ;

    private final String codigo;

    VoiceCmdEnum(String codigo) {
        this.codigo = codigo;
    }

    public String getCodigo() {
        return this.codigo;
    }
}
