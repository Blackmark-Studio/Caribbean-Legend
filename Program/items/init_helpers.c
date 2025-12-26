void InitMultiObjectCommon(
	ref    ref_id_idx,
	string sAttr,
	string component_id,
	string component_use,
	int    component_qty)
{
	ref rItem = FindItem_VT(ref_id_idx);
	rItem.component.(sAttr).id 	= component_id;
	rItem.component.(sAttr).use = component_use;
	rItem.component.(sAttr).qty = component_qty;
}

ref InitNewItem(ref newItem)
{
	int i;
	ref itm;
	object tempItems[TOTAL_ITEMS];

	for(i = 0; i < TOTAL_ITEMS; i++)
	{
		CopyAttributes(&tempItems[i], &Items[i]);
		// trace("Index " + i + " ID temp " + tempItems[i].id + " ID real " + Items[i].id);
	}
	
	ExpandItemsArray();
	
	ITEMS_QUANTITY++;
	
	DeleteAttribute(&Items[ITEMS_QUANTITY - 1], "");
	InitAddItem(ITEMS_QUANTITY - 1);
	
	makeref(itm,Items[ITEMS_QUANTITY - 1]);
	CopyAttributes(&itm, newItem);
	
	for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		DeleteAttribute(&Items[i], "");
		CopyAttributes(&Items[i], &tempItems[i - 1]);
		Items[i].index = i;
	}
	
	// belamour просто финальное логирование (пока оставить)
	// for(i = 0; i < TOTAL_ITEMS; i++)
	// {
	// 	trace("New object full loop" + i + " ID real " + Items[i].id);
	// }
	return itm;
}