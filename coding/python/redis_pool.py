import time
import redis

POOL = redis.ConnectionPool(host=REDIS_HOST, port=REDIS_PORT, db=REDIS_DEF_DB)

def add_addr(ip_pool, ip_addr):
    redis_conn = redis.Redis(connection_pool=POOL)
    lua_script = """
    if redis.call('EXISTS', string.format('_pool_cd_%s', KEYS[3])) == 1 then
        return nil
    end
    return redis.call('ZADD', KEYS[1], KEYS[3], KEYS[2])
    """
    redis_pool_name = '_pool_avl_:%s' % ip_pool_name.upper()
    return redis_conn.eval(lua_script, 3, redis_pool_name, ip_addr, int(time.time()))


def pop_addr(ip_pool):
    redis_conn = redis.Redis(connection_pool=POOL)
    redis_pool_name = '_pool_avl_:%s' % ip_pool_name.upper()
    lua_script = """
    local ip = unpack(redis.call('zrange', KEYS[1], 0, 0))
    if ip == nil or ip == '' then
        return nil
    end
    local cd_flag =  string.format('_pool_cd_%s', ip)
    if redis.call('EXISTS', cd_flag) == 1 then
        return nil
    end
    redis.call('SETEX', cd_flag, 30, ip)
    redis.call('ZREM', KEYS[1], ip)
    return ip
    """
    return redis_conn.eval(lua_script, 1, redis_pool_name)