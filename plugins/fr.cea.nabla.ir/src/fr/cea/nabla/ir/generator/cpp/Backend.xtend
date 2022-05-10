/*******************************************************************************
 * Copyright (c) 2022 CEA
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 * Contributors: see AUTHORS file
 *******************************************************************************/
package fr.cea.nabla.ir.generator.cpp

import fr.cea.nabla.ir.generator.jni.Jniable
import fr.cea.nabla.ir.ir.ExtensionProvider
import fr.cea.nabla.ir.ir.ExternFunction
import fr.cea.nabla.ir.transformers.CheckKokkosMultithreadLoops
import fr.cea.nabla.ir.transformers.IrTransformationStep
import fr.cea.nabla.ir.transformers.ReplaceReductions
import fr.cea.nabla.ir.transformers.SetMultithreadableLoops
import org.eclipse.xtend.lib.annotations.Accessors

abstract class Backend implements Jniable
{
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) String name
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) IrTransformationStep[] irTransformationSteps = #[]
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) CMakeContentProvider cmakeContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) TypeContentProvider typeContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) ExpressionContentProvider expressionContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) InstructionContentProvider instructionContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) FunctionContentProvider functionContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) TraceContentProvider traceContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) IncludesContentProvider includesContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) JsonContentProvider jsonContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) JobCallerContentProvider jobCallerContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) JobContentProvider jobContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) MainContentProvider mainContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) IrModuleContentProvider irModuleContentProvider
	@Accessors(PUBLIC_GETTER, PROTECTED_SETTER) DefaultExtensionProviderContentProvider defaultExtensionProviderContentProvider

	override getJniDefinitionContent(ExternFunction f, ExtensionProvider provider)
	{
		functionContentProvider.getJniDefinitionContent(f, provider)
	}
}

class SequentialBackend extends Backend
{
	new()
	{
		name = 'Sequential'
		irTransformationSteps = #[new ReplaceReductions(true)]
		cmakeContentProvider = new CMakeContentProvider
		typeContentProvider = new StlThreadTypeContentProvider
		expressionContentProvider = new ExpressionContentProvider(typeContentProvider)
		instructionContentProvider = new SequentialInstructionContentProvider(typeContentProvider, expressionContentProvider)
		functionContentProvider = new FunctionContentProvider(typeContentProvider, expressionContentProvider, instructionContentProvider)
		traceContentProvider = new TraceContentProvider
		includesContentProvider = new IncludesContentProvider
		jsonContentProvider = new JsonContentProvider(expressionContentProvider, instructionContentProvider)
		jobCallerContentProvider = new JobCallerContentProvider
		jobContentProvider = new StlThreadJobContentProvider(traceContentProvider, expressionContentProvider, instructionContentProvider, jobCallerContentProvider, jsonContentProvider)
		mainContentProvider = new MainContentProvider(jsonContentProvider)
		irModuleContentProvider = new IrModuleContentProvider(traceContentProvider, includesContentProvider, functionContentProvider, jobContentProvider, typeContentProvider, expressionContentProvider, jsonContentProvider, jobCallerContentProvider, mainContentProvider)
		defaultExtensionProviderContentProvider = new DefaultExtensionProviderContentProvider(includesContentProvider, functionContentProvider)
	}
}

class StlThreadBackend extends Backend
{
	new()
	{
		name = 'StlThread'
		irTransformationSteps = #[new SetMultithreadableLoops]
		cmakeContentProvider = new StlThreadCMakeContentProvider
		typeContentProvider = new StlThreadTypeContentProvider
		expressionContentProvider = new ExpressionContentProvider(typeContentProvider)
		instructionContentProvider = new StlThreadInstructionContentProvider(typeContentProvider, expressionContentProvider)
		functionContentProvider = new FunctionContentProvider(typeContentProvider, expressionContentProvider, instructionContentProvider)
		traceContentProvider = new TraceContentProvider
		includesContentProvider = new StlThreadIncludesContentProvider
		jsonContentProvider = new JsonContentProvider(expressionContentProvider, instructionContentProvider)
		jobCallerContentProvider = new JobCallerContentProvider
		jobContentProvider = new StlThreadJobContentProvider(traceContentProvider, expressionContentProvider, instructionContentProvider, jobCallerContentProvider, jsonContentProvider)
		mainContentProvider = new MainContentProvider(jsonContentProvider)
		irModuleContentProvider = new IrModuleContentProvider(traceContentProvider, includesContentProvider, functionContentProvider, jobContentProvider, typeContentProvider, expressionContentProvider, jsonContentProvider, jobCallerContentProvider, mainContentProvider)
		defaultExtensionProviderContentProvider = new DefaultExtensionProviderContentProvider(includesContentProvider, functionContentProvider)
	}
}

