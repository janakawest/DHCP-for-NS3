# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('dhcp', ['core'])
    module.source = [
        'model/dhcp.cc',
				'model/dhcp-server.cc',
				'model/dhcp-client.cc',
				'model/dhcp-header.cc',
        'helper/dhcp-client-helper.cc',
        'helper/dhcp-server-helper.cc',
        ]

#    module_test = bld.create_ns3_module_test_library('dhcp')
#    module_test.source = [
#        'test/dhcp-test-suite.cc',
#        ]

    headers = bld(features='ns3header')
    headers.module = 'dhcp'
    headers.source = [
        'model/dhcp-header.h',
				'model/dhcp-server.h',
				'model/dhcp-client.h',
        'model/dhcp.h',
        'helper/dhcp-client-helper.h',
        'helper/dhcp-server-helper.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

