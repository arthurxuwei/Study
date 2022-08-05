from __future__ import annotations
from abc import ABC, abstractmethod
from collections import defaultdict
from dataclasses import dataclass
from typing import Generic, Callable, Sequence, TypeVar, Iterable, Set, Mapping, Tuple
import numpy as np
from pprint import pprint

from .distribution import Distribution, FiniteDistribution, Categorical, SampledDistribution, A

S = TypeVar('S')
X = TypeVar('X')

class State(ABC, Generic[S]):
    state: S
    def on_non_terminal(self, f: Callable[[NonTerminal[S]], X], default: X) -> X:
        if isinstance(self, NonTerminal):
            return f(self)
        else:
            return default

@dataclass(frozen=True)
class Terminal(State[S]):
    state: S

@dataclass(frozen=True)
class NonTerminal(State[S]):
    state: S

class MarkovProcess(ABC, Generic[S]):
    @abstractmethod
    def transition(self, state: NonTerminal[S]) -> Distribution[State[S]]:
        pass
    
    def simulate(self, start_state_distribution: Distribution[NonTerminal[S]]) -> Iterable[State[S]]:
        state: State[S] = start_state_distribution.sample()
        yield state
        while isinstance(state, NonTerminal):
            state = self.transition(state).sample()
            yield state

Transition = Mapping[NonTerminal[S], FiniteDistribution[State[S]]]

class FiniteMarkovProcess(MarkovProcess[S]):
    non_terminal_states: Sequence[NonTerminal[S]]
    transition_map: Transition[S]

    def __init__(self, transition_map: Transition) -> None:
        non_terminals: Set[S] = set(transition_map.keys())
        self.transition_map = {
            NonTerminal(s): Categorical({(NonTerminal(s1) if s1 in non_terminals else Terminal(s1)) : p for s1, p in v})
            for s, v in transition_map.items()
        }
        self.non_terminal_states = list(self.transition_map.keys())

    def __repr__(self) -> str:
        display = ""
        for s, d in self.transition_map.items():
            display += f"From State {s.state}:\n"
            for s1, p in d:
                opt = ("Terminal State" if isinstance(s1, Terminal) else "State")
                display += f"To {opt} {s1.state} with Probability {p:.3f}\n"
        return display
    
    def transition(self, state: NonTerminal[S]) -> Distribution[State[S]]:
        return self.transition_map[state]

    def get_transition_matrix(self) -> np.ndarray:
        sz = len(self.non_terminal_states)
        mat = np.zeros((sz, sz))
        for i, s1 in enumerate(self.non_terminal_states):
            for j, s2 in enumerate(self.non_terminal_states):
                mat[i, j] = self.transition(s1).probability(s2)
        return mat

    def get_stationary_distribution(self) -> FiniteDistribution[S]:
        eig_vals, eig_vecs = np.linalg.eig(self.get_transition_matrix().T)
        index_of_first_unit_eig_val = np.where(np.abs(eig_vals - 1) < 1e-8)[0][0]
        eig_vec_of_unit_eig_val = np.real(eig_vecs[:, index_of_first_unit_eig_val])
        return Categorical({
            self.non_terminal_states[i].state: ev 
            for i, ev in enumerate(eig_vec_of_unit_eig_val / sum(eig_vec_of_unit_eig_val))
        })

    def display_stationary_distribution(self):
        pprint({
            s: round(p, 3)
            for s, p in self.get_stationary_distribution()
        })

@dataclass(frozen=True)
class TransitionStep(Generic[S, A]):
    state: NonTerminal[S]
    next_state: State[S]
    reward: float

class MarkovRewardProcess(MarkovProcess[S]):

    @abstractmethod
    def transition_reward(self, state: NonTerminal[S]) -> Distribution(Tuple[State[S], float]):
        pass

    def simulate_reward(self, start_state_distribution: Distribution[NonTerminal[S]]) -> Iterable[TransitionStep[S]]:
        state: State[S] = start_state_distribution.sample()
        reward: float = 0.

        while isinstance(state, NonTerminal):
            next_distribution = self.transition_reward(state)
            next_state, reward = next_distribution.sample()
            yield TransitionStep(state, next_state, reward)
            state = next_state

    def transition(self, state: NonTerminal[S]) -> Distribution[State[S]]:
        distribution = self.transition_reward(state)
        def next_state(distribution=distribution):
            next_s, _ = distribution.sample()
            return next_s
        return SampledDistribution(next_state)
    
    def reward_traces(self, start_state_distribution: Distribution[NonTerminal[S]]) -> Iterable[Iterable[TransitionStep[S]]]:
        while True:
            yield self.simulate_reward(start_state_distribution)


StateReward = FiniteDistribution[Tuple[State[S], float]]
RewardTransition = Mapping[NonTerminal[S], StateReward[S]]

class FiniteMarkovRewardProcess(FiniteMarkovProcess[S], MarkovRewardProcess[S]):
    transition_reward_map: RewardTransition[S]
    reward_function_vec: np.ndarray

    def __init__(self, transition_reward_map: Transition) -> None:
        transition_map = {}
        for state, trans in transition_reward_map.items():
            probabilities = defaultdict(float)
            for (next_state, _), probability in trans:
                probabilities[next_state] += probability
            transition_map[state] = Categorical(probabilities)
        super().__init__(transition_map)

        nt = set(transition_reward_map.keys())
        self.transition_reward_map = {
            NonTerminal(s): Categorical({(NonTerminal(s1) if s1 in nt else Terminal(s1), r): p for (s1, r), p in v})
            for s, v in transition_reward_map.items()
        }
        self.reward_function_vec = np.array([
            sum(probability * reward for (_, reward), probability in self.transition_reward_map[state])
            for state in self.non_terminal_states
        ])
    
    def transition_reward(self, state: NonTerminal[S]) -> Distribution(Tuple[State[S], float]):
        return self.transition_reward_map[state]

    def display_reward_function(self):
        pprint({
            self.non_terminal_states[i]: round(r, 3)
            for i, r in enumerate(self.reward_function_vec)
        })
    
    def get_value_function_vec(self, gamma: float) -> np.ndarray:
        return np.linalg.solve(
            np.eye(len(self.non_terminal_states)) - gamma * self.get_transition_matrix(),
            self.reward_function_vec
        )
    
    def display_value_function(self, gamma: float):
        pprint({
            self.non_terminal_states[i]: round(v, 3)
            for i, v in enumerate(self.get_value_function_vec(gamma))
        })
