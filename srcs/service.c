const char *durex_service = "#!/bin/sh\n\
\n\
### BEGIN INIT INFO\n\
# Provides:          durex\n\
# Required-Start:    $local_fs $network $syslog\n\
# Required-Stop:     $local_fs $network $syslog\n\
# Default-Start:     2 3 4 5\n\
# Default-Stop:      0 1 6\n\
# Short-Description: Durex\n\
# Description:       Durex - Debian\n\
### END INIT INFO\n\
\n\
NAME=\"Durex\"\n\
PATH=\"/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin\"\n\
APPDIR=\"/\"\n\
APPBIN=\"/bin/Durex\"\n\
APPARGS=\"\"\n\
USER=\"root\"\n\
GROUP=\"root\"\n\
\n\
# Include functions\n\
set -e\n\
. /lib/lsb/init-functions\n\
\n\
start() {\n\
	start-stop-daemon --start --chuid \"$USER:$GROUP\" --background --chdir \"$APPDIR\" --exec \"$APPBIN\" -- $APPARGS || true\n\
}\n\
\n\
status() {\n\
	status_of_proc $NAME $NAME && exit 0 || exit $?\n\
}\n\
\n\
case \"$1\" in\n\
	start)\n\
		start\n\
		;;\n\
	status)\n\
		status\n\
		;;\n\
	*)\n\
		exit 1\n\
		;;\n\
esac\n\
\n\
exit 0";
