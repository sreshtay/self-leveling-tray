import serial, struct, time

PORT = "/dev/tty.usbserial-1120" 
kobuki = serial.Serial(PORT, 115200)

def drive(speed_mm_s, radius_mm):
    payload = bytes([0x01, 0x04]) + struct.pack("<hh", speed_mm_s, radius_mm)
    body = bytes([len(payload)]) + payload
    checksum = 0
    for b in body:
        checksum ^= b
    kobuki.write(bytes([0xAA, 0x55]) + body + bytes([checksum]))

def run(speed, radius, seconds):
    end = time.time() + seconds
    while time.time() < end:      # keep resending
        drive(speed, radius)
        time.sleep(0.1)

run(100, 0, 1)    # forward at 100 mm/s for 1 second
run(100, 1, 1)    # spin in place for 1 second
run(0, 0, 0.5)    # stop