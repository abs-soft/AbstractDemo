/*
Copyright 2023 Abstract Software, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "IAAGenerator.h"
#include "AAGeneratorInitUtilities.h"

class TArrayAAGenerator : public IAAGenerator
{
public:
	TArrayAAGenerator(const AAGeneratorInitUtilities::ValueTypeQualifier* qualifier);
	virtual ~TArrayAAGenerator() override;

	/** FBaseGenerator interface */
	virtual FString GetKey() const override;
	virtual bool CanExport()const  override;
	virtual void ExportToMemory() override;
	virtual void FinalizeMemory() override;
	virtual FString GetClassName() const override;
	virtual Type GetType() const override { return Type::Array; }

	virtual FString ExportName() const override;
	virtual FString ExportHeaderContent() const override;
	virtual FString ExportConversionRules() const override;
	virtual FString ExportTypeDeclarations() const override;
	virtual bool RequiresImplementation() const override;
	virtual FString ExportAdditionalIncludeDirectives() const override;

	virtual FString ExportBlueprintFunctionLibraryForwardDecl() const override;
	virtual FString ExportBlueprintFunctionLibraryDeclarations() const override;
	virtual FString ExportBlueprintFunctionLibraryDefinitions() const override;

private:
	const AAGeneratorInitUtilities::ValueTypeQualifier* m_qualifier;
};
