
string GetItemDescriptorsToString(ref ref_Id_Idx)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	string result = "";
	aref descriptors = GetItemDescriptors(refItem);
	for (int i = 0; i < GetAttributesNum(descriptors); i++)
	{
		aref attributeN = GetAttributeN(descriptors, i);
		result += GetDescriptorName(attributeN, refItem) + " ";
	}

	return result;
}

string GetDescriptorName(aref descriptor, ref rObject)
{
	string name = GetAttributeName(descriptor);
	return DLG_Convert("descriptor_" + name, "ItemsDescriptors.txt", rObject);
}

string GetDescriptorDescribe(aref descriptor, ref rObject)
{
	string name = GetAttributeName(descriptor);
	return DLG_Convert("descriptor_descr_" + name, "ItemsDescriptors.txt", rObject);
}

aref GetItemDescriptors(ref ref_Id_Idx)
{
	ref item = FindItem_VT(&ref_Id_Idx);
	aref descriptors;
	makearef(descriptors, item.descriptors);
	return descriptors;
}

void SetDescriptorsTooltip(string sCurrentNode, ref header, ref text, ref badText, ref goodText, ref rObject)
{
	if (!HasSubStr(sCurrentNode, "DESCRIPTOR_")) return;

	aref descriptors = GetItemDescriptors(rObject);
	int descriptorNum = sti(FindStringAfterChar(sCurrentNode, "_")) - 1;
	aref descriptor = GetAttributeN(descriptors, descriptorNum);
	header = GetDescriptorName(descriptor, rObject);
	text = GetDescriptorDescribe(descriptor, rObject)
	badText = "";
	goodText = "";
}

int FillUpDescriptors(ref rObject)
{
	aref descriptors, descriptor;
	makearef(descriptors, rObject.descriptors);
	int descriptorsQty = GetAttributesNum(descriptors);
	for(int x=0; x<4;x++)
	{
		string nodeName = "DESCRIPTOR_" + (x+1);
		string nodeName2 = nodeName + "_VALUE";
		if (x < descriptorsQty)
		{
			SetNodeUsing(nodeName, true);
			SetNodeUsing(nodeName2, true);
			descriptor = GetAttributeN(descriptors, x);
			SetFormatedText(nodeName2, GetDescriptorName(descriptor, rObject));
			SetVAligmentFormatedText(nodeName2);
		}
		else
		{
			SetNodeUsing(nodeName, false);
			SetNodeUsing(nodeName2, false);
		}
	}

	return descriptorsQty;
}