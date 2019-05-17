/*******************************************************************************
 * Copyright (c) 2018 CEA
 * This program and the accompanying materials are made available under the 
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 * 	Benoit Lelandais - initial implementation
 * 	Marie-Pierre Oudot - initial implementation
 * 	Jean-Sylvain Camier - Nabla generation support
 *******************************************************************************/
package fr.cea.nabla.ir.generator.java

import fr.cea.nabla.ir.ir.ArrayVariable
import fr.cea.nabla.ir.ir.ScalarVariable

import static extension fr.cea.nabla.ir.generator.java.Ir2JavaUtils.*

class VariableExtensions 
{
	static def dispatch getJavaType(ScalarVariable it) 
	{ 
		type.javaType
	}
	
	static def dispatch getJavaType(ArrayVariable it)
	{
		var t = getType.javaType 
		for (d : dimensions) t += '[]'
		return t
	}
}