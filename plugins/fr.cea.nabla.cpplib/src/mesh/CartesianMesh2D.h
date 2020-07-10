/*******************************************************************************
 * Copyright (c) 2020 CEA
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 * Contributors: see AUTHORS file
 *******************************************************************************/
#ifndef MESH_CARTESIANMESH2D_H_
#define MESH_CARTESIANMESH2D_H_

#include <utility>
#include "types/Types.h"
#include "mesh/MeshGeometry.h"

using namespace std;

namespace nablalib
{

class CartesianMesh2D
{
public:
	static constexpr int MaxNbNodesOfCell = 4;
	static constexpr int MaxNbNodesOfFace = 2;
	static constexpr int MaxNbCellsOfNode = 4;
	static constexpr int MaxNbCellsOfFace = 2;
	static constexpr int MaxNbFacesOfCell = 4;
	static constexpr int MaxNbNeighbourCells = 2;

	CartesianMesh2D(MeshGeometry<2>* geometry, const vector<Id>& inner_nodes_ids,
                  const vector<Id>& top_nodes_ids, const vector<Id>& bottom_nodes_ids,
                  const vector<Id>& left_nodes_ids, const vector<Id>& right_nodes_ids,
                  const Id top_left_node_id, const Id top_right_node_id,
                  const Id bottom_left_node_id, const Id bottom_right_node_id,
				  const vector<Id>& inner_cells_ids_ , const vector<Id>& outer_cells_ids_,
				  const vector<Id>& top_row_cells_, const vector<Id>& bottom_row_cells_,
				  const vector<Id>& left_column_cells_, const vector<Id>& right_column_cells_);

	MeshGeometry<2>* getGeometry() noexcept { return m_geometry; }

	size_t getNbNodes() const noexcept { return m_geometry->getNodes().size(); }
	size_t getNbCells() const noexcept { return m_geometry->getQuads().size(); }

	//test guillaume
	size_t getNbInnerCells() const noexcept { return m_inner_cells.size();}
	const vector<Id>& getInnerCells() const noexcept {return m_inner_cells;}

	size_t getNbOuterCells() const noexcept { return m_outer_cells.size();}
	const vector<Id>& getOuterCells() const noexcept {return m_outer_cells;}

	//fin test

	size_t getNbFaces() const noexcept { return m_geometry->getEdges().size(); }
	const vector<Id>& getFaces() const noexcept { return m_faces; }
	
	size_t getNbInnerNodes() const noexcept { return m_inner_nodes.size(); }
	const vector<Id>& getInnerNodes() const noexcept { return m_inner_nodes; }

	size_t getNbTopNodes() const noexcept { return m_top_nodes.size(); }
	const vector<Id>& getTopNodes() const noexcept { return m_top_nodes; }

	size_t getNbBottomNodes() const noexcept { return m_bottom_nodes.size(); }
	const vector<Id>& getBottomNodes() const noexcept { return m_bottom_nodes; }

	size_t getNbLeftNodes() const noexcept { return m_left_nodes.size(); }
	const vector<Id>& getLeftNodes() const noexcept { return m_left_nodes; }

	size_t getNbRightNodes() const noexcept { return m_right_nodes.size(); }
	const vector<Id>& getRightNodes() const noexcept { return m_right_nodes; }


	size_t getNbTopCells() const noexcept { return m_top_cells.size(); }
	const vector<Id>& getTopCells() const noexcept { return m_top_cells; }

	size_t getNbBottomCells() const noexcept { return m_bottom_cells.size(); }
	const vector<Id>& getBottomCells() const noexcept { return m_bottom_cells; }

	size_t getNbLeftCells() const noexcept { return m_left_cells.size(); }
	const vector<Id>& getLeftCells() const noexcept { return m_left_cells; }

	size_t getNbRightCells() const noexcept { return m_right_cells.size(); }
	const vector<Id>& getRightCells() const noexcept { return m_right_cells; }

	size_t getNbTopFaces() const noexcept { return m_top_faces.size(); }
	const vector<Id>& getTopFaces() const noexcept { return m_top_faces; }

	size_t getNbBottomFaces() const noexcept { return m_bottom_faces.size(); }
	const vector<Id>& getBottomFaces() const noexcept { return m_bottom_faces; }

