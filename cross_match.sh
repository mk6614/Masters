##cat TC2xx | tr -s ' ' | sed s/'AURIX™ '//g


echo 'The following can be found in both TC2xx and TC3xx:' > eqs
echo 'The following in TC2xx can not be found in TC3xx:' > diffs
echo 'The following in TC2xx have changed in TC3xx:' > changed
while read line
do
	l=$(echo $line | strings | grep -io -f TC3xx.txt)
	if test -n "$l" 
	then
		if test "$l" = "$line"
		then
			echo -e '\t'$line >> eqs
		else 
			echo -e '('$line') has changed:\n\t'"$l" >> changed
		fi
	else
		echo -e '\t'$line >> diffs
	fi
done < TC2xx.txt


echo -e '\nThe following in TC3xx can not be found in TC2xx:' >> diffs
echo -e '\nThe following in TC3xx have changed in TC2xx:' >> changed
while read line
do 
	l=$(echo $line | strings | grep -io -f TC2xx.txt)
	if test -n "$l"
	then
		if test "$l" = "$line"
		then
			#echo -e '('$line') found:\n\t'"$l" >> eqs
			echo -n ''
		else 
			echo -e '('$line') has changed:\n\t'"$l" >> changed
		fi
	else
		echo -e '\t'$line >> diffs
	fi
done < TC3xx.txt


