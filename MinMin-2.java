package org.cloudbus.cloudsim.examples;
//import java.text.DecimalFormat;
		import java.util.*;
		import java.util.Map.Entry;

		import org.cloudbus.cloudsim.Cloudlet;
		//import org.cloudbus.cloudsim.CloudletSchedulerTimeShared;
		import org.cloudbus.cloudsim.CloudletSchedulerSpaceShared;
		import org.cloudbus.cloudsim.Datacenter;
		import org.cloudbus.cloudsim.DatacenterBroker;
		import org.cloudbus.cloudsim.DatacenterCharacteristics;
		import org.cloudbus.cloudsim.Host;
		import org.cloudbus.cloudsim.Log;
		import org.cloudbus.cloudsim.Pe;
		import org.cloudbus.cloudsim.Storage;
		import org.cloudbus.cloudsim.UtilizationModel;
		import org.cloudbus.cloudsim.UtilizationModelFull;
		import org.cloudbus.cloudsim.Vm;
		import org.cloudbus.cloudsim.VmAllocationPolicySimple;
		import org.cloudbus.cloudsim.VmSchedulerTimeShared;
		//import org.cloudbus.cloudsim.VmSchedulerSpaceShared;
		import org.cloudbus.cloudsim.core.CloudSim;
		import org.cloudbus.cloudsim.provisioners.BwProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.PeProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.RamProvisionerSimple;


		public class MinMin{
			
			/*Global variables*/
			private static int num_vm=5,num_cloudlets=10;
			private static double FinalTime;
			private static List<Cloudlet> cloudletList; 
			//private static List<Cloudlet> sortedcloudletList;
			private static List <Cloudlet> sortList= new ArrayList<Cloudlet>();
			private static double resTime[]=new double[] {0,0,0,0,0,0,0,0,0,0};
			private static List<Vm> vmList;
			
			/* function to create vmlist*/
			
			private static List<Vm> createVM(int userId, int vms, int idShift) {
				//Creates a container to store VMs. This list is passed to the broker later
				LinkedList<Vm> list = new LinkedList<Vm>();
				//Random rand=new Random();
				//VM Parameters
				long size = 1000; //image size (MB) 
				int ram = 512; //vm memory (MB)
				int mips;
				long bw = 100;
				int pesNumber = 1; //number of cpus
				String vmm = "Xen"; //VMM name

				//create VMs
				Vm[] vm = new Vm[vms];

				for(int i=0;i<vms;i++){
					mips=100+(i*50); 
					vm[i] = new Vm(idShift + i, userId,mips , pesNumber, ram, bw, size, vmm, new CloudletSchedulerSpaceShared());
					list.add(vm[i]);
					System.out.println("");
					System.out.println("Vm"+i+"  mips:"+mips);
				}
				 
				return list; 
			} 

			/* function to create CloudletList */

			private static List<Cloudlet> createCloudlet(int userId, int cloudlets, int idShift){
				// Creates a container to store Cloudlets
				LinkedList<Cloudlet> list = new LinkedList<Cloudlet>();
				//Random rand=new Random();
				//cloudlet parameters
				
				long fileSize = 300;
				long outputSize = 300; 
				int pesNumber = 1;
				UtilizationModel utilizationModel = new UtilizationModelFull();

				Cloudlet[] cloudlet = new Cloudlet[cloudlets];
		 
				for(int i=0;i<cloudlets;i++){
					cloudlet[i] = new Cloudlet(idShift + i,4000+(i*1000), pesNumber, fileSize, outputSize, utilizationModel, utilizationModel, utilizationModel);
					// setting the owner of these Cloudlets
					cloudlet[i].setUserId(userId);
					list.add(cloudlet[i]);
				}

				return list;
			}
			
			/**
			 * execution starts here
			 **/
			
			public static void main(String[] args) {
				Log.printLine("Starting Min-Min Algorithm Simulation...");

				try {
					//Initialize the CloudSim package. 
					int num_user = 2;   // number of grid users
					Calendar calendar = Calendar.getInstance();
					boolean trace_flag = false;  // mean trace events

					// Initialize the CloudSim library
					CloudSim.init(num_user, calendar, trace_flag);

					//  Create Datacenters
					//Datacenters are the resource providers in CloudSim. We need atleast one of them to run a CloudSim simulation
					Datacenter datacenter0 = createDatacenter("Datacenter_0");
					//Datacenter datacenter1 = createDatacenter("Datacenter_1");
					
					//Create Broker   
					//Broker assigns cloudlets to vms and registers the vm in a datacenter
					DatacenterBroker broker = createBroker("Broker_0");
					int brokerId = broker.getId();

					//Create VMs and Cloudlets and send them to broker
					vmList = createVM(brokerId, num_vm, 0); //creating 5 vms
					cloudletList = createCloudlet(brokerId, num_cloudlets, 0); // creating 10 cloudlets
		            
					broker.submitVmList(vmList); 
					bindCloudletToVmsMinMin();

					broker.submitCloudletList(sortList);
					
					//Start the simulation
					
					CloudSim.startSimulation();
					//Log.printLine("Time: "+CloudSim.clock());
					//Print results when simulation is over
					
					List<Cloudlet> newList = broker.getCloudletReceivedList();
					
					//Stop the simulation			
					CloudSim.stopSimulation();
					double start=CloudSim.clock();
					//System.out.println("Start : "+start);
					//Log.printLine("Time: "+CloudSim.clock());
					printCloudletList(newList);
					
					//datacenter0.printDebts();
					//datacenter1.printDebts();
					System.out.println("");
					System.out.println("");
					System.out.println("");
					calculateThroughput(newList);
					calculateWaitingTime(newList);
					calculateResponseTime(newList);
					System.out.println("");
					Log.printLine("Min-Min Algorithm Simulation finished!");
				}
				catch (Exception e)
				{
					e.printStackTrace();
					Log.printLine("The simulation has been terminated due to an unexpected error");
				} 
			}

			private static Datacenter createDatacenter(String name){

				//create a list to store one or more Machines
				List<Host> hostList = new ArrayList<Host>();

				//A Machine contains one or more PEs(Processing elements) or CPUs/Cores. 
				//Therefore, should create a list to store these PEs before creating a Machine.
				List<Pe> peList1 = new ArrayList<Pe>();

				int mips = 10000;

				// Create PEs and add these into the list.
				//for a quad-core machine, a list of 4 PEs is required:
				peList1.add(new Pe(0, new PeProvisionerSimple(mips)));// need to store Pe id and MIPS Rating
				peList1.add(new Pe(1, new PeProvisionerSimple(mips)));
				peList1.add(new Pe(2, new PeProvisionerSimple(mips)));
				peList1.add(new Pe(3, new PeProvisionerSimple(mips)));

				//Another list, for a dual-core machine
				List<Pe> peList2 = new ArrayList<Pe>(); 

				peList2.add(new Pe(0, new PeProvisionerSimple(mips)));
				peList2.add(new Pe(1, new PeProvisionerSimple(mips)));

				//Create Hosts with its id and list of PEs and add them to the list of machines
				int hostId=0;
				int ram = 16384; //host memory (MB)
				long storage = 1000000; //host storage
				int bw = 100000;

				hostList.add(
		    			new Host(
		    				hostId,
		    				new RamProvisionerSimple(ram),
		    				new BwProvisionerSimple(bw),
		    				storage,
		    				peList1,
		    				new VmSchedulerTimeShared(peList1)
		    			)
		    		); // first machine

				hostId++;

				hostList.add(
		    			new Host(
		    				hostId,
		    				new RamProvisionerSimple(ram),
		    				new BwProvisionerSimple(bw),
		    				storage,
		    				peList2,
		    				new VmSchedulerTimeShared(peList2)
		    			)
		    		); // Second machine

				// Create a DatacenterCharacteristics object that stores the properties of a data center
				String arch = "x86";      // system architecture
				String os = "Linux";          // operating system
				String vmm = "Xen";
				
				double time_zone = 10.0;         // time zone this resource located
				double cost = 3.0;              // the cost of using processing in this resource
				double costPerMem = 0.05;		// the cost of using memory in this resource
				double costPerStorage = 0.1;	// the cost of using storage in this resource
				double costPerBw = 0.1;			// the cost of using bw in this resource
				LinkedList<Storage> storageList = new LinkedList<Storage>();	

				DatacenterCharacteristics characteristics = new DatacenterCharacteristics(
		                arch, os, vmm, hostList, time_zone, cost, costPerMem, costPerStorage, costPerBw);


				//create a PowerDatacenter object.
				Datacenter datacenter = null;
				try {
					datacenter = new Datacenter(name, characteristics, new VmAllocationPolicySimple(hostList), storageList, 0);
				} catch (Exception e) {
					e.printStackTrace();
				} 
				
				return datacenter;
			}

			private static DatacenterBroker createBroker(String name){

				DatacenterBroker broker = null;
				try {
					broker = new DatacenterBroker(name);
				} catch (Exception e) {
					e.printStackTrace();
					return null;
				}
				return broker;
			}

			/**
			 * Prints the Cloudlet objects
			 * @param list  list of Cloudlets
			 */
			private static void printCloudletList(List<Cloudlet> list) {
				int size = list.size();
				Cloudlet cloudlet = null;
				
				
				
				
				String indent = "   ";
				//String newline="\n";
				Log.printLine();
				Log.printLine("========== OUTPUT ==========");
				Log.printLine("Cloudlet ID" + indent+ indent + "STATUS" + indent + indent+
						"Data center ID" + indent + indent+ "VM ID" + indent + indent + "    "+"Time" + indent + indent+ indent+ indent +"Start Time" + indent + indent+ indent + indent+ "Finish Time");
			    String indent2="      ";
				for (int i = 0; i < size; i++) {
					cloudlet = list.get(i);
					System.out.printf(indent + cloudlet.getCloudletId() + indent + indent);
					
					if (cloudlet.getCloudletStatus() == Cloudlet.SUCCESS){
						System.out.printf(indent2+"SUCCESS");
						System.out.printf( indent + indent + indent+ cloudlet.getResourceId() + indent + indent + indent + indent+"   "+ cloudlet.getVmId()+ indent + indent+ indent+"  ");
						System.out.printf("%-22.5f",cloudlet.getActualCPUTime());
						System.out.printf("%-22.5f", cloudlet.getExecStartTime());
						System.out.printf("%-22.5f", cloudlet.getFinishTime());
						System.out.println("");

						
						resTime[cloudlet.getVmId()]+=cloudlet.getActualCPUTime();
						if(i==size-1)
						{
							FinalTime=cloudlet.getFinishTime();
						}
					}
				}
				System.out.println("");
				for(int k=0;k<5;k++) {
					resTime[k]=(resTime[k]/FinalTime)*100;
					System.out.println("% Resource Time for vm "+(k)+" : "+resTime[k]);
				}
				
				for (int a=0; a<size;a++)
		    		Log.printLine("Waiting Time for Task-" + list.get(a).getCloudletId() + "   =  " + list.get(a).getExecStartTime());

			}

		/* Min-Min algorithm */
			public static void bindCloudletToVmsMinMin() 
			{
				int cloudletNum = cloudletList.size();
				int vmNum = vmList.size();
			
				// ready time for each machine; initially to be 0
				Double[] readyTime = new Double[vmNum]; 
				for (int i = 0; i < readyTime.length; i++) {
					readyTime[i] = 0.0;
				}
			
				// initialize the 2-dimensional matrix with ready time + completion time
				List<List<Double>> tasksVmsMatrix = create2DMatrix(cloudletList, vmList);
			
				int count = 1;
			
				do {
					System.out.println("===========================");
					System.out.println("This is start of iteration " + count);
					print2DArrayList(tasksVmsMatrix);
					// find smallest in each row; and find the largest of all;
					Map<Integer[], Double> map = findMinMinTimeMap(tasksVmsMatrix);
					printMapForMinMin(map);
			
					//retrieve all the info from the map
					Integer[] rowAndColIndexAndCloudletId = getRowAndColIndexesAndCloudletId(map);
					Double Min = getMinimumTimeValue(map);
					int rowIndex = rowAndColIndexAndCloudletId[0];
					int columnIndex = rowAndColIndexAndCloudletId[1];
					int cloudletId = rowAndColIndexAndCloudletId[2]; 
					
					// assign the cloudlet to the vm
					cloudletList.get(cloudletId).setVmId(vmList.get(columnIndex).getId());
					System.out.printf("The cloudlet %d has been assigned to VM %d \n", cloudletId, columnIndex);
					
					//adding the cloudlet to sorted list
					Cloudlet cloudlet=cloudletList.get(cloudletId);
					sortList.add(cloudlet);
					
					// update ready time array;
					Double oldReadyTime = readyTime[columnIndex];
					readyTime[columnIndex] = Min;
					System.out.printf("The ready time array is %s \n", Arrays.toString(readyTime));
			
					// update the cloudlet-vm matrix with current ready time
					updateTotalTimeMatrix(columnIndex, oldReadyTime, readyTime, tasksVmsMatrix);
			
					// remove the row after the cloudlet has been assigned
					tasksVmsMatrix.remove(rowIndex);
			
					System.out.println("This is end of iteration " + count);
					System.out.println("===========================");
					++count;
				} while (tasksVmsMatrix.size() > 0); 
				calculateThroughputNew(readyTime, cloudletNum);
			}
			
			/* below are the helper functions for Min-Min */
			
			/*create a 2D matrix to represent task-vm relationship*/
			  /* row is cloudlet and column is vm, intersection cell is the expected*/
			private static List<List<Double>> create2DMatrix(List<Cloudlet> cloudletList,List<Vm> vmList)
			{
				List<List<Double>> table= new ArrayList<List<Double>>();
				for(int i=0;i<cloudletList.size();i++)
				{
					//original cloudlet id is added as last column
					Double originalCloudletId = (double) cloudletList.get(i).getCloudletId();
					//System.out.println("the original cloudlet id is:" + originalCloudletId);
					List<Double> temp=new ArrayList<Double>();
					
					for(int j=0;j<vmList.size();j++)
					{
						Double load=cloudletList.get(i).getCloudletLength()/vmList.get(j).getMips();
						temp.add(load);
					}
					temp.add(originalCloudletId); 
					table.add(temp);
				}
				return table;
			}

			/* iterate the matrix find min among min */
			private static Map<Integer[], Double> findMinMinTimeMap(List<List<Double>> tasksVmsMatrix)
			{
				// scan each row and find the minimum
				List<Integer[]> indexList= new ArrayList<Integer[]>();
			    int colNum = tasksVmsMatrix.get(0).size();
			    Integer initialCloudletId=tasksVmsMatrix.get(0).get(colNum-1).intValue();
			    Integer[] indexOfMin={0,0,initialCloudletId};
			    Double min=tasksVmsMatrix.get(0).get(0);
			    indexList.add(indexOfMin);
			    int rowNum=tasksVmsMatrix.size();
			    for(int row=0;row<rowNum;row++){
			        int colNumWithOutLastColumn =tasksVmsMatrix.get(row).size()-1;
			        for (int col=0;col<colNumWithOutLastColumn;col++){
			            Double current=tasksVmsMatrix.get(row).get(col);
			            if(current<min){
			                min=current;
			                Integer targetCloudletId=(tasksVmsMatrix.get(row).get(colNumWithOutLastColumn)).intValue();
			                Integer[] indexOfCurrent = {row,col,targetCloudletId};
			                indexList.add(indexOfCurrent);

			            }
			        }
			    }
			    Map<Integer[],Double> map=new HashMap<Integer[],Double>();
			    Integer[] rowAndColIndexAndCloudletId = new Integer[3];
			    rowAndColIndexAndCloudletId[0]=indexList.get(indexList.size()-1)[0];
			    rowAndColIndexAndCloudletId[1]=indexList.get(indexList.size()-1)[1];
			    rowAndColIndexAndCloudletId[2]=indexList.get(indexList.size()-1)[2];
			    map.put(rowAndColIndexAndCloudletId,min);
			    return map;
			}
			
			@SuppressWarnings("unchecked")
			public static <T extends Cloudlet> List<T> getSortList() {
				return (List<T>) sortList;
			}
			
			@SuppressWarnings({ "rawtypes", "unchecked" })
			private static HashMap<Integer[], Double> sortMapByValue(Map<Integer[], Double> map)
			{
				Set<Entry<Integer[], Double>> set = map.entrySet();
				List<Entry<Integer[], Double>> list = new ArrayList<Entry<Integer[], Double>>(set);
			
				Collections.sort(list, new Comparator<Map.Entry<Integer[], Double>>() {
					public int compare(Map.Entry<Integer[], Double> o1, Map.Entry<Integer[], Double> o2) {
						return (o2.getValue()).compareTo(o1.getValue());
					}
				});
			
				// copying the sorted list in HashMap
				// using LinkedHashMap to preserve the insertion order
				HashMap sortedHashMap = new LinkedHashMap();
				for (Iterator it = list.iterator(); it.hasNext();) {
					Map.Entry entry = (Map.Entry) it.next();
					sortedHashMap.put(entry.getKey(), entry.getValue());
				}
				return sortedHashMap;
			}
			/*return the only one key from this map=>{row,column,cloudlet id} */
			private static Integer[] getRowAndColIndexesAndCloudletId(Map<Integer[],Double> map)
			{
				Integer[] key=new Integer[3];
				for(Entry<Integer[],Double> entry: map.entrySet())
				{
					key=entry.getKey();
				}
				return key; 
			}
			/*return the only one value from this map =>minimum of expected completion */
			 private static Double getMinimumTimeValue(Map<Integer[],Double> map)
			 {
				 Double value=0.0;
				 for(Entry<Integer[],Double> entry: map.entrySet())
				 {
					 value=entry.getValue();
				 }
				 return value;
			 }
			 
			 /*update the expected completion time */
			 
			 private static void updateTotalTimeMatrix(int columnIndex,Double oldReadyTime,Double[] readyTime,List<List<Double>> taskVmsMatrix)
			 {
				 //by adding current ready time to old corresponding expected completion time
				 Double newReadyTime =readyTime[columnIndex];
				 Double readyTimeDifference =newReadyTime- oldReadyTime;
				 for(int row=0;row<taskVmsMatrix.size();row++)
				 {
					 Double oldTotalTime=taskVmsMatrix.get(row).get(columnIndex);
					 Double newTotalTime=oldTotalTime+readyTimeDifference;
					 taskVmsMatrix.get(row).set(columnIndex,newTotalTime);
				 }
			 }
			 
			 /* print current cloudlet vs vm matrix */ 
			 
			 private static void print2DArrayList(List<List<Double>> table)
			 {
				 String indent="           ";
				 System.out.println("The current required exceution time matirx is as below,with size of "+ table.size()+" by "+table.get(0).size());
				 //System.out.printf(indent);
				 for(int j=0;j<num_vm;j++)
				 {
					 System.out.printf("    Vm"+j+indent);
				 }
				 System.out.println("cloudletNum");
				 for(int i=0;i<table.size();i++)
				 {
			 		//System.out.printf(indent);
			 		 String indent2="   "; 
					 for(int j=0;j<table.get(i).size();j++)
					 {
						 System.out.printf("%-15.5f", table.get(i).get(j));
						 System.out.printf(indent2);
					 }
					 System.out.printf("\n");
				 }
				 
			 }
			 
			 /* print selected cloudlet-vm pair */ 
			 
			private static void printMapForMinMin(Map<Integer[], Double> map) {
				for (Entry<Integer[], Double> entry : map.entrySet()) {
			        Integer[] key = entry.getKey();
			        Double value = entry.getValue();
			        System.out.println("The keys are: " + "{" + key[0] + ", " + key[1] + ", " + key[2] + "}");
			        System.out.println("The min is " + value + ", located at row " + key[0] + " column " + key[1] + " and the cloudlet id is " + key[2]);
			    }
			}
			
			/* get the first pair of map */
			
			private static Map<Integer[], Double> getFirstPairFromMap(Map<Integer[], Double> map) {
				Map.Entry<Integer[], Double> entry = map.entrySet().iterator().next();
				Integer[] key = entry.getKey();
				Double value = entry.getValue();
				Map<Integer[], Double> firstPair = new HashMap<Integer[], Double>();
				firstPair.put(key, value);
				return firstPair;
			}
			
			/* calculate average turn-around time */
			
			public double calculateAvgTurnAroundTime(List<? extends Cloudlet> cloudletList)
			{
				double totalTime=0.0;
				int cloudletNum=cloudletList.size();
				for(int i=0;i<cloudletNum;i++)
				{
					totalTime+=cloudletList.get(i).getFinishTime();
					
				}
				double averageTurnAroundTime=totalTime/cloudletNum;
				System.out.printf("The average turnaround time is %.4f\n",averageTurnAroundTime);
				return averageTurnAroundTime;
			} 
			 
			/* calculate throughput */
			
			public static double calculateThroughput(List<? extends Cloudlet> cloudletList)
			{
				double maxFinishTime=0.0;
				int cloudletNum=cloudletList.size();
				for(int i=0;i<cloudletNum;i++) 
				{
					double currentFinishTime=cloudletList.get(i).getFinishTime();
					if(currentFinishTime>maxFinishTime)
						maxFinishTime=currentFinishTime;
				}
				double throughput=cloudletNum/maxFinishTime;
				System.out.printf("The throughput is %.6f\n",throughput);
				return throughput;
			}
			
			/* calculate average throughput */
			
			public static double calculateThroughputNew(Double[] readyTime, int cloudletNum) {
				List<Double> temp = new ArrayList<Double>(Arrays.asList(readyTime));
				Double throughput = cloudletNum / (Collections.max(temp) + 0.1);
				System.out.printf("The throughput is %.6f \n", throughput);
				return throughput;
			}
			public static double calculateWaitingTime(List<Cloudlet> list) {
				double TotalWaitTime=0.0;
				int size = list.size();
				Cloudlet cloudlet;
				for(int i=0;i<size;i++)
				{
					cloudlet = list.get(i);
					double indiWaitTime=cloudlet.getExecStartTime()-cloudlet.getSubmissionTime();
					TotalWaitTime=TotalWaitTime+indiWaitTime;
				}
				double avgWaitTime=TotalWaitTime/size;
				System.out.printf("The avg Waiting time is is %.6f\n",avgWaitTime);
				return avgWaitTime;

			}
			public static double calculateResponseTime(List<Cloudlet> list) {
				double TotalResponseTime=0.0;
				int size = list.size();
				Cloudlet cloudlet;
				for(int i=0;i<size/2;i++)
				{
					cloudlet = list.get(i);
					double indiResponseTime=cloudlet.getFinishTime()-cloudlet.getSubmissionTime();
					System.out.println("The response time for Vm " + (i) + " is: " + indiResponseTime);
					TotalResponseTime=TotalResponseTime+indiResponseTime;
				}
				double avgResTime=TotalResponseTime/size;
				System.out.printf("The avg response time is is %.6f\n",avgResTime);
				return avgResTime;

			}
		}