	size_t getNbLeftFaces() const noexcept { return m_left_faces.size(); }
	const vector<Id>& getLeftFaces() const noexcept { return m_left_faces; }

	size_t getNbRightFaces() const noexcept { return m_right_faces.size(); }
	const vector<Id>& getRightFaces() const noexcept { return m_right_faces; }
	
	
	size_t getNbOuterFaces() const noexcept { return m_outer_faces.size(); }
	vector<Id> getOuterFaces() const noexcept { return m_outer_faces; }
  
	size_t getNbInnerFaces() const noexcept { return m_inner_faces.size(); }
	vector<Id> getInnerFaces() const noexcept { return m_inner_faces; }
	
	size_t getNbInnerHorizontalFaces() const noexcept { return m_inner_horizontal_faces.size(); }
	vector<Id> getInnerHorizontalFaces() const noexcept { return m_inner_horizontal_faces; }

	size_t getNbInnerVerticalFaces() const noexcept { return m_inner_vertical_faces.size(); }
	vector<Id> getInnerVerticalFaces() const noexcept { return m_inner_vertical_faces; }

	// TODO: Temporary until single item is available in grammar
	size_t getNbTopLeftNode() const noexcept { return 1; }
	vector<Id> getTopLeftNode() const noexcept { return vector<Id>({ m_top_left_node}); }

	// TODO: Temporary until single item is available in grammar
	size_t getNbTopRightNode() const noexcept { return 1; }
	vector<Id> getTopRightNode() const noexcept { return vector<Id>({ m_top_right_node}); }

	// TODO: Temporary until single item is available in grammar
	size_t getNbBottomLeftNode() const noexcept { return 1; }
	vector<Id> getBottomLeftNode() const noexcept { return vector<Id>({ m_bottom_left_node}); }

	// TODO: Temporary until single item is available in grammar
	size_t getNbBottomRightNode() const noexcept { return 1; }
	vector<Id> getBottomRightNode() const noexcept { return vector<Id>({ m_bottom_right_node}); }
		
	const array<Id, 4>& getNodesOfCell(const Id& cellId) const noexcept;
	const array<Id, 2>& getNodesOfFace(const Id& faceId) const noexcept;
	vector<Id> getCellsOfNode(const Id& nodeId) const noexcept;
	vector<Id> getCellsOfFace(const Id& faceId) const;
	vector<Id> getNeighbourCells(const Id& cellId) const;
	vector<Id> getFacesOfCell(const Id& cellId) const;
  
	Id getCommonFace(const Id& cellId1, const Id& cellId2) const;
  
 	Id getFirstNodeOfFace(const Id& faceId) const noexcept;
	Id getSecondNodeOfFace(const Id& faceId) const noexcept;

	Id getBackCell(const Id& faceId) const;
	Id getFrontCell(const Id& faceId) const;
	Id getBottomFaceOfCell(const Id& cellId) const noexcept;
	Id getLeftFaceOfCell(const Id& cellId) const noexcept;
	Id getRightFaceOfCell(const Id& cellId) const noexcept;
	Id getTopFaceOfCell(const Id& cellId) const noexcept;

	//Test guillaume
	Id getBottomCell(const Id& cellId) const;
	Id getTopCell(const Id& cellId) const;
	Id getLeftCell(const Id& cellId) const;
	Id getRightCell(const Id& cellId) const;

	//each function consider the cases HorizontalFace and VerticalFace
	Id getBottomFaceNeighbour(const Id& faceId) const;
	Id getBottomLeftFaceNeighbour(const Id& faceId) const;
	Id getBottomRightFaceNeighbour(const Id& faceId) const;

	Id getTopFaceNeighbour(const Id& faceId) const;
	Id getTopLeftFaceNeighbour(const Id& faceId) const;
	Id getTopRightFaceNeighbour(const Id& faceId) const;

	Id getRightFaceNeighbour(const Id& faceId) const;
	Id getLeftFaceNeighbour(const Id& faceId) const;

	//fin test

	//test guillaume
	size_t getNbCompletelyInnerFaces() const noexcept { return m_completely_inner_faces.size(); }
	const vector<Id>& getCompletelyInnerFaces() const noexcept { return m_completely_inner_faces; }

