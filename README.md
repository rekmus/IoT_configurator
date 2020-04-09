This is a self-contained web application allowing browser access to your IoT device.

It stores configuration in a single JSON file.

It should take about 7 MB of the memory space and less than 0.1% of the CPU time.

Authentication is based on clear-text password stored in a configuration file. User name is not checked, however you can easily add the check in do_login().

Random, at least 8 character long password should be generated for each device and written into initial configuration.
