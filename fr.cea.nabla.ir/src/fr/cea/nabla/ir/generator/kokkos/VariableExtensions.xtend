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
package fr.cea.nabla.ir.generator.kokkos

import fr.cea.nabla.ir.ir.ArrayVariable
import fr.cea.nabla.ir.ir.ScalarVariable

import static extension fr.cea.nabla.ir.generator.kokkos.Ir2KokkosUtils.*

class VariableExtensions 
{
	static def dispatch getKokkosType(ScalarVariable it) 
	{ 
		type.kokkosType
	}
	
	static def dispatch getKokkosType(ArrayVariable it)
	{
		getType.kokkosType + dimensions.map['*'].join
	}
}