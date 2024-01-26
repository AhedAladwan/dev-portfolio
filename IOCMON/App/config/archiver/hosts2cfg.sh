for i in $(grep -- -VME /exchange/system/hostsud/hosts_common |	\
	   grep -v not_installed|grep -v MRIDI-VME-BPM12|grep -v XTEST|\
	   awk '{sub("[.].*ch","",$2);print $2}')
do
	awk -vd=$i '{sub("#.*","");print d":"$0}' iocmoc_arch_cfg.txt 
done >G_IOCMON_MT.config
cp G_IOCMON_MT.config G_IOCMON_ST.config
regreplace -f "TIME\([ \t]*\)3600" "TIME\\160" G_IOCMON_ST.config
