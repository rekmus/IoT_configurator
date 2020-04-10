This is a self-contained web application allowing browser access to your IoT device.

It stores configuration in a single JSON file. Its path is in `silgy_app.h`.

It should take about 9 MB of memory and less than 0.1% of the CPU time.

Settings list is defined in `M_settings` array at the top of `silgy_app.cpp`.

Authentication is based on clear-text password stored in a configuration file. User name is not checked, however you can easily add the check in `do_login()`.

Random, at least 8 character long password should be generated for each device and written into initial configuration.
