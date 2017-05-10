#include <SPI.h>
#include <SD.h>

File root;
File folderLogs;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  folderLogs = SD.open("/logs");

  int totalFiles = countFilesInDirectory(folderLogs);
  Serial.println("Total Files :: "+ String (totalFiles));
  totalFiles++;
  String newFileName = "F"+getNewLogFileName(totalFiles, 7)+".LOG";
  File myFile = SD.open(newFileName, FILE_WRITE);
  if (myFile) {
	  Serial.println("Se ha creado el nuevo archivo " + myFile);
	  myFile.print("Tiempo(ms)=");
	  myFile.println(String(millis()));
	  myFile.close();
  }else{
	  Serial.println("NO se ha creado el nuevo archivo " + myFile);
  }

  folderLogs.close();
  root.close();
  Serial.println("done!");



}

void loop() {
  // nothing happens after setup finishes.
}

String getNewLogFileName(int index, int ceros){
	String res = String(index);
	int totalCeros = ceros - (index % 10);
	for (int j = 0; j < totalCeros; j++){
		res =  "0" + res;
	}
	return res;
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

int countFilesInDirectory(File dir) {
  int count = 0;
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    Serial.print(entry.name());
    if (!entry.isDirectory()) {
      count++;
    }
    entry.close();
  }
  return count;
}

