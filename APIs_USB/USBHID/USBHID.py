from pywinusb import hid

# Whenever the host computer receives data from the
# Mbed board, the received data is printed
def on_data(data):
    print(f"Got message {data}")

'''
Gets all HIDs currently connected to host computer,
and sets the first device with string "mbed" in its
vendor name equal to variable mbed. This variable
will be used to send data to the Mbed board.
'''
all_hid_devices = hid.find_all_hid_devices()
mbed_devices = [d for d in all_hid_devices if "mbed" in d.vendor_name]

if mbed_devices is None:
    raise ValueError("No HID devices found")

# A buffer of bytes representing the values 1-8
# The first byte is the report ID which must be 0
buffer = [0, 1, 2, 3, 4, 5, 6, 7, 8]

mbed_devices[0].open()
# Set custom raw data handler
mbed_devices[0].set_raw_data_handler(on_data)

# Send the message to the Mbed board
out_report = mbed_devices[0].find_output_reports()
out_report[0].set_raw_data(buffer)
out_report[0].send()