class KokkosBackend extends Backend
{
	new()
	{
		name = 'Kokkos'
		irTransformationSteps = #[new SetMultithreadableLoops, new CheckKokkosMultithreadLoops]
		cmakeContentProvider = new KokkosCMakeContentProvider
		typeContentProvider = new KokkosTypeContentProvider
		expressionContentProvider = new ExpressionContentProvider(typeContentProvider)
		instructionContentProvider = new KokkosInstructionContentProvider(typeContentProvider, expressionContentProvider)
		functionContentProvider = new FunctionContentProvider(typeContentProvider, expressionContentProvider, instructionContentProvider)
		traceContentProvider = new KokkosTraceContentProvider
		includesContentProvider = new KokkosIncludesContentProvider
		jsonContentProvider = new JsonContentProvider(expressionContentProvider, instructionContentProvider)
		jobCallerContentProvider = new JobCallerContentProvider
		jobContentProvider = new KokkosJobContentProvider(traceContentProvider, expressionContentProvider, instructionContentProvider, jobCallerContentProvider, jsonContentProvider)
		mainContentProvider = new KokkosMainContentProvider(jsonContentProvider)
		irModuleContentProvider = new IrModuleContentProvider(traceContentProvider, includesContentProvider, functionContentProvider, jobContentProvider, typeContentProvider, expressionContentProvider, jsonContentProvider, jobCallerContentProvider, mainContentProvider)
		defaultExtensionProviderContentProvider = new DefaultExtensionProviderContentProvider(includesContentProvider, functionContentProvider)
	}
}

class KokkosTeamThreadBackend extends Backend
{
	new()
	{
		name = 'Kokkos Team Thread'
		irTransformationSteps = #[new SetMultithreadableLoops, new CheckKokkosMultithreadLoops]
		cmakeContentProvider = new KokkosCMakeContentProvider
		typeContentProvider = new KokkosTypeContentProvider
		expressionContentProvider = new ExpressionContentProvider(typeContentProvider)
		instructionContentProvider = new KokkosTeamThreadInstructionContentProvider(typeContentProvider, expressionContentProvider)
		functionContentProvider = new FunctionContentProvider(typeContentProvider, expressionContentProvider, instructionContentProvider)
		traceContentProvider = new KokkosTraceContentProvider
		includesContentProvider = new KokkosIncludesContentProvider
		jsonContentProvider = new JsonContentProvider(expressionContentProvider, instructionContentProvider)
		jobCallerContentProvider = new KokkosTeamThreadJobCallerContentProvider
		jobContentProvider = new KokkosTeamThreadJobContentProvider(traceContentProvider, expressionContentProvider, instructionContentProvider, jobCallerContentProvider, jsonContentProvider)
		mainContentProvider = new KokkosMainContentProvider(jsonContentProvider)
		irModuleContentProvider = new KokkosTeamThreadIrModuleContentProvider(traceContentProvider, includesContentProvider, functionContentProvider, jobContentProvider, typeContentProvider, expressionContentProvider, jsonContentProvider, jobCallerContentProvider, mainContentProvider)
		defaultExtensionProviderContentProvider = new DefaultExtensionProviderContentProvider(includesContentProvider, functionContentProvider)
	}
}

class OpenMpBackend extends Backend
{
	new()
	{
		name = 'OpenMP'
		irTransformationSteps = #[new SetMultithreadableLoops]
		cmakeContentProvider = new OpenMpCMakeContentProvider
		typeContentProvider = new StlThreadTypeContentProvider
		expressionContentProvider = new ExpressionContentProvider(typeContentProvider)
		instructionContentProvider = new OpenMpInstructionContentProvider(typeContentProvider, expressionContentProvider)
		functionContentProvider = new FunctionContentProvider(typeContentProvider, expressionContentProvider, instructionContentProvider)
		traceContentProvider = new TraceContentProvider
		includesContentProvider = new OpenMpIncludesContentProvider
		jsonContentProvider = new JsonContentProvider(expressionContentProvider, instructionContentProvider)
		jobCallerContentProvider = new JobCallerContentProvider
		jobContentProvider = new StlThreadJobContentProvider(traceContentProvider, expressionContentProvider, instructionContentProvider, jobCallerContentProvider, jsonContentProvider)
		mainContentProvider = new MainContentProvider(jsonContentProvider)
		irModuleContentProvider = new IrModuleContentProvider(traceContentProvider, includesContentProvider, functionContentProvider, jobContentProvider, typeContentProvider, expressionContentProvider, jsonContentProvider, jobCallerContentProvider, mainContentProvider)
		defaultExtensionProviderContentProvider = new DefaultExtensionProviderContentProvider(includesContentProvider, functionContentProvider)
	}
}