/*******************************************************************************
 * Copyright (c) 2018 CEA
 * This program and the accompanying materials are made available under the 
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 * Contributors: see AUTHORS file
 *******************************************************************************/
package fr.cea.nabla.ui.hovers

import com.google.inject.Inject
import fr.cea.nabla.LabelServices
import fr.cea.nabla.nabla.Expression
import fr.cea.nabla.typing.ExpressionTypeProvider
import org.eclipse.emf.ecore.EObject
import org.eclipse.jface.internal.text.html.HTMLPrinter
import org.eclipse.jface.text.IRegion
import org.eclipse.jface.text.ITextViewer
import org.eclipse.xtext.resource.EObjectAtOffsetHelper
import org.eclipse.xtext.ui.editor.XtextSourceViewer
import org.eclipse.xtext.ui.editor.hover.html.DefaultEObjectHoverProvider
import org.eclipse.xtext.ui.editor.hover.html.XtextBrowserInformationControlInput
import org.eclipse.xtext.ui.editor.model.IXtextDocument

/**
 * Xtext supports hovers only for identifying features of model artifacts, i.e. the name of an object or crosslinks to other objects.
 * If you put the cursor on a binary operation operator for example, getFirstLine will not be called.
 * That is the reason why the method XtextBrowserInformationControlInput getHoverInfo is overriden.
 */
class NablaEObjectHoverProvider extends DefaultEObjectHoverProvider 
{
	@Inject extension ExpressionTypeProvider
	@Inject EObjectAtOffsetHelper eObjectAtOffsetHelper	
	EObject resolvedContainedObject

	override String getFirstLine(EObject o) 
	{
		if (resolvedContainedObject === null) 
			super.getFirstLine(o)
		else
		{
			val expression = resolvedContainedObject.expression
			if (expression === null || expression.eIsProxy) 
				super.getFirstLine(o)
			else 
				expression.buildLabel
		}
	}

	override XtextBrowserInformationControlInput getHoverInfo(EObject object, IRegion region, XtextBrowserInformationControlInput prev) 
	{
		if (resolvedContainedObject === null) 
			super.getHoverInfo(object, region, prev)
		else
		{
			val expression = resolvedContainedObject.expression
			if (expression === null || expression.eIsProxy) 
				super.getHoverInfo(object, region, prev)
			else 
			{
				val buffer = new StringBuilder(expression.buildLabel)
				HTMLPrinter.insertPageProlog(buffer, 0, getStyleSheet())
				HTMLPrinter.addPageEpilog(buffer)
				return new XtextBrowserInformationControlInput(prev, object, buffer.toString(), labelProvider)
			}
		}
	}

	override IInformationControlCreatorProvider getHoverInfo(EObject object, ITextViewer viewer, IRegion region)
	{
		if (viewer instanceof XtextSourceViewer)
		{
			val document = (viewer as XtextSourceViewer).document
			if(document instanceof IXtextDocument)
				resolvedContainedObject = (document as IXtextDocument).readOnly([state |
						eObjectAtOffsetHelper.resolveContainedElementAt(state, region.offset)
				])
		}
		super.getHoverInfo(object, viewer, region)
	}

	private def Expression getExpression(EObject o)
	{
		if (o instanceof Expression) o as Expression
		else if (o.eContainer !== null) o.eContainer.expression
		else null
	}

	private def buildLabel(Expression e)
	{
		val eType = e.typeFor
		'Expression <b>' + LabelServices.getLabel(e) + '</b> of type <b>' + eType?.label + '</b>'
	}
}