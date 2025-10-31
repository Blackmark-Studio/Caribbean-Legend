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