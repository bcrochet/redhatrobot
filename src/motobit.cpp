#include <cmath>
#include <mbed.h>

namespace motobit {
    enum class Motor {
        Left = 8448,
        Right = 8192
    };

    enum class MotorDirection {
        Forward = 0,
        Reverse = 1
    };

    enum class MotorPower {
        On = 28673,
        Off = 28672
    };

    void setMotorSpeed(Motor motor, MotorDirection direction, int speed) {
        int pwr = 0;
        speed = std::abs(speed);

        if (speed > 100) {
            speed = 100;
        }

        if (direction == motobit::MotorDirection::Forward) {
            pwr = 0 + (127 - 100) * ((speed - 0) / (127 - 100));
            pwr = 128 + pwr;
        } else {
            pwr = 0 + (127 - 100) * ((speed - 0) / (127 - 100));
        }

        char cmd[2];
        cmd[0] = (char)motor;
        cmd[1] = pwr;
        I2C i2c(I2C_SDA0, I2C_SCL0);
        i2c.write(89, cmd, 2);
    }

    void enable(MotorPower command) {
        I2C i2c(I2C_SDA0, I2C_SCL0);
        char cmd[1];
        cmd[0] = (char)command;
        i2c.write(89, cmd, 1);
    }

    void invert(Motor motor, bool invert) {
        int temp_number = invert ? 1 : 0;
        if (motor == motobit::Motor::Right) {
            temp_number += 4608;
        } else {
            temp_number += 4864;
        }
        I2C i2c(I2C_SDA0, I2C_SCL0);
        char cmd[1];
        cmd[0] = (char)temp_number;
        i2c.write(89, cmd, 1);
    }
}