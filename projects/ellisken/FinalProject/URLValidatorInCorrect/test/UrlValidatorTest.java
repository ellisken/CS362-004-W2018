

import java.util.Objects;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!
public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   /*compareResult() is used in our manual tests
    * to print each test's results to the console
    * Inputs: int test_num - the current test's number, boolean expected - the
    * expected isValid() return based on input, boolean result - the actual return
    * value of isValid() for that test*/
   private boolean compareResult(int test_num, String url, boolean expected, boolean result){
        if (result == expected) {
			System.out.println("Test " + test_num + ": " + url + " resulted in " + result);
			return true;
        }
		System.out.println("Test " + test_num + " UNEXPECTED: " + url + " resulted in " + result);
		return false;
	}
	
   
   
   /*isolateParTest() is used on our last test where urls are auto-generated.
    * Inputs: String url_fragment - a valid url fragment that will be appended
    * to all items in the array for the isolated part, ResultPair[] test_parts - 
    * the array that contains test values for the isolated part, String part - the
    * name of the current part under test*/
   private void isolatePartTest(String url_fragment, ResultPair[] test_parts, String part) {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   boolean expected;
	   boolean actual;
	   String url;
	   int test_ct;
	   int fail_ct;
	   test_ct = 0;
	   fail_ct = 0;
	   
       //Print title
       System.out.println("\n-----AUTO-GENERATED TESTS: " + part + "-----\n");
	   
	   //For each ResultPair in the given part array
	   for(int i=0; i < test_parts.length-1; i++) {
		   test_ct++;
		   
		   //Append part to the url_fragment
		   if(Objects.equals(part, "scheme")) {
		   url = test_parts[i].item + url_fragment;}
		   else url = url_fragment + test_parts[i].item;
		   expected = test_parts[i].valid; //Set expected based on part
	       actual = urlVal.isValid(url);
	       
	       if(expected != actual) {
	    	   fail_ct++;
	    	   System.out.print("ERROR ");
	    	   System.out.println("URL tested: " + url);
	    	   System.out.println("Expected: " + expected);
	    	   System.out.println("Actual: " + actual);
	    	   System.out.print('\n');}
	   }
	   
	   System.out.println("SUMMARY for " + part);
	   System.out.println("Tests run: " + test_ct);
	   System.out.println("Failures: " + fail_ct);
	   System.out.println("% passed: " + (test_ct - fail_ct)/test_ct + "\n"); 
   }

   
   
   //Manual tests of isValid() method
   public void testManualTest()
   {
       int passed = 0; //Used to indicate all tests passed
       int test_ct = 0; //Used to track # of tests
       UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

       //Print title
       System.out.println("\n-----MANUAL TESTS-----\n");

       //1. Test valid url Scheme + Auth
       test_ct++;
       String url = "http://www.google.com";
       boolean result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //2. Test same valid Scheme + different valid Auth
       test_ct++;
       url = "http://go.au";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //3. Test valid Scheme +  valid Auth + valid Port
       test_ct++;
       url = "http://www.google.com:0";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //4. Test valid Scheme +  valid Auth + valid Path
       test_ct++;
       url = "http://www.google.com/test123";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //5. Test valid Scheme +  valid Auth + valid Query
       test_ct++;
       url = "http://www.google.com?action=view";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //6. Test invalid Scheme + valid Auth
       test_ct++;
       url = "3ht://www.google.com";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, false, result)) {
           passed++;
       }

       //7. Test invalid Scheme + invalid Auth
       test_ct++;
       url = "3ht://1.2.3.4.5";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, false, result)) {
           passed++;
       }

       //8. Test another valid Scheme + valid Auth
       test_ct++;
       url = "ftp://go.au";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //9. No port, yes path and query
       test_ct++;
       url = "http://www.google.com/test1/?action=view";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //10. Yes port, no path, yes query
       test_ct++;
       url = "http://www.google.com:80?action=view";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //11. Yes port, yes path, no query
       test_ct++;
       url = "http://www.google.com:80/test1";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }
       
       //12. Boundary: non-ascii
       test_ct++;
       url = "£¥©";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, false, result)) {
           passed++;
       }
       
       //13. empty scheme
       test_ct++;
       url = "";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, "[empty scheme]", false, result)) {
           passed++;
       }
       
       //14. empty auth
       test_ct++;
       url = "http:// ";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, false, result)) {
           passed++;
       }
       
       //15. Test another valid Scheme + valid Auth (country TLD)
       test_ct++;
       url = "http://go.au";
       result = urlVal.isValid(url);
       if (compareResult(test_ct, url, true, result)) {
           passed++;
       }

       //Check ending value of passed
       assertEquals(passed, test_ct);
	 
	   
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
   
   /*Tests Generated URLs determined as follows:
   * Calls isolatePartTest for each of the 5 parts in order, passing
   * in a url_fragment made up of all valid parts not including the 
   * isolated part. */
   public void testIsValid()
   {
	   //Test Scheme w/valid Auth
	   isolatePartTest("www.google.com", testUrlScheme, "scheme");
	   
	   //Test Auth w/valid scheme
	   isolatePartTest("https://", testUrlScheme, "authority");
	   
	   //Test Port w/valid scheme+auth
	   isolatePartTest("https://www.google.com", testUrlScheme, "port");
	   
	   //Test Path w/valid scheme+auth+port
	   isolatePartTest("https://www.google.com:80", testUrlScheme, "path");
	   
	   //Test Query w/valid scheme+auth+port+path
	   isolatePartTest("https://www.google.com:80/test123", testUrlScheme, "query");
   }
   
   
   /*Data declarations for Partition and Programmed tests
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] testUrlScheme = {
		   new ResultPair("http://", true),
		   new ResultPair("http/", false),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("://", false),
           new ResultPair("", true)};

   ResultPair[] testUrlAuthority = {
		   new ResultPair("go.com", true),
		   new ResultPair("1.2.3", false),
           new ResultPair("go.com", true),
           new ResultPair("go.au", true),
           new ResultPair("0.0.0.0", true),
           new ResultPair("255.255.255.255", true),
           new ResultPair("256.256.256.256", false),
           new ResultPair("255.com", true),
           new ResultPair("1.2.3.4.5", false),
           new ResultPair("1.2.3.4.", false),
           new ResultPair(".1.2.3.4", false),
           new ResultPair("go.a", false),
           new ResultPair("go.a1a", false),
           new ResultPair("go.1aa", false),
           new ResultPair("aaa.", false),
           new ResultPair(".aaa", false),
           new ResultPair("aaa", false),
           new ResultPair("", false)};
   
   ResultPair[] testUrlPort = {
		   new ResultPair(":80", true),
		   new ResultPair(":-1", false),
           new ResultPair(":65535", true),
           new ResultPair(":0", true),
           new ResultPair("", true),
           new ResultPair(":65636",false),
           new ResultPair(":65a", false)};
                            
   ResultPair[] testPath = {
		   new ResultPair("/test1", true),
		   new ResultPair("/..//file", false),
           new ResultPair("/t123", true),
           new ResultPair("/$23", true),
           new ResultPair("/..", false),
           new ResultPair("/../", false),
           new ResultPair("/test1/", true),
           new ResultPair("", true),
           new ResultPair("/test1/file", true),
           new ResultPair("/test1//file", false)};
   
   ResultPair[] testUrlQuery = {
		   new ResultPair("?action=view", true),
		   new ResultPair("?action=??=&view&?", false),
           new ResultPair("?action=edit&mode=up", true),
           new ResultPair("", true)};

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};


}


