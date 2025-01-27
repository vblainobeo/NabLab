"""
DO NOT EDIT THIS FILE - it is machine generated
"""
import sys
import json
import numpy as np
import math
from cartesianmesh2d import CartesianMesh2D
from pvdfilewriter2d import PvdFileWriter2D

class ExplicitHeatEquation:
	u0 = 1.0
	vectOne = np.full((2), 1.0, dtype=np.double)

	def __init__(self, mesh):
		self.__mesh = mesh
		self.__nbNodes = mesh.nbNodes
		self.__nbCells = mesh.nbCells
		self.__nbFaces = mesh.nbFaces

	def jsonInit(self, jsonContent):
		self.__outputPath = jsonContent["outputPath"]
		self.__writer = PvdFileWriter2D("ExplicitHeatEquation", self.__outputPath)
		self.outputPeriod = jsonContent["outputPeriod"]
		self.lastDump = -sys.maxsize - 1
		self.n = 0
		self.stopTime = jsonContent["stopTime"]
		self.maxIterations = jsonContent["maxIterations"]
		self.delta_t = 0.001
		self.X = np.empty((self.__nbNodes, 2), dtype=np.double)
		self.Xc = np.empty((self.__nbCells, 2), dtype=np.double)
		self.u_n = np.empty((self.__nbCells), dtype=np.double)
		self.u_nplus1 = np.empty((self.__nbCells), dtype=np.double)
		self.V = np.empty((self.__nbCells), dtype=np.double)
		self.D = np.empty((self.__nbCells), dtype=np.double)
		self.faceLength = np.empty((self.__nbFaces), dtype=np.double)
		self.faceConductivity = np.empty((self.__nbFaces), dtype=np.double)
		self.alpha = np.empty((self.__nbCells, self.__nbCells), dtype=np.double)

		# Copy node coordinates
		gNodes = mesh.geometry.nodes
		for rNodes in range(self.__nbNodes):
			self.X[rNodes] = gNodes[rNodes]

	"""
	 Job computeFaceLength called @1.0 in simulate method.
	 In variables: X
	 Out variables: faceLength
	"""
	def _computeFaceLength(self):
		for fFaces in range(self.__nbFaces):
			fId = fFaces
			reduction0 = 0.0
			nodesOfFaceF = mesh.getNodesOfFace(fId)
			nbNodesOfFaceF = len(nodesOfFaceF)
			for pNodesOfFaceF in range(nbNodesOfFaceF):
				pId = nodesOfFaceF[pNodesOfFaceF]
				pPlus1Id = nodesOfFaceF[(pNodesOfFaceF+1+nbNodesOfFaceF)%nbNodesOfFaceF]
				pNodes = pId
				pPlus1Nodes = pPlus1Id
				reduction0 = self.__sumR0(reduction0, self.__norm(self.__operatorSub(self.X[pNodes], self.X[pPlus1Nodes])))
			self.faceLength[fFaces] = 0.5 * reduction0

	"""
	 Job computeTn called @1.0 in executeTimeLoopN method.
	 In variables: delta_t, t_n
	 Out variables: t_nplus1
	"""
	def _computeTn(self):
		self.t_nplus1 = self.t_n + self.delta_t

	"""
	 Job computeV called @1.0 in simulate method.
	 In variables: X
	 Out variables: V
	"""
	def _computeV(self):
		for cCells in range(self.__nbCells):
			cId = cCells
			reduction0 = 0.0
			nodesOfCellC = mesh.getNodesOfCell(cId)
			nbNodesOfCellC = len(nodesOfCellC)
			for pNodesOfCellC in range(nbNodesOfCellC):
				pId = nodesOfCellC[pNodesOfCellC]
				pPlus1Id = nodesOfCellC[(pNodesOfCellC+1+nbNodesOfCellC)%nbNodesOfCellC]
				pNodes = pId
				pPlus1Nodes = pPlus1Id
				reduction0 = self.__sumR0(reduction0, self.__det(self.X[pNodes], self.X[pPlus1Nodes]))
			self.V[cCells] = 0.5 * reduction0

	"""
	 Job initD called @1.0 in simulate method.
	 In variables: 
	 Out variables: D
	"""
	def _initD(self):
		for cCells in range(self.__nbCells):
			self.D[cCells] = 1.0

	"""
	 Job initTime called @1.0 in simulate method.
	 In variables: 
	 Out variables: t_n0
	"""
	def _initTime(self):
		self.t_n0 = 0.0

	"""
	 Job initXc called @1.0 in simulate method.
	 In variables: X
	 Out variables: Xc
	"""
	def _initXc(self):
		for cCells in range(self.__nbCells):
			cId = cCells
			reduction0 = np.full((2), 0.0, dtype=np.double)
			nodesOfCellC = mesh.getNodesOfCell(cId)
			nbNodesOfCellC = len(nodesOfCellC)
			for pNodesOfCellC in range(nbNodesOfCellC):
				pId = nodesOfCellC[pNodesOfCellC]
				pNodes = pId
				reduction0 = self.__sumR1(reduction0, self.X[pNodes])
			self.Xc[cCells] = self.__operatorMult(0.25, reduction0)

	"""
	 Job updateU called @1.0 in executeTimeLoopN method.
	 In variables: alpha, u_n
	 Out variables: u_nplus1
	"""
	def _updateU(self):
		for cCells in range(self.__nbCells):
			cId = cCells
			reduction0 = 0.0
			neighbourCellsC = mesh.getNeighbourCells(cId)
			nbNeighbourCellsC = len(neighbourCellsC)
			for dNeighbourCellsC in range(nbNeighbourCellsC):
				dId = neighbourCellsC[dNeighbourCellsC]
				dCells = dId
				reduction0 = self.__sumR0(reduction0, self.alpha[cCells, dCells] * self.u_n[dCells])
			self.u_nplus1[cCells] = self.alpha[cCells, cCells] * self.u_n[cCells] + reduction0

	"""
	 Job computeDeltaTn called @2.0 in simulate method.
	 In variables: D, V
	 Out variables: delta_t
	"""
	def _computeDeltaTn(self):
		reduction0 = sys.float_info.max
		for cCells in range(self.__nbCells):
			reduction0 = self.__minR0(reduction0, self.V[cCells] / self.D[cCells])
		self.delta_t = reduction0 * 0.24

	"""
	 Job computeFaceConductivity called @2.0 in simulate method.
	 In variables: D
	 Out variables: faceConductivity
	"""
	def _computeFaceConductivity(self):
		for fFaces in range(self.__nbFaces):
			fId = fFaces
			reduction0 = 1.0
			cellsOfFaceF = mesh.getCellsOfFace(fId)
			nbCellsOfFaceF = len(cellsOfFaceF)
			for c1CellsOfFaceF in range(nbCellsOfFaceF):
				c1Id = cellsOfFaceF[c1CellsOfFaceF]
				c1Cells = c1Id
				reduction0 = self.__prodR0(reduction0, self.D[c1Cells])
			reduction1 = 0.0
			cellsOfFaceF = mesh.getCellsOfFace(fId)
			nbCellsOfFaceF = len(cellsOfFaceF)
			for c2CellsOfFaceF in range(nbCellsOfFaceF):
				c2Id = cellsOfFaceF[c2CellsOfFaceF]
				c2Cells = c2Id
				reduction1 = self.__sumR0(reduction1, self.D[c2Cells])
			self.faceConductivity[fFaces] = 2.0 * reduction0 / reduction1

	"""
	 Job initU called @2.0 in simulate method.
	 In variables: Xc, u0, vectOne
	 Out variables: u_n
	"""
	def _initU(self):
		for cCells in range(self.__nbCells):
			if self.__norm(self.__operatorSub(self.Xc[cCells], self.vectOne)) < 0.5:
				self.u_n[cCells] = self.u0
			else:
				self.u_n[cCells] = 0.0

	"""
	 Job setUpTimeLoopN called @2.0 in simulate method.
	 In variables: t_n0
	 Out variables: t_n
	"""
	def _setUpTimeLoopN(self):
		self.t_n = self.t_n0

	"""
	 Job computeAlphaCoeff called @3.0 in simulate method.
	 In variables: V, Xc, delta_t, faceConductivity, faceLength
	 Out variables: alpha
	"""
	def _computeAlphaCoeff(self):
		for cCells in range(self.__nbCells):
			cId = cCells
			alpha_Diag = 0.0
			neighbourCellsC = mesh.getNeighbourCells(cId)
			nbNeighbourCellsC = len(neighbourCellsC)
			for dNeighbourCellsC in range(nbNeighbourCellsC):
				dId = neighbourCellsC[dNeighbourCellsC]
				dCells = dId
				fId = mesh.getCommonFace(cId, dId)
				fFaces = fId
				alpha_ExtraDiag = self.delta_t / self.V[cCells] * (self.faceLength[fFaces] * self.faceConductivity[fFaces]) / self.__norm(self.__operatorSub(self.Xc[cCells], self.Xc[dCells]))
				self.alpha[cCells, dCells] = alpha_ExtraDiag
				alpha_Diag = alpha_Diag + alpha_ExtraDiag
			self.alpha[cCells, cCells] = 1 - alpha_Diag

	"""
	 Job executeTimeLoopN called @4.0 in simulate method.
	 In variables: lastDump, maxIterations, n, outputPeriod, stopTime, t_n, t_nplus1, u_n
	 Out variables: t_nplus1, u_nplus1
	"""
	def _executeTimeLoopN(self):
		self.n = 0
		self.t_n = 0.0
		continueLoop = True
		while continueLoop:
			self.n += 1
			print("START ITERATION n: %5d - t: %5.5f - delta_t: %5.5f\n" % (self.n, self.t_n, self.delta_t))
			if (self.n >= self.lastDump + self.outputPeriod):
				self.__dumpVariables(self.n)
		
			self._computeTn() # @1.0
			self._updateU() # @1.0
		
			# Evaluate loop condition with variables at time n
			continueLoop = (self.t_nplus1 < self.stopTime  and  self.n + 1 < self.maxIterations)
		
			self.t_n = self.t_nplus1
			for i1Cells in range(self.__nbCells):
				self.u_n[i1Cells] = self.u_nplus1[i1Cells]
		
		print("FINAL TIME: %5.5f - delta_t: %5.5f\n" % (self.t_n, self.delta_t))
		self.__dumpVariables(self.n+1);

	def __norm(self, a):
		return math.sqrt(self.__dot(a, a))

	def __dot(self, a, b):
		result = 0.0
		for i in range(len(a)):
			result = result + a[i] * b[i]
		return result

	def __det(self, a, b):
		return (a[0] * b[1] - a[1] * b[0])

	def __sumR1(self, a, b):
		return self.__operatorAdd(a, b)

	def __minR0(self, a, b):
		return min(a, b)

	def __sumR0(self, a, b):
		return a + b

	def __prodR0(self, a, b):
		return a * b

	def __operatorAdd(self, a, b):
		result = np.empty((len(a)), dtype=np.double)
		for ix0 in range(len(a)):
			result[ix0] = a[ix0] + b[ix0]
		return result

	def __operatorMult(self, a, b):
		result = np.empty((len(b)), dtype=np.double)
		for ix0 in range(len(b)):
			result[ix0] = a * b[ix0]
		return result

	def __operatorSub(self, a, b):
		result = np.empty((len(a)), dtype=np.double)
		for ix0 in range(len(a)):
			result[ix0] = a[ix0] - b[ix0]
		return result

	def simulate(self):
		print("Start execution of explicitHeatEquation")
		self._computeFaceLength() # @1.0
		self._computeV() # @1.0
		self._initD() # @1.0
		self._initTime() # @1.0
		self._initXc() # @1.0
		self._computeDeltaTn() # @2.0
		self._computeFaceConductivity() # @2.0
		self._initU() # @2.0
		self._setUpTimeLoopN() # @2.0
		self._computeAlphaCoeff() # @3.0
		self._executeTimeLoopN() # @4.0
		print("End of execution of explicitHeatEquation")

	def __dumpVariables(self, iteration):
		if not self.__writer.disabled:
			quads = mesh.geometry.quads
			self.__writer.startVtpFile(iteration, self.t_n, self.X, quads)
			self.__writer.openNodeData()
			self.__writer.closeNodeData()
			self.__writer.openCellData()
			self.__writer.openCellArray("Temperature", 0)
			for i in range(self.__nbCells):
				self.__writer.write(self.u_n[i])
			self.__writer.closeCellArray()
			self.__writer.closeCellData()
			self.__writer.closeVtpFile()
			self.lastDump = self.n

if __name__ == '__main__':
	args = sys.argv[1:]
	
	if len(args) == 1:
		f = open(args[0])
		data = json.load(f)
		f.close()

		# Mesh instanciation
		mesh = CartesianMesh2D()
		mesh.jsonInit(data["mesh"])

		# Module instanciation
		explicitHeatEquation = ExplicitHeatEquation(mesh)
		explicitHeatEquation.jsonInit(data["explicitHeatEquation"])

		# Start simulation
		explicitHeatEquation.simulate()
	else:
		print("[ERROR] Wrong number of arguments: expected 1, actual " + str(len(args)), file=sys.stderr)
		print("        Expecting user data file name, for example ExplicitHeatEquation.json", file=sys.stderr)
		exit(1)
