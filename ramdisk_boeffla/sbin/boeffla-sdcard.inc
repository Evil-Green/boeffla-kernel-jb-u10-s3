# Change sd card read ahead buffer

# Initialize buffer variable and read tweak setting
BUFFER="256"
TWEAK=$(/sbin/busybox sed -n -e 's/.*sdcardtweaks=\(.*\)(.*/\1/p' $BOEFFLA_CONFIG)

if [ "${TWEAK:-0}" -ge 128 ] && [ "${TWEAK:-0}" -le 4096 ] ; then
	BUFFER=$TWEAK
fi

# Only change read ahead buffer if tweak is not switched off
if  [ ! "`/sbin/busybox grep sdcardtweaks=off $BOEFFLA_CONFIG`" ]; then
	echo $(( $BUFFER * 1)) > /sys/block/mmcblk0/bdi/read_ahead_kb
	echo $(( $BUFFER * 1)) > /sys/block/mmcblk1/bdi/read_ahead_kb
	echo $(date) "SDcard buffer tweaks ($BUFFER kb) applied" >> $BOEFFLA_LOGFILE
fi
