cmake_minimum_required(VERSION 3.10)

project(DBusDemo)

include_directories(/usr/include/dbus-1.0)
include_directories(/usr/lib/x86_64-linux-gnu/dbus-1.0/include)
include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include)


add_executable(Send send_signal.c)
add_executable(Recv listen_signal.c)
target_link_libraries(Send dbus-1 dbus-glib-1)
target_link_libraries(Recv dbus-1 dbus-glib-1)