	size_t getNbCompletelyInnerVerticalFaces() const noexcept { return m_completely_inner_vertical_faces.size(); }
	const vector<Id>& getCompletelyInnerVerticalFaces() const noexcept { return m_completely_inner_vertical_faces; }

	size_t getNbCompletelyInnerHorizontalFaces() const noexcept { return m_completely_inner_horizontal_faces.size(); }
	const vector<Id>& getCompletelyInnerHorizontalFaces() const noexcept { return m_completely_inner_horizontal_faces; }

	size_t getNbTopRowCells() const noexcept { return m_top_row_cells.size(); }
	const vector<Id>& getTopRowCells() const noexcept { return m_top_row_cells; }

	size_t getNbBottomRowCells() const noexcept { return m_bottom_row_cells.size(); }
	const vector<Id>& getBottomRowCells() const noexcept { return m_bottom_row_cells; }

	size_t getNbLeftColumnCells() const noexcept { return m_left_column_cells.size(); }
	const vector<Id>& getLeftColumnCells() const noexcept { return m_left_column_cells;}

	size_t getNbRightColumnCells() const noexcept { return m_right_column_cells.size(); }
	const vector<Id>& getRightColumnCells() const noexcept { return m_right_column_cells; }
	//fin test
  
private:
	inline Id index2IdCell(const size_t& i, const size_t& j) const noexcept;
	inline Id index2IdNode(const size_t& i, const size_t& j) const noexcept;
	inline pair<size_t, size_t> id2IndexCell(const Id& k) const noexcept;
	inline pair<size_t, size_t> id2IndexNode(const Id& k) const noexcept;
  
	bool isInnerEdge(const Edge& e) const noexcept;
	bool isInnerVerticalEdge(const Edge& e) const noexcept;
	bool isInnerHorizontalEdge(const Edge& e) const noexcept;

	//test guillaume
	bool isCompletelyInnerEdge(const Edge& e) const noexcept;


	bool isCompletelyInnerVerticalEdge(const Edge& e) const noexcept;


	bool isCompletelyInnerHorizontalEdge(const Edge& e) const noexcept;
	//fin test
  
	size_t getNbCommonIds(const vector<Id>& a, const vector<Id>& b) const noexcept;
	template <size_t N, size_t M>
	size_t	getNbCommonIds(const array<Id, N>& as, const array<Id, M>& bs) const noexcept
	{
		size_t nbCommonIds(0);
		for (const auto& a : as)
			if (find(bs.begin(), bs.end(), a) != bs.end())
				++nbCommonIds;
		return nbCommonIds;
	}

	inline vector<Id> cellsOfNodeCollection(const vector<Id>& nodes);
	
private:
	MeshGeometry<2>* m_geometry;
    
	vector<Id> m_inner_nodes;
	vector<Id> m_top_nodes;
	vector<Id> m_bottom_nodes;
	vector<Id> m_left_nodes;
	vector<Id> m_right_nodes;
	Id m_top_left_node;
	Id m_top_right_node;
	Id m_bottom_left_node;
	Id m_bottom_right_node;

	vector<Id> m_top_cells;
	vector<Id> m_bottom_cells;
	vector<Id> m_left_cells;
	vector<Id> m_right_cells;

	vector<Id> m_faces;
	vector<Id> m_outer_faces;
	vector<Id> m_inner_faces;
	vector<Id> m_inner_horizontal_faces;
	vector<Id> m_inner_vertical_faces;
	vector<Id> m_top_faces;
	vector<Id> m_bottom_faces;
	vector<Id> m_left_faces;
	vector<Id> m_right_faces;

	//test guillaume
	vector<Id> m_inner_cells;
	vector<Id> m_outer_cells;

	vector<Id> m_completely_inner_horizontal_faces;
	vector<Id> m_completely_inner_vertical_faces;
	vector<Id> m_completely_inner_faces;

	vector<Id> m_top_row_cells;
	vector<Id> m_bottom_row_cells;
	vector<Id> m_left_column_cells;
	vector<Id> m_right_column_cells;

	//fin test

	size_t m_nb_x_quads;
	size_t m_nb_y_quads;
};

}
#endif /* MESH_CARTESIANMESH2D_H_ */
