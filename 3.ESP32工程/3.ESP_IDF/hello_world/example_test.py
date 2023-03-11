'''
Author: your name
Date: 2022-03-03 08:17:09
LastEditTime: 2022-03-03 08:23:36
LastEditors: Please set LastEditors
Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
FilePath: \hello_world\example_test.py
'''
#!/usr/bin/env python

from __future__ import division, print_function, unicode_literals

import ttfw_idf


@ttfw_idf.idf_example_test(env_tag='Example_GENERIC', target=['esp32', 'esp32s2', 'esp32c3'], ci_target=['esp32'])
def test_examples_hello_world(env, extra_data):
    app_name = 'hello_world'
    dut = env.get_dut(app_name, 'examples/get-started/hello_world')
    dut.start_app()
    res = dut.expect(ttfw_idf.MINIMUM_FREE_HEAP_SIZE_RE)
    if not res:
        raise ValueError('Maximum heap size info not found')
    ttfw_idf.print_heap_size(app_name, dut.app.config_name, dut.TARGET, res[0])


if __name__ == '__main__':
    test_examples_hello_world()
