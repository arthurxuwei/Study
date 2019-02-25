# -*- coding: utf-8 -*-    

from contextlib import contextmanager
from log import logger

def make_error_handler(catch):
	@contextmanager
	def handler():
		try:
			yield
		except catch, e:
			logger.error(e)
			raise
	return handler
	
def full_error_handler(catch):
	@contextmanager
	def handler(**kwargs):
		try:
			yield
		except catch, e:
			if 'handler' in kwargs:
				kwargs['handler']()
			raise
		else:
			if 'without' in kwargs:
				kwargs['without']()
		finally:
			if 'cleanup' in kwargs:
				kwargs['cleanup']()
	return handler
	
def db_error_handler(catch, conn):
	@contextmanager
	def handler(**kwargs):
		cursor = conn.cursor()
		try:
			yield cursor
		except catch, e:
			if 'handler' in kwargs:
				kwargs['handler']()
			raise
		else:
			if 'without' in kwargs:
				kwargs['without']()
		finally:
			cursor.close()
	return handler
	
	
if __name__ == '__main__':
	error_handler = full_error_handler(Exception)
	with error_handler():
		raise Exception
	db_handler = db_error_handler(Exception, conn)