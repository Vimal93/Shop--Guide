Pod::Spec.new do |s|
  s.name         = "ScanAPI"
  s.version      = "10.2.227"
  s.summary      = "Socket Mobile Wireless barcode scanners SDK."
  s.homepage     = "http://www.socketmobile.com"
  s.license      = { :type => "COMMERCIAL", :file => "LICENSE" }
  s.author       = { "Eric Glaenzer" => "ericg@socketmobile.com" }
  s.docset_url   = "http://www.socketmobile.com/docs/default-source/developer-documentation/scanapi.pdf?sfvrsn=2"
  s.platform     = :ios, "7.1"
  s.ios.deployment_target = "7.1"
  s.source_files  = "**/*.{h,m,mm}"
  s.preserve_path = "**/*.a"
  s.resource = "*.wav"
  s.ios.vendored_library = "lib/libScanApiCore.a"
  s.ios.library = "c++"
  s.frameworks = "ExternalAccessory", "AudioToolbox", "AVFoundation"
end
