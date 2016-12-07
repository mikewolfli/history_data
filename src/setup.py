# -*- coding: utf-8 -*-
'''
Created on 2015年8月25日

@author: 10256603
'''
from distutils.core import setup
import py2exe
		 
setup( description="历史数据导出程序",
	   zipfile=None,
       windows=[  {
                        "script":"history_data.py",
                        "icon_resources": [(1, "history_data.ico")]
                }])