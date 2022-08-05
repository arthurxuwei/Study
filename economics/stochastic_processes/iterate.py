from typing import Callable, Iterable, Iterator, TypeVar

X = TypeVar('X')
Y = TypeVar('Y')

def iterate(step: Callable[[X], X], start: X) -> Iterable[X]:
    state = start
    while True:
        yield state
        state = step(state)


def converge(values: Iterator[X],  done: Callable[[X, X], bool]) -> Iterator[X]:
    a = next(values, None)
    if a is None:
        return
    yield a
    for b in values:
        yield b
        if done(a, b):
            return
        a = b

