while read line
do

	tmp1=$(echo $line | sed s/' '/'_'/g)
	name1=$(ls TC2xx | grep $tmp1'-Training')
	tmp2=$(echo $line | sed s/' '/'_'/g)
	name2=$(ls TC3xx | grep $tmp2'-Training')
	if test -n "$name1" 
	then
		#echo $line matched with $name1
		if test -n "$name2" 
		then
			#echo $line matched with $name2
			echo Changes in $line:
			pdftotext TC2xx/"$name1" a.txt
			pdftotext TC3xx/"$name2" b.txt
			grep -v -F -x -f a.txt b.txt
			rm a.txt
			rm b.txt
			echo 
		else
			echo -e "\tE"  Could not match $line with a pdf in TC3xx
		fi 
	else
			echo -e "\tE" Could not match $line with a pdf in TC2xx
	fi
done < eqs

exit 3

#	pdftotext TC2xx/"$line".pdf
#	pdftotext TC3xx/"$line".pdf
#	grep -v -F -x -f TC3xx/"$line".txt TC2xx/"$line".txt



