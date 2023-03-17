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

class FUClassAAGenerator : public IAAGenerator
{
public:
	// TODO: Probably should just make this a factory pattern and hide this in the construct function
	static void RegisterNew(FUClassAAGenerator* generator);

	FUClassAAGenerator(UClass* uclass, const FString& headerFileName);
	virtual ~FUClassAAGenerator() override;

	/** FBaseGenerator interface */
	virtual bool CanExport()const  override;
	virtual void ExportToMemory() override;
	virtual void FinalizeMemory() override;
	virtual FString GetKey() const override { return GetClassName(); }
	virtual FString GetClassName() const override;
	virtual Type GetType() const override { return Type::UClass; }

    virtual FString ExportName() const override;
	virtual FString ExportHeaderContent() const override;
	virtual FString ExportConversionRules() const override;
    virtual FString ExportTypeDeclarations() const override;
	virtual bool RequiresImplementation() const override;
	virtual FString ExportAdditionalIncludeDirectives() const override;

	void ExportDataMembersToMemory();
	void ExportFunctionMembersToMemory();

private:
	bool CanExportFunction(UFunction* InFunction);

	UClass* m_uclass;
	FString m_headerFilepath;
	AAGeneratorInitUtilities::ClassExportInfo m_exportInfo;
};
