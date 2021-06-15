import simpy
from random import seed, randint
seed(23)


class Demo:
    def __init__(self, env):
        self.env = env
        self.drive_proc = env.process(self.drive(env))
        self.bat_ctrl_proc = env.process(self.bat_ctrl(env))
        self.bat_ctrl_reactivate = env.event()
        self.bat_ctrl_sleep = env.event()

    def drive(self, env):
        while True:
            print("start driving: ", env.now)
            yield env.timeout(randint(20, 40))
            print("stop driving: ", env.now)

            print("start parking: ", env.now)
            self.bat_ctrl_reactivate.succeed()
            self.bat_ctrl_reactivate = env.event()
            yield env.timeout(randint(60, 360)) & self.bat_ctrl_sleep
            print("stop parking: ", env.now)

    def bat_ctrl(self, env):
        while True:
            print("charging process sleep: ", env.now)
            yield self.bat_ctrl_reactivate
            print("charging process awake: ", env.now)
            yield env.timeout(randint(30, 90))
            print("charging process end: ", env.now)
            self.bat_ctrl_sleep.succeed()
            self.bat_ctrl_sleep = env.event()


if __name__ == '__main__':
    environment = simpy.Environment()
    ev = Demo(environment)
    environment.run(until=300)


