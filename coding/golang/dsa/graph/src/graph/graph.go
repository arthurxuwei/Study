package graph

import (
	//	"fmt"
	"graph/disjoint"
)

type Graph struct {
	vertexMap map[int64]*Vertex
	edgeMap   map[string]*Edge
}

func New() *Graph {
	g := new(Graph)
	g.edgeMap = make(map[string]*Edge)
	g.vertexMap = make(map[int64]*Vertex)
	return g
}

func (g *Graph) EdgeCount() int {
	return len(g.edgeMap)
}

func (g *Graph) VertexCount() int {
	return len(g.vertexMap)
}

func (g *Graph) AddVertex() *Vertex {
	v := newVertex()
	g.vertexMap[v.Identifier()] = v
	return v
}

func (g *Graph) GetVertex(id int64) *Vertex {
	vertex := g.vertexMap[id]
	return vertex
}

func (g *Graph) RemoveVertex(v *Vertex) {
	if !g.VertexExists(v) {
		return
	}
	iteration_channel := v.EdgeIter()

	//	for !closed(iteration_channel) {
	//		e := <-iteration_channel
	//		if e == nil { continue }
	//		e.removeSelf()
	//		g.edgeMap[e.Identifier()] = e, false
	//	}
outer:
	for {
		select {
		case e, ok := <-iteration_channel:
			if ok {
				//read data.
				e.removeSelf()
				delete(g.edgeMap, e.Identifier())
			} else {
				//channel close.
				break outer
			}
		default:
			//no value ready, moving on.
			break
		}
	}

	delete(g.vertexMap, v.Identifier())
}

func (g *Graph) RemoveEdge(e *Edge) {
	if !g.EdgeExists(e) {
		return
	}

	e.removeSelf()
	delete(g.edgeMap, e.Identifier())
}

func (g *Graph) GetEdge(id string) *Edge {
	edge := g.edgeMap[id]
	return edge
}

func (g *Graph) ConnectVertices(v1, v2 *Vertex) (edge *Edge) {
	edge = newEdge(v1, v2)

	if g.EdgeExists(edge) {
		edge = g.edgeMap[edge.Identifier()]
	} else {
		g.edgeMap[edge.Identifier()] = edge
		v1.registerEdge(edge)
		v2.registerEdge(edge)
	}

	return edge
}

func (g *Graph) VertexExists(v *Vertex) bool {
	if _, ok := g.vertexMap[v.Identifier()]; ok {
		return true
	} else {
		return false
	}
}

func (g *Graph) EdgeExists(edge *Edge) bool {
	if _, ok := g.edgeMap[edge.Identifier()]; ok {
		return true
	} else {
		return false
	}
}

func (g *Graph) edgeiterate(c chan<- *Edge) {
	for _, val := range g.edgeMap {
		c <- val
	}
	close(c)
}

func (g *Graph) EdgeIterIter() chan *Edge {
	c := make(chan *Edge)
	go g.edgeiterate(c)
	return c
}

func (g *Graph) vertexiterate(c chan<- *Vertex) {
	for _, val := range g.vertexMap {
		c <- val
	}
	close(c)
}

func (g *Graph) VertexIter() chan *Vertex {
	c := make(chan *Vertex)
	go g.vertexiterate(c)
	return c
}

func dfs(visited map[int64]bool, iter <-chan *Edge, f func(*Vertex)) {
	//	for !closed(iter) {
	//		e := <-iter
	//		if e == nil {continue}
	//		v1, v2 = e.Endpoints()
	//
	//		if !visited[v1.Identifier()] {
	//			//disjoint.Union(forest[v1.Identifier()], forest[v.Identifier()])
	//			f(v1)
	//			visited[v1.Identifier()] = true
	//			dfs(visited, v1.EdgeIter(), f)
	//		}
	//
	//		if !visited[v2.Identifier()] {
	//			//disjoint.Union(forest[v2.Identifier()], forest[v.Identifier()])
	//			f(v2)
	//			visited[v2.Identifier()] = true
	//			dfs(visited, v2.EdgeIter(), f)
	//		}
	//	}
outer:
	for {
		select {
		case e, ok := <-iter:
			if ok {
				v1, v2 := e.Endpoints()

				if !visited[v1.Identifier()] {
					//disjoint.Union(forest[v1.Identifier()], forest[v.Identifier()])
					f(v1)
					visited[v1.Identifier()] = true
					dfs(visited, v1.EdgeIter(), f)
				}

				if !visited[v2.Identifier()] {
					//disjoint.Union(forest[v2.Identifier()], forest[v.Identifier()])
					f(v2)
					visited[v2.Identifier()] = true
					dfs(visited, v2.EdgeIter(), f)
				}

			} else {
				break outer
			}
		default:
			break
		}
	}
}

func (g *Graph) Dfs(v *Vertex, f func(*Vertex)) map[int64]bool {
	visited := make(map[int64]bool)

	for v := range g.VertexIter() {
		visited[v.Identifier()] = false
	}

	visited[v.Identifier()] = true
	dfs(visited, v.EdgeIter(), f)

	return visited
}

func (g *Graph) dfsrevisit(visited map[int64]bool, v *Vertex, f func(*Vertex)) map[int64]bool {
	visited[v.Identifier()] = true
	dfs(visited, v.EdgeIter(), f)
	return visited
}

func (g *Graph) FindConnectedComponents() map[int64]*disjoint.Element {
	forest := make(map[int64]*disjoint.Element)

	for v := range g.VertexIter() {
		forest[v.Identifier()] = disjoint.Makeset()
	}

	var current_rep *Vertex
	for key, _ := range forest {
		current_rep = g.GetVertex(key)
		break
	}

	process_vertex := func(v *Vertex) {
		disjoint.Union(forest[v.Identifier()], forest[current_rep.Identifier()])
	}

	visited := g.Dfs(current_rep, process_vertex)

	find_unfound := func(visited_map map[int64]bool) *Vertex {
		for key, value := range visited_map {
			if !value {
				return g.GetVertex(key)
			}
		}
		return nil
	}

	for {
		current_rep = find_unfound(visited)
		if current_rep == nil {
			break
		}
		visited = g.dfsrevisit(visited, current_rep, process_vertex)
	}

	return forest
}
