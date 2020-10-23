Pod::Spec.new do |s|  
    s.name              = 'BuzzSDK'
    s.version           = '3.2.0'
    s.summary           = 'BuzzSDK is a turnkey solution for publishers to add an extra revenue stream to their mobile app suites.'
    s.homepage          = 'http://www.buzzsdk.com/'

    s.author            = { 'Name' => 'alfonso@buzztechno.com' }
    s.license           = { :type => 'Apache-2.0', :file => 'LICENSE' }

    s.platform          = :ios
    s.source            = { :git => 'https://github.com/move-fast/BuzzSDKPod.git', :tag => 'v3.2.0' }

    s.ios.deployment_target = '11.0'
    s.ios.vendored_frameworks = 'BuzzSDK.framework'
    s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
    s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
end  
