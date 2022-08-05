

from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Callable, Generic, Iterable, Mapping, TypeVar


from .distribution import Choose, Constant, Distribution, FiniteDistribution
from .markov_process import NonTerminal

A = TypeVar('A')
S = TypeVar('S')
class Policy(ABC, Generic[S, A]):

    @abstractmethod
    def act(self, state: NonTerminal[S]) -> Distribution[A]:
        pass


@dataclass(frozen=True)
class DeterministicPolicy(Policy[S, A]):
    action_for: Callable[[S], A]

    def act(self, state: NonTerminal[S]) -> Distribution[A]:
        return Constant(self.action_for(state.state))


@dataclass(frozen=True)
class UniformPolicy(Policy[S, A]):
    valid_actions: Callable[[S], Iterable[A]]

    def act(self, state: NonTerminal[S]) -> Distribution[A]:
        return Choose(self.valid_actions(state.state))


@dataclass(frozen=True)
class FinitePolicy(Policy[S, A]):
    policy_map: Mapping[S, FiniteDistribution[A]]

    def __repr__(self) -> str:
        display = ""
        for s, d in self.policy_map.items():
            display += f"For State {s}:\n"
            for a, p in d:
                display += f"  Do Action {a} with Probability {p:.3f}\n"
        return display

    def act(self, state: NonTerminal[S]) -> FiniteDistribution[A]:
        return self.policy_map[state.state]


class FiniteDeterministicPolicy(FinitePolicy[S, A]):
    action_for: Mapping[S, A]
    
    def __init__(self, action_for: Mapping[S, A]) -> None:
        self.action_for = action_for
        super().__init__(policy_map={s: Constant(a) for s, a in self.action_for.items()})

    def __repr__(self) -> str:
        display = ""
        for s, a in self.action_for.items():
            display += f"For State {s}: Do Action {a}\n"
        return display