
string GetItemDescriptorsToString(ref ref_Id_Idx)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	string result = "";
	aref descriptors = GetItemDescriptors(refItem);
	for (int i = 0; i < GetAttributesNum(descriptors); i++)
	{
		aref attributeN = GetAttributeN(descriptors, i);
		result += GetConvertStrB("descriptor_" + GetAttributeName(attributeN), "ItemsDescriptors.txt") + " ";
	}

	return result;
}

aref GetItemDescriptors(ref ref_Id_Idx)
{
	ref item = FindItem_VT(&ref_Id_Idx);
	aref descriptors;
	makearef(descriptors, item.descriptors);
	return descriptors;
}

void SetDescriptorsTooltip(string sCurrentNode, string header, string text, string badText, string goodText, ref rObject)
{
	if (!HasSubStr(sCurrentNode, "DESCRIPTOR_")) return;

	aref descriptors = GetItemDescriptors(rObject);
	int descriptorNum = sti(FindStringAfterChar(sCurrentNode, "_")) - 1;
	aref descriptor = GetAttributeN(descriptors, descriptorNum);
	string descriptorId = GetAttributeName(descriptor);
	header = DLG_Convert("descriptor_" + descriptorId, "ItemsDescriptors.txt", rObject);
	text = DLG_Convert("descriptor_descr_" + descriptorId, "ItemsDescriptors.txt", rObject);
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
			string descriptorName = GetAttributeName(descriptor);
			descriptorName = DLG_Convert("descriptor_" + descriptorName, "ItemsDescriptors.txt", rObject);
			SetFormatedText(nodeName2, descriptorName);
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