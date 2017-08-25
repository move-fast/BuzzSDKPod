Pod::Spec.new do |s|  
    s.name              = 'BuzzSDK'
    s.version           = '1.2.2'
    s.summary           = 'BuzzSDK is a turnkey solution for publishers to add an extra revenue stream to their mobile app suites.\nThe SDK offers high RPM while providing great user experience to keep churn low.\nThis is achieved using great video ads in conjunction with a trouble free user experience and picture-in-picture video playback.'
    s.homepage          = 'http://www.buzzsdk.com/'

    s.author            = { 'Name' => 'alfonso@buzztechno.com' }
    s.license           = { :type => 'Apache-2.0', :file => 'LICENSE' }

    s.platform          = :ios
    s.source            = { :git => 'https://github.com/move-fast/BuzzSDKPod.git', , :tag => 'v1.2.2' }

    s.ios.deployment_target = '9.0'
    s.ios.vendored_frameworks = 'BuzzSDK.framework'
end  