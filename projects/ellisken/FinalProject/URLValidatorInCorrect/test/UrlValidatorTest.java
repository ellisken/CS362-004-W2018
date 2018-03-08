

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!
public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

	private boolean compareResult(String url, boolean expected, boolean result){
        if (result == expected) {
			System.out.println(url + " resulted in " + result);
			return true;
        }
		System.out.println("UNEXPECTED: " + url + " resulted in " + result);
		return false;
	}

   //Manual tests of isValid() method
   public void testManualTest_1()
   {
       int passed = 0; //Used to indicate all tests passed
       //UrlValidatorTest testObj = new UrlValidatorTest("url test");
       UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

       //Print title
       System.out.println("\n-----MANUAL TESTS-----\n");

       //1. Test valid url Scheme + Auth
       String url = "http://www.google.com";
       boolean result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //2. Test same valid Scheme + different valid Auth
       url = "http://go.au";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //3. Test valid Scheme +  valid Auth + valid Port
       url = "http://www.google.com:0";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //4. Test valid Scheme +  valid Auth + valid Path
       url = "http://www.google.com/test123";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //5. Test valid Scheme +  valid Auth + valid Query
       url = "http://www.google.com?action=view";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //6. Test invalid Scheme + valid Auth
       url = "3ht://www.google.com";
       result = urlVal.isValid(url);
       if (compareResult(url, false, result)) {
           passed++;
       }

       //7. Test invalid Scheme + invalid Auth
       url = "3ht://1.2.3.4.5";
       result = urlVal.isValid(url);
       if (compareResult(url, false, result)) {
           passed++;
       }

       //8. Test another valid Scheme + valid Auth
       url = "ftp://go.au";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //9. No port, yes path and query
       url = "http://www.google.com/test1/?action=true";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //10. Yes port, no path, yes query
       url = "http://www.google.com:80?action=true";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       }

       //Yes port, yes path, no query
       url = "http://www.google.com:80/test1";
       result = urlVal.isValid(url);
       if (compareResult(url, true, result)) {
           passed++;
       
       }
       //Boundary: non-ascii, 
       //empty scheme
       //empty auth

       //Check ending value of passed
       assertEquals(passed, 8);
	 
	   
   }
   
   /*Tests Partitions determined as follows:
    * The space is partitioned by all possible binary combinations of 
    * parts {Scheme, Authority, Port, Path, Query}, i.e., 2^5 total
    * partitions. For example, the partition '11111' consists of all URLs
    * whose Scheme, Authority, Port, Path, and Query are valid.*/
   public void testPartitions()
   {   
	   //Create UrlValidator Object
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   String binCombo;
	   boolean expected;
	   boolean actual;
	   int validPart, invalidPart; //Used for indexing into URL part arrays
	   validPart = 0;
	   invalidPart = 1;
	   
	   //Print title
	   System.out.println("\n-----PARTITION TESTS-----\n");

	   //For each binary number between 0-31, padded with zeroes
	   for(int x=0; x < 32; x++){
		   StringBuilder testUrl = new StringBuilder();
		   //Get binary string representing the parts combination
		   //And guarantee 5 bits
		   binCombo = Integer.toBinaryString(x);
		   if(binCombo.length() < 5)
			   binCombo = String.format("%05d", Integer.parseInt(binCombo));
		   
		   //calculate expected result (if sum of digits != 0, then false, else true)
		   expected = !(binCombo.indexOf('0') >= 1);
		
		   //Construct a URL:
		   //for each index (0-4) in the bin number string
		   for(int j=0; j < 5; j++) {
		   		//If string[index] == 0
		   		//Grab valid part from testUrlParts[index] and append to url string
			    ResultPair[] currentPartArray = (ResultPair[]) testUrlParts[j];
			    if(binCombo.charAt(j) == '1')
				   testUrl.append(currentPartArray[validPart].item);
		   		//Else grab an invalid part and append to string
			   else testUrl.append(currentPartArray[invalidPart].item);
		   }
		   	//Test isValid() and compare to expected
	   		//Print results to console
		   	String url = testUrl.toString();
		   	actual = urlVal.isValid(url);
		   	System.out.println("Combination tested: " + binCombo);
		   	System.out.println("URL generated from combination: " + url);
		   	System.out.println("Expected: " + expected);
		   	System.out.println("Actual: " + actual);
		   	System.out.print('\n');
	   }
   }
   

   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   
   
   /*Data declarations for Partition and Programmatic tests
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] testUrlScheme = {
		   new ResultPair("http://", true),
		   new ResultPair("http/", false)};

   ResultPair[] testUrlAuthority = {
		   new ResultPair("go.com", true),
		   new ResultPair("1.2.3", false)};
   
   ResultPair[] testUrlPort = {
		   new ResultPair(":80", true),
		   new ResultPair(":-1", false)};
                            
   ResultPair[] testPath = {
		   new ResultPair("/test1", true),
		   new ResultPair("/..//file", false)};
   
   ResultPair[] testUrlQuery = {
		   new ResultPair("?action=view", true),
		   new ResultPair("?action=??=&view&?", false)};

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};


}


