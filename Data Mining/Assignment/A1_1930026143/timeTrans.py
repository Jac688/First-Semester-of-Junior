
def func(time1):
    if('P' in time1):
        spl = time1.split('P', 1)
        print(spl)
        spl2= spl[0].split(':', 1)
        print(spl2)
        hour = int(spl2[0]) + 12
        final_time= str(hour)+ ':'+ spl2[1]
        print(final_time)
        return final_time

time1 = '9:45PM'
func(time1)