ls TC2xx/ | grep 'Infineon' | sed s/'Infineon-AURIX_'/''/g | sed s/'_'/' '/g | sed s/'-v[0-9 ]*-EN'/''/g | sed s/'.pdf'/''/g | sed s/'-Training'/''/g > TC2xx/all.txt 

echo "Things that might be missing in TC2xx"
while read line
do
	x=$(grep "$line" TC2xx/all.txt)
	if test -z "$x"
	then
		echo -e '\tE:' "$line" cannot be matched
	else
		tmp=$(echo $line | sed s/' '/'_'/g)
		name=$(ls TC2xx | grep $tmp)
		#echo $line matches with $name
	fi	
done < TC2xx.txt



ls TC3xx/ | grep 'Infineon' | sed s/'Infineon-AURIX_'/''/g | sed s/'_'/' '/g | sed s/'-v[0-9 ]*-EN'/''/g | sed s/'.pdf'/''/g | sed s/'-Training'/''/g > TC3xx/all.txt 

echo -e "\nThings that might be missing in TC3xx:"
while read line
do
	x=$(grep "$line" TC3xx/all.txt)
	if test -z "$x"
	then
		echo -e '\tE:' "$line" cannot be matched
	else
		tmp=$(echo $line | sed s/' '/'_'/g)
		name=$(ls TC3xx | grep $tmp)
		#echo $line matches with $name
	fi
done < TC3xx.txt

echo "TC2xx.txt is suggesting "$(cat TC2xx.txt | wc -l)" and you have downloaded "$(ls TC2xx | grep Infineon | wc -l)

echo "TC3xx.txt is suggesting "$(cat TC3xx.txt | wc -l)" and you have downloaded "$(ls TC3xx | grep Infineon | wc -l)

