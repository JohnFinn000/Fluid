
gprof -l | head -n 12 | tail -n 7 | awk '{ print $3," ",$7 }' 
