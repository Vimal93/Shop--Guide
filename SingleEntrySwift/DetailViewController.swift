
import UIKit
import AVFoundation

class DetailViewController: UIViewController,ScanApiHelperDelegate {
    let noScannerConnected = "No scanner connected"
    var scanners : [NSString] = []  // keep a list of scanners to display in the status
    var softScanner : DeviceInfo?  // keep a reference on the SoftScan Scanner
    let synth = AVSpeechSynthesizer()
    var myUtterance = AVSpeechUtterance(string: "")
    
    
    @IBOutlet weak var connectionStatus: UILabel!
    @IBOutlet weak var decodedData: UITextField!
    @IBOutlet weak var softScanTrigger: UIButton!

    var detailItem: AnyObject?
    var showSoftScanOverlay = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        softScanTrigger.hidden = true;

    }
    
    override func viewDidAppear(animated: Bool) {
        // if we are showing the SoftScan Overlay view we don't
        // want to push our delegate again when our view becomes active
        if showSoftScanOverlay == false {
            // since we use ScanApiHelper in shared mode, we push this
            // view controller delegate to the ScanApiHelper delegates stack
            ScanApiHelper.sharedScanApiHelper().pushDelegate(self)
        }
        showSoftScanOverlay = false
        displayScanners()
    }
    
    override func viewDidDisappear(animated: Bool) {
        // if we are showing the SoftScan Overlay view we don't
        // want to remove our delegate from the ScanApiHelper delegates stack
        if showSoftScanOverlay == false {
            // remove all the scanner names from the list
            // because in ScanApiHelper shared mode we will receive again
            // the deviceArrival for each connected scanner once this view
            // becomes active again
            scanners = []
            softScanTrigger.hidden = true;
            ScanApiHelper.sharedScanApiHelper().popDelegate(self)
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func onSoftScanTrigger(sender: AnyObject) {
        if let scanner = softScanner as DeviceInfo! {
            showSoftScanOverlay = true
            ScanApiHelper.sharedScanApiHelper().postSetTriggerDevice(scanner, action: UInt8(kSktScanTriggerStart), target: self, response: "onSetTrigger:")
        }
    }
    
    // MARK: - Utility functions
    func displayScanners(){
        if let status = connectionStatus {
            status.text = ""
            for scanner in scanners {
                status.text = status.text! + (scanner as String) + "\n"
            }
            if(scanners.count == 0){
                status.text = noScannerConnected
            }
        }
    }

    func displayErrorAlert(result: SKTRESULT, operation : String){
        if result != ESKT_NOERROR {
            let errorTxt = "Error \(result) while doing a \(operation)"
            let alert = UIAlertController(title: "ScanAPI Error", message: errorTxt, preferredStyle: .Alert)
            alert.addAction(UIAlertAction(title: "Dismiss", style: .Default, handler: nil))
            self.presentViewController(alert, animated: true, completion: nil)
        }
    }
    
    // MARK: - ScanApi complete callbacks
    
    // display an error message if the setTrigger failed
    // and reset the showSoftScanOverlay
    func onSetTrigger(scanObj : ISktScanObject){
        let result = scanObj.Msg().Result()
        displayErrorAlert(result, operation: "SetTrigger")
        if result != ESKT_NOERROR {
            showSoftScanOverlay = false
        }
    }
    
    // display an error message if the setOverlayView failed
    func onSetOverlayView(scanObj: ISktScanObject){
        let result = scanObj.Msg().Result()
        displayErrorAlert(result, operation: "SetOverlayView")
    }
    
    // MARK: - ScanApiHelperDelegate

    func onDecodedDataResult(result: Int, device: DeviceInfo!, decodedData: ISktScanDecodedData!) {
        print("onDecodedDataResult in the detail view")
        if result==ESKT_NOERROR {
            let rawData = decodedData.getData()
            let rawDataSize = decodedData.getDataSize()
            let data = NSData(bytes: rawData, length: Int(rawDataSize))
            print("Size: \(rawDataSize)")
            print("data: \(data)")
            let str = NSString(data: data, encoding: NSUTF8StringEncoding)
            let s = str as! String
            //print(string.bridgeToObjectiveC().className)
            print("Decoded Data \(s)")
            self.decodedData.text = s
            let character = Array(s.characters)
            
            myUtterance = AVSpeechUtterance(string: "The scanned barcode is")
            myUtterance.rate = 0.4
            synth.speakUtterance(myUtterance)
            var strng = ""
            for c in character {
                myUtterance = AVSpeechUtterance(string: String(c))
                print("\(c)")
                synth.speakUtterance(myUtterance)
            strng.append(c)
            }
            searchDB(strng)
            
        }
    }
    

    // since we use ScanApiHelper in shared mode, we receive a device Arrival
    // each time this view becomes active and there is a scanner connected
    func onDeviceArrival(result: SKTRESULT, device deviceInfo: DeviceInfo!) {
        print("onDeviceArrival in the detail view")
        let name = deviceInfo.getName()
        if(name.caseInsensitiveCompare("SoftScanner") == NSComparisonResult.OrderedSame){
            softScanTrigger.hidden = false;
            softScanner = deviceInfo
            
            // set the Overlay View context to give a reference to this controller
            if let scanner = softScanner as DeviceInfo! {
                let context : NSDictionary = [
                    String.fromCString(kSktScanSoftScanContext)! : self
                ]
                ScanApiHelper.sharedScanApiHelper().postSetOverlayView(scanner, overlayView: context, target: self, response: "onSetOverlayView:")
            }
        }
        scanners.append(deviceInfo.getName())
        displayScanners()
        myUtterance = AVSpeechUtterance(string: "Socket Scanner Connected")
        myUtterance.rate = 0.4
        synth.speakUtterance(myUtterance)
    }

    func onDeviceRemoval(deviceRemoved: DeviceInfo!) {
        print("onDeviceRemoval in the detail view")
        var newScanners : [String] = []
        for scanner in scanners{
            if(scanner != deviceRemoved.getName()){
                newScanners.append(scanner as String)
            }
        }
        // if the scanner that is removed is SoftScan then
        // we nil its reference
        if softScanner != nil {
            if softScanner == deviceRemoved {
                softScanner = nil
            }
        }
        scanners=newScanners
        displayScanners()
        myUtterance = AVSpeechUtterance(string: "Scanner Disconnected")
        myUtterance.rate = 0.4
        synth.speakUtterance(myUtterance)
    }
    
    func searchDB(str: String)
    {
        //let searchURL = "http://api.v3.factual.com/t/products-cpg-nutrition"
        //let apiKey: String = "efqwzjqeda9tbufbtdux7zhv"
        
        //let character = Array(str.characters)
        
        var c = str.characters.count
        
        print(c)
        
        // Add search paramenters for the URL to search
        var searchURL : String = "http://api.walmartlabs.com/v1/items?apiKey=ktkq2hyr88d2bzvdmfj5efte"
        searchURL += "&upc="
        //searchURL += sliced
        
        if(c == 14) {
            let sliced = String(str.characters.dropFirst())
            print("\(sliced)")
            searchURL += sliced }
        else if(c == 9){
            var s = String(str.characters.dropFirst())
            s = s.substringToIndex(s.endIndex.predecessor())
            print(s)
            let ch = Array(s.characters)
            var u = "0"
            u.append(ch[0])
            u.append(ch[1])
            u.append(ch[2])
            u.appendContentsOf("00000")
            u.append(ch[3])
            u.append(ch[4])
            u.append(ch[5])
            print(u)
            searchURL += u
            searchURL.append(ch[3])
            searchURL.append(ch[4])
            searchURL.append(ch[4])
            
            }
        else {
            searchURL += str
        }
        
    
        var urlstr: String = searchURL.stringByAddingPercentEscapesUsingEncoding(NSUTF8StringEncoding)!
        urlstr = urlstr.substringToIndex(urlstr.endIndex.predecessor())
        urlstr = urlstr.substringToIndex(urlstr.endIndex.predecessor())
        urlstr = urlstr.substringToIndex(urlstr.endIndex.predecessor())
        
        
        print("\(urlstr)")
        
        // URL object
        guard let url : NSURL = NSURL(string: urlstr) else
        {
            print("Error: cannot create URL")
            return
        }
        
        print ("\(url)")
        
        //Create URL request
        let request: NSMutableURLRequest = NSMutableURLRequest(URL:url)
        
        
        // Set request HTTP method to GET
        request.HTTPMethod = "GET"
        
        // Excute HTTP Request
        let task = NSURLSession.sharedSession().dataTaskWithRequest(request) {
            data, response, error in
            
            // Check for error
            if error != nil
            {
                print("error=\(error)")
                return
            }
            
            // Print out response string
            let responseString = NSString(data: data!, encoding: NSUTF8StringEncoding)
            print("responseString = \(responseString)")
            
            let data = responseString!.dataUsingEncoding(NSUTF8StringEncoding)
            // Convert server json response to NSDictionary
            //var names = [String]()
            
            do {
                let json = try NSJSONSerialization.JSONObjectWithData(data!, options: .AllowFragments)
                
                if let blogs = json["items"] as? [[String: AnyObject]] {
                    for blog in blogs {
                        if let name = blog["name"] as? String {
                            self.myUtterance = AVSpeechUtterance(string: "The name of the scanned product is \(name)")
                            self.myUtterance.rate = 0.4
                            self.synth.speakUtterance(self.myUtterance)
                            print(name)
                        }
                        if let saleprice = blog["salePrice"] as? Float {
                            self.myUtterance = AVSpeechUtterance(string: "The price is \(saleprice)")
                            self.myUtterance.rate = 0.4
                            self.synth.speakUtterance(self.myUtterance)
                            print(saleprice)
                        }
                    }
                }
            } catch {
                print("error serializing JSON: \(error)")
            }
            
        }
        
        task.resume()
    }

}
