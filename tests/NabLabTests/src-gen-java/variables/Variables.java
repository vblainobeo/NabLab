/* DO NOT EDIT THIS FILE - it is machine generated */

package variables;

import java.io.FileReader;
import java.io.IOException;
import java.util.stream.IntStream;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.google.gson.JsonElement;

import fr.cea.nabla.javalib.mesh.*;

public final class Variables
{
	// Mesh and mesh variables
	private final CartesianMesh2D mesh;
	private final int nbNodes;
	// Options and global variables
	static final double maxTime = 0.1;
	static final int maxIter = 500;
	static final double deltat = 1.0;
	static final double t = 0.0;
	double[][] X;
	int optDim;
	double[] optVect1;
	double[] optVect2;
	double[] optVect3;
	static final int constexprDim = 2;
	static final double[] constexprVec = new double[] {1.1, 1.1};
	double[] varVec;
	int checkDynamicDim;
	double[] dynamicVec;

	public Variables(CartesianMesh2D aMesh)
	{
		// Mesh and mesh variables initialization
		mesh = aMesh;
		nbNodes = mesh.getNbNodes();
	}

	public void jsonInit(final String jsonContent)
	{
		final Gson gson = new Gson();
		final JsonObject options = gson.fromJson(jsonContent, JsonObject.class);
		X = new double[nbNodes][2];
		assert options.has("optDim") : "No optDim option";
		final JsonElement valueof_optDim = options.get("optDim");
		assert(valueof_optDim.isJsonPrimitive());
		optDim = valueof_optDim.getAsJsonPrimitive().getAsInt();
		optVect1 = new double[2];
		assert options.has("optVect1") : "No optVect1 option";
		final JsonElement valueof_optVect1 = options.get("optVect1");
		assert(valueof_optVect1.isJsonArray());
		assert(valueof_optVect1.getAsJsonArray().size() == 2);
		for (int i1=0 ; i1<2 ; i1++)
		{
			assert(valueof_optVect1.getAsJsonArray().get(i1).isJsonPrimitive());
			optVect1[i1] = valueof_optVect1.getAsJsonArray().get(i1).getAsJsonPrimitive().getAsDouble();
		}
		optVect2 = new double[2];
		assert options.has("optVect2") : "No optVect2 option";
		final JsonElement valueof_optVect2 = options.get("optVect2");
		assert(valueof_optVect2.isJsonArray());
		assert(valueof_optVect2.getAsJsonArray().size() == 2);
		for (int i1=0 ; i1<2 ; i1++)
		{
			assert(valueof_optVect2.getAsJsonArray().get(i1).isJsonPrimitive());
			optVect2[i1] = valueof_optVect2.getAsJsonArray().get(i1).getAsJsonPrimitive().getAsDouble();
		}
		optVect3 = new double[2];
		optVect3 = operatorAdd(optVect1, optVect2);
		varVec = new double[constexprDim];
		varVec = new double[] {1.0, 1.0};
		dynamicVec = new double[optDim];

		// Copy node coordinates
		double[][] gNodes = mesh.getGeometry().getNodes();
		IntStream.range(0, nbNodes).parallel().forEach(rNodes ->
		{
			X[rNodes][0] = gNodes[rNodes][0];
			X[rNodes][1] = gNodes[rNodes][1];
		});
	}

	/**
	 * Job dynamicVecInitialization called @1.0 in simulate method.
	 * In variables: optDim
	 * Out variables: checkDynamicDim, dynamicVec
	 */
	protected void dynamicVecInitialization()
	{
		int cpt = 0;
		for (int i=0; i<optDim; i++)
		{
			cpt = cpt + 1;
			dynamicVec[i] = 3.3;
		}
		checkDynamicDim = cpt;
	}

	/**
	 * Job varVecInitialization called @1.0 in simulate method.
	 * In variables: constexprDim
	 * Out variables: varVec
	 */
	protected void varVecInitialization()
	{
		varVec = new double[] {2.2, 2.2};
	}

	/**
	 * Job oracle called @2.0 in simulate method.
	 * In variables: checkDynamicDim, constexprDim, constexprVec, optDim, optVect1, optVect2, optVect3, varVec
	 * Out variables: 
	 */
	protected void oracle()
	{
		final boolean testOptDim = assertEquals(2, optDim);
		final boolean testOptVect1 = assertEquals(new double[] {1.0, 1.0}, optVect1);
		final boolean testOptVect2 = assertEquals(new double[] {2.0, 2.0}, optVect2);
		final boolean testOptVect3 = assertEquals(new double[] {3.0, 3.0}, optVect3);
		final boolean testConstexprDim = assertEquals(2, constexprDim);
		final boolean testConstexprVec = assertEquals(new double[] {1.1, 1.1}, constexprVec);
		final boolean testVarVec = assertEquals(new double[] {2.2, 2.2}, varVec);
		final boolean testDynamicVecLength = assertEquals(2, checkDynamicDim);
	}

	private static boolean assertEquals(int expected, int actual)
	{
		final boolean ret = (expected == actual);
		if (!ret)
			throw new RuntimeException("** Assertion failed");
		return ret;
	}

	private static boolean assertEquals(double[] expected, double[] actual)
	{
		for (int i=0; i<expected.length; i++)
		{
			if (expected[i] != actual[i])
				throw new RuntimeException("** Assertion failed");
		}
		return true;
	}

	private static double[] operatorAdd(double[] a, double[] b)
	{
		double[] result = new double[a.length];
		for (int ix0=0; ix0<a.length; ix0++)
		{
			result[ix0] = a[ix0] + b[ix0];
		}
		return result;
	}

	public void simulate()
	{
		System.out.println("Start execution of variables");
		dynamicVecInitialization(); // @1.0
		varVecInitialization(); // @1.0
		oracle(); // @2.0
		System.out.println("End of execution of variables");
	}

	public static void main(String[] args) throws IOException
	{
		if (args.length == 1)
		{
			final String dataFileName = args[0];
			final Gson gson = new Gson();
			final JsonObject o = gson.fromJson(new FileReader(dataFileName), JsonObject.class);

			// Mesh instanciation
			assert o.has("mesh") : "No mesh option";
			CartesianMesh2D mesh = new CartesianMesh2D();
			mesh.jsonInit(o.get("mesh").toString());

			// Module instanciation(s)
			Variables variables = new Variables(mesh);
			assert o.has("variables") : "No variables option";
			variables.jsonInit(o.get("variables").toString());

			// Start simulation
			variables.simulate();
		}
		else
		{
			System.err.println("[ERROR] Wrong number of arguments: expected 1, actual " + args.length);
			System.err.println("        Expecting user data file name, for example Variables.json");
			System.exit(1);
		}
	}
};
