// Рисование пушек по «сетке» для экрана орудий

void XI_CannonSetGrid(int qty, ref startOffset, ref inRowQty, ref size, ref offset, ref rowsNum, ref xOffset, ref yOffset)
{
	int fullWidth = 750; // ширина картинки борта
	if (qty < 12) inRowQty = qty;
	else if (qty <= 24) inRowQty = ceil(qty * 0.5);
	else if (qty <= 50) inRowQty = int(qty / 3.0);
	else if (qty > 50) inRowQty = 17;
	else inRowQty = ceil(qty / 3.0) + ceil(qty*0.02);

	size = ceil(fullWidth / (inRowQty) * 0.66);
	rowsNum = func_min(3, ceil(qty/float(inRowQty)));
	switch (rowsNum)
	{
		case 1: 
			size = func_min(size, 82);
			xOffset = 0;
			yOffset = 0;
		break;
		case 2:
			yOffset = int(func_max(0, size-48) * 0.1);
			xOffset = int(func_max(0, size-48) * 0.8);
			size = func_min(size, 48);
		break;
		case 3:
			yOffset = int(func_max(0, size-36) * 0.1);
			xOffset = int(func_max(0, size-36) * 0.8);
			size = func_min(size, 36);
		break;
	}
	offset = int(size * 0.3);
	startOffset = ceil((fullWidth - (size+offset+xOffset)*inRowQty) * 0.5);
	if (rowsNum == 2) startOffset += int(offset * 0.5);
}

void XI_DrawCannonToBort(string bortNodeName, string bortName, int forceQty = -1)
{
	int x1,x2,y1,y2, size, offset, cannonsInRow, startOffset, rowsNum, xOffset, yOffset;
	int index = 1;
	int rowIndex = 0;
	GetNodePosition(bortNodeName, &x1,&y1,&x2,&y2);

	aref borts = xi_refCharacter.Ship.Cannons.Borts$aref;
	aref bort = touchattr(borts.(bortName).damages);
	object tempBort;
	if (forceQty > 0)
	{
		for (int i = 0; i < forceQty; i++) { tempBort.(kstring("c"+i)) = 0.0; }
	}
	else CopyAttributes(&tempBort, &bort);
	
	int cannonsLeft = @tempBort;
	if (cannonsLeft < 1) return;

	SmartSort(&tempBort, "", "float", true, 0, "c");
	if (bortNodeName == "BORT_LAYOUT_F" || bortNodeName == "BORT_LAYOUT_B")
	{
		int bonusOffsetsX[3] = bortNodeName == "BORT_LAYOUT_F" ? {2,0,0,0} : {-3,0,0,0};
		int bonusOffsetsY[3] = bortNodeName == "BORT_LAYOUT_F" ? {0,0,0,0} : {-10,-8,4,0};
		xOffset = 0;
		yOffset = 0;
		if (cannonsLeft < 3) 
		{
			x2 -= 126 + bonusOffsetsX[rowIndex];
			y2 -= 114;
			size = 68;
			offset = 34;
		}
		else if (cannonsLeft < 5)
		{
			if (bortNodeName == "BORT_LAYOUT_B") bonusOffsetsY = {30,0,0,0};
			x2 -= 123 + bonusOffsetsX[rowIndex];
			y2 -= 78  + bonusOffsetsY[rowIndex];
			size = 52;
			offset = 26;
		}
		else 
		{
			if (bortNodeName == "BORT_LAYOUT_B") bonusOffsetsY = {-10,-20,0,0};
			else bonusOffsetsY = {14,10,-24,0};
			x2 -= 128 + bonusOffsetsX[rowIndex];
			y2 -= 54 + bonusOffsetsY[rowIndex];
			size = 48;
			offset = 36;
		}

		for (string cannonName, aref arCannon: tempBort)
		{
			string cannonNode = bortName +"_" + cannonName;
			if ("tempCannons." + cannonNode !in &GameInterface)
			{
				touchattr(GameInterface.tempCannons.(cannonNode));
				XI_MakeNode("", "PICTURE", cannonNode, 110);
			}
			string picname = tempBort.(cannonName)$float(0.0) < 1.0 ? "cannon" : "empty_port";
			SetNewGroupPicture(cannonNode, "CANNONS_MANAGEMENT",picname);

			SetNodePosition(cannonNode, x2-size+xOffset, y2-size+yOffset, x2+xOffset, y2+yOffset);
			xOffset += size + offset;
			if (xOffset == (size+offset) * 2) 
			{
				rowIndex++;
				xOffset = 0;
				yOffset -= size + offset + bonusOffsetsY[rowIndex];
			}
		}
			return;
	}

	// bool inverse = (bortNodeName == "BORT_LAYOUT_R");
	bool inverse = false;

	x2 -= 11;
	XI_CannonSetGrid(cannonsLeft, &startOffset, &cannonsInRow, &size, &offset, &rowsNum, &xOffset, &yOffset);
	int shift = int((size+offset)*0.5) * (inverse ? -1 : 1);
	int xStart = inverse ? x1 + startOffset : x2 - startOffset;
	int yStart = y2-(y2-y1)*0.4 + size*rowsNum*0.6 - 4;
	bool even = false;
	int bonusCannon[4] = {0,0,0,0};
	if (rowsNum == 3 && cannonsLeft % 3.0 == 0) even = true;
	else if (rowsNum == 3 && cannonsLeft % 3.0 >= 2.0) bonusCannon = {1,0,1,0};
	else if (rowsNum == 3 && cannonsLeft % 3.0 >= 1.0) bonusCannon = {0,1,0,0};

	if (bonusCannon[rowIndex] > 0) xStart += shift; 

	for (string cannonName, aref arCannon: tempBort)
	{
		string cannonNode = bortName +"_" + cannonName;
		if ("tempCannons." + cannonNode !in &GameInterface)
		{
			touchattr(GameInterface.tempCannons.(cannonNode));
			XI_MakeNode("", "PICTURE", cannonNode, 110);
		}
		string picname = tempBort.(cannonName)$float(0.0) < 1.0 ? "cannon" : "empty_port";
		SetNewGroupPicture(cannonNode, "CANNONS_MANAGEMENT",picname);
		
		if (inverse) SetNodePosition(cannonNode, xStart, yStart-size ,xStart+size, yStart);
		else SetNodePosition(cannonNode, xStart, yStart-size ,xStart-size, yStart);

		if (index == cannonsInRow + bonusCannon[rowIndex])
		{
			xStart = inverse ? x1 + startOffset : x2 - startOffset;
			yStart -= (offset + size + yOffset);
			index = 0;
			rowIndex ++;
			if (bonusCannon[rowIndex] > 0) xStart += shift; 
			else if (rowsNum == 2) xStart += (cannonsLeft > cannonsInRow ? shift : -shift); 
			else if (even && rowIndex == 1) xStart += shift;
		}
		else
		{
			xStart -= inverse ? -(offset + size + xOffset) : (offset + size + xOffset);
		}

		index++;
		cannonsLeft--;
	}
}
