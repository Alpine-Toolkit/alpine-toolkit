####################################################################################################
#
# Setup a Remote AVD
#

# Launch avd on remote
# emulator -avd Nexus_5x_API_23

REMOTE=192.168.10.1
PORT1=5554
PORT2=5555

# Forward local ports to remote ports
# -N  Do not execute a remote command.
# -L local_port:host:host_port
# ask password !
ssh -N -L ${PORT1}:localhost:${PORT1} -L ${PORT2}:localhost:${PORT2} ${REMOTE} &

adb kill-server # to restart server
adb devices -l
