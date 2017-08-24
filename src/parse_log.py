import csv
import glob
import os
import threading
import os

cwd = os.getcwd()
dir_path = os.path.dirname(os.path.realpath(__file__))
#full 15 dos attributes

def extract_average_log(parser_output_dir,rule_dir):
    list_of_files = glob.glob(parser_output_dir+'conn*.csv')
    latest_file = max(list_of_files, key=os.path.getctime)
    filename=os.path.basename(latest_file)
    with open(latest_file) as csvfile:
        with open(rule_dir+os.path.splitext(filename)[0]+'.rules','w') as outputfile:
            readCSV = csv.reader(csvfile)
            normal_count = 0
            total_record = 0
            for row in readCSV:
                sub_array = []
                a = ','.join(row)        
                for i in a.split(','):
                    if i == '-':
                        sub_array.append('0')
                    else:    
                        sub_array.append(i) 
                if sub_array[-1] == "1" and sub_array[2] == "tcp":
                    normal_count = normal_count+int(sub_array[7])
                    total_record = total_record + 1
            outputfile.write('alert tcp any any -> $HOME_NET any (msg:"TCP SYN flood attack detected"; flags:S; threshold: type threshold, track by_dst, count '+str(normal_count/total_record)+' , seconds 2; sid: 5000001; rev:1;)')
            print 'threshold is '+str(normal_count/total_record)

            
def parse_log(log_dir,parser_output_dir):
    # threading.Timer(5.0, parse_log).start()
    list_of_files = glob.glob(log_dir+'conn*.log') # * means all if need specific format then *.csv
    latest_file = max(list_of_files, key=os.path.getctime)
    filename=os.path.basename(latest_file)
    
    output_file = parser_output_dir+os.path.splitext(filename)[0]+'.csv'
    
    
    with open(latest_file) as csvfile:
        
        
        with open(output_file,'w') as outputfile:
            readCSV = csv.reader(csvfile)
            list_syn_error = ["RSTOS0", "RSTRH", "SH", "SHR", "OTH"]
            all_log = []
            count = 0
            index = 0
            check_index = 0
            for row in readCSV:
                count_time = 0
                count_serror = 0
                count_rerror = 0
                dst_host_srv_serror_count = 0
                count_diff_srv_count = 0
                dst_host_count = 0
                dst_host_srv_count = 0
                count = count+1
                if count >= 9 :
                    sub_array = []
                    a = ''.join(row)        
                    for i in a.split():
                        if i == '-':
                            sub_array.append('0')
                        else:    
                            sub_array.append(i)
                    if len(sub_array) > 6:
                        all_log.append(sub_array)
                        check_index = index-1
                        if check_index > -1:               
                            while True:
                                if check_index > -1:
                                     
                                    time = float(all_log[index][0]) - float(all_log[check_index][0])
                                    setip1 = set(all_log[check_index][2].split(' '))
                                    setip11 =  set(all_log[index][2].split(' '))
                                    setip2 = set(all_log[check_index][4].split(' '))
                                    setip21 =  set(all_log[index][4].split(' '))              
                                if time > float(60) or check_index < 0:
                                    break  
                                if setip1 == setip11 and setip2 == setip21:
                                    if all_log[check_index][11] in list_syn_error:
                                        count_serror = count_serror + 1
                                    if all_log[check_index][11] == "REJ":
                                        count_rerror = count_rerror + 1
                                    if all_log[check_index][5] != all_log[index][5]:
                                        count_diff_srv_count = count_diff_srv_count + 1        
                                    count_time = count_time+1                                  
                                check_index = check_index -1
                        check_index = index-1
                        if check_index > -1:
                            i = 0
                            while (i < 100):
                                if check_index < 0:
                                    break  
                                if check_index > -1:
                                    srv1 = all_log[check_index][5]
                                    srv2 = all_log[index][5]
                                    setip2 = set(all_log[check_index][4].split(' '))
                                    setip21 =  set(all_log[index][4].split(' '))
                                if setip2 == setip21:
                                    dst_host_count = dst_host_count + 1
                                if setip2 == setip21 and srv1 == srv2:
                                    if all_log[check_index][11] in list_syn_error:
                                       dst_host_srv_serror_count = dst_host_srv_serror_count+1      
                                    dst_host_srv_count =  dst_host_srv_count +1
                                i = i+1  
                                check_index = check_index - 1
                    if  dst_host_srv_count != 0:
                        host_same_srv_rate = dst_host_srv_count*100/dst_host_count
                        host_diff_srv_rate = 100 - host_same_srv_rate             
                    else:
                        host_same_srv_rate = 0
                        host_diff_srv_rate = 100 - host_same_srv_rate
                    if count_serror != 0:
                        serror_rate = count_serror*100/count_time
                    else:
                        serror_rate = 0
                    if count_rerror != 0:
                        rerror_rate = count_rerror*100/count_time
                    else:
                        rerror_rate = 0
                    if count_diff_srv_count != 0:
                        diff_srv_rate = count_diff_srv_count*100/count_time
                    else:
                        diff_srv_rate = 0
                    if dst_host_srv_serror_count != 0:
                        dst_host_srv_serror_rate = dst_host_srv_serror_count*100/dst_host_srv_count
                    else:
                        dst_host_srv_serror_rate = 0                                                                   
                    index = index + 1      
                    if len(sub_array) > 6:
                        outputfile.write(sub_array[0]+","+sub_array[8]+","+sub_array[6] + ","+sub_array[5]+"," +sub_array[11] + ","+sub_array[9]+","+sub_array[10]+","+str(count_time)+","+str(serror_rate)+","+str(rerror_rate)+","+str(diff_srv_rate)+","+str(dst_host_count)+","+str(dst_host_srv_count)+","+str(host_same_srv_rate)+","+str(host_diff_srv_rate)+","+str(dst_host_srv_serror_rate)+"\n")
    return output_file
