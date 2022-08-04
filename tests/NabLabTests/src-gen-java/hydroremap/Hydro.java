/* DO NOT EDIT THIS FILE - it is machine generated */

package hydroremap;

import java.io.FileReader;
import java.io.IOException;
import java.util.stream.IntStream;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.google.gson.JsonElement;

import fr.cea.nabla.javalib.mesh.*;

public final class Hydro
{
	// Mesh and mesh variables
	private final CartesianMesh2D mesh;
	private final int nbNodes;
	private final int nbCells;
	// Additional modules
	protected R1 r1;
	protected R2 r2;

	// Options and global variables
	int maxIter;
	double maxTime;
	double delta_t;
	static final double t = 0.0;
	double[][] X;
	double[] hv1;
	double[] hv2;
	double[] hv3;
	double[] hv4;
	double[] hv5;
	double[] hv6;
	double[] hv7;

	public Hydro(CartesianMesh2D aMesh)
	{
		// Mesh and mesh variables initialization
		mesh = aMesh;
		nbNodes = mesh.getNbNodes();
		nbCells = mesh.getNbCells();
	}

	public void jsonInit(final String jsonContent)
	{
		final Gson gson = new Gson();
		final JsonObject options = gson.fromJson(jsonContent, JsonObject.class);
		assert options.has("maxIter") : "No maxIter option";
		final JsonElement valueof_maxIter = options.get("maxIter");
		assert(valueof_maxIter.isJsonPrimitive());
		maxIter = valueof_maxIter.getAsJsonPrimitive().getAsInt();
		assert options.has("maxTime") : "No maxTime option";
		final JsonElement valueof_maxTime = options.get("maxTime");
		assert(valueof_maxTime.isJsonPrimitive());
		maxTime = valueof_maxTime.getAsJsonPrimitive().getAsDouble();
		assert options.has("delta_t") : "No delta_t option";
		final JsonElement valueof_delta_t = options.get("delta_t");
		assert(valueof_delta_t.isJsonPrimitive());
		delta_t = valueof_delta_t.getAsJsonPrimitive().getAsDouble();
		X = new double[nbNodes][2];
		hv1 = new double[nbCells];
		hv2 = new double[nbCells];
		hv3 = new double[nbCells];
		hv4 = new double[nbCells];
		hv5 = new double[nbCells];
		hv6 = new double[nbCells];
		hv7 = new double[nbCells];

		// Copy node coordinates
		double[][] gNodes = mesh.getGeometry().getNodes();
		IntStream.range(0, nbNodes).parallel().forEach(rNodes ->
		{
			X[rNodes][0] = gNodes[rNodes][0];
			X[rNodes][1] = gNodes[rNodes][1];
		});
	}

	/**
	 * Job iniHv1 called @1.0 in simulate method.
	 * In variables: 
	 * Out variables: hv1
	 */
	protected void iniHv1()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			hv1[cCells] = 2.0;
		});
	}

	/**
	 * Job iniHv2 called @1.0 in simulate method.
	 * In variables: 
	 * Out variables: hv2
	 */
	protected void iniHv2()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			hv2[cCells] = 0.0;
		});
	}

	/**
	 * Job hj1 called @2.0 in simulate method.
	 * In variables: hv2
	 * Out variables: hv3
	 */
	protected void hj1()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			hv3[cCells] = hv2[cCells] + 1.0;
		});
	}

	/**
	 * Job oracleHv1 called @2.0 in simulate method.
	 * In variables: hv1
	 * Out variables: 
	 */
	protected void oracleHv1()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			final boolean testHv1 = assertEquals(2.0, hv1[cCells]);
		});
	}

	/**
	 * Job oracleHv2 called @2.0 in simulate method.
	 * In variables: hv2
	 * Out variables: 
	 */
	protected void oracleHv2()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			final boolean testHv2 = assertEquals(0.0, hv2[cCells]);
		});
	}

	/**
	 * Job hj2 called @3.0 in simulate method.
	 * In variables: hv3
	 * Out variables: hv5
	 */
	protected void hj2()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			hv5[cCells] = hv3[cCells] + 2.0;
		});
	}

	/**
	 * Job oracleHv3 called @3.0 in simulate method.
	 * In variables: hv3
	 * Out variables: 
	 */
	protected void oracleHv3()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			final boolean testHv3 = assertEquals(1.0, hv3[cCells]);
		});
	}

	/**
	 * Job oracleHv4 called @3.0 in simulate method.
	 * In variables: hv4
	 * Out variables: 
	 */
	protected void oracleHv4()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			final boolean testHv4 = assertEquals(4.0, hv4[cCells]);
		});
	}

	/**
	 * Job oracleHv5 called @4.0 in simulate method.
	 * In variables: hv5
	 * Out variables: 
	 */
	protected void oracleHv5()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			final boolean testHv5 = assertEquals(3.0, hv5[cCells]);
		});
	}

	/**
	 * Job hj3 called @5.0 in simulate method.
	 * In variables: hv4, hv5, hv6
	 * Out variables: hv7
	 */
	protected void hj3()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			hv7[cCells] = hv4[cCells] + hv5[cCells] + hv6[cCells];
		});
	}

	/**
	 * Job oracleHv6 called @5.0 in simulate method.
	 * In variables: hv6
	 * Out variables: 
	 */
	protected void oracleHv6()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			final boolean testHv6 = assertEquals(6.0, hv6[cCells]);
		});
	}

	/**
	 * Job oracleHv7 called @6.0 in simulate method.
	 * In variables: hv7
	 * Out variables: 
	 */
	protected void oracleHv7()
	{
		IntStream.range(0, nbCells).parallel().forEach(cCells ->
		{
			final boolean testHv7 = assertEquals(13.0, hv7[cCells]);
		});
	}

	private static boolean assertEquals(double expected, double actual)
	{
		final boolean ret = (expected == actual);
		if (!ret)
			throw new RuntimeException("** Assertion failed");
		return ret;
	}

	public void simulate()
	{
		System.out.println("Start execution of hydro");
		iniHv1(); // @1.0
		iniHv2(); // @1.0
		hj1(); // @2.0
		oracleHv1(); // @2.0
		oracleHv2(); // @2.0
		r1.rj1(); // @2.0
		hj2(); // @3.0
		oracleHv3(); // @3.0
		oracleHv4(); // @3.0
		r2.rj1(); // @3.0
		r1.rj2(); // @3.0
		oracleHv5(); // @4.0
		r2.rj2(); // @4.0
		hj3(); // @5.0
		oracleHv6(); // @5.0
		oracleHv7(); // @6.0
		System.out.println("End of execution of hydro");
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
			Hydro hydro = new Hydro(mesh);
			assert o.has("hydro") : "No hydro option";
			hydro.jsonInit(o.get("hydro").toString());
			R1 r1 = new R1(mesh);
			assert o.has("r1") : "No r1 option";
			r1.jsonInit(o.get("r1").toString());
			r1.setMainModule(hydro);
			R2 r2 = new R2(mesh);
			assert o.has("r2") : "No r2 option";
			r2.jsonInit(o.get("r2").toString());
			r2.setMainModule(hydro);

			// Start simulation
			hydro.simulate();
		}
		else
		{
			System.err.println("[ERROR] Wrong number of arguments: expected 1, actual " + args.length);
			System.err.println("        Expecting user data file name, for example HydroRemap.json");
			System.exit(1);
		}
	}
};
