package fr.cea.nabla.tests

import com.google.inject.Inject
import fr.cea.nabla.ir.interpreter.NV0Real
import org.eclipse.xtext.testing.InjectWith
import org.eclipse.xtext.testing.XtextRunner
import org.junit.Test
import org.junit.runner.RunWith

import static fr.cea.nabla.tests.TestUtils.*

import static extension fr.cea.nabla.ir.interpreter.ModuleInterpreter.*

@RunWith(XtextRunner)
@InjectWith(NablaInjectorProvider)
class ModuleInterpreterTest 
{
	@Inject CompilationChainHelper compilationHelper

	@Test
	def void testInterpreteModule()
	{
		val model = TestUtils::getTestModule(10, 10, 0.2, 2000)
		+
		'''
		InitT: t = 0.;
		ComputeTn: t^{n+1} = t + 0.01;
		'''
		
		println(model)

		val irModule = compilationHelper.getIrModule(model, TestUtils::testGenModel)
		val context = irModule.interprete
		assertVariableValueInContext(irModule, context, "t", new NV0Real(0.2))
	}
}