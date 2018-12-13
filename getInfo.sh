temp=$(wc -l temp.txt | cut -f 1 -d " ")
light=$(wc -l light.txt | cut -f 1 -d " ")
var=1
#while [ $temp -eq $(wc -l temp.txt | cut -f 1 -d ' ') -o $var -eq 5 ]
#do
	mosquitto_pub -t command -m "light"
	#add checks to see if it appended anything at the end
	sleep 5
	mosquitto_pub -t command -m "temp"
	sleep 5
#	var=$((var+1))
#done

