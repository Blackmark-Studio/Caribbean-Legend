// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Adelante, ¿qué deseas?","Justo estábamos hablando de eso. Debes haberlo olvidado...","Esta es la tercera vez hoy que hablas de alguna pregunta...","Escucha, esto es una tienda. La gente compra cosas aquí. ¡No me molestes!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabes, "+NPChar.name+", tal vez la próxima vez.","Correcto, lo he olvidado por alguna razón...","Sí, realmente es la tercera vez...","Hm, yo no...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = "Tienes mis bienes almacenados en tu almacén. Té, cacao y guayacán. Quiero recuperarlos.";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "Tienes mis bienes de Saint-Martin almacenados en tu almacén. El Barón Noel Forget me los dejó.";
                link.l2.go = "patria_goods_3";
			}
		break;
		
		case "patria_goods":
			dialog.text = "Así es, capitán, tengo sus mercancías. ¿Está seguro de que quiere llevárselas?";
			link.l1 = "Sí.";
			link.l1.go = "patria_goods_1";
			link.l2 = "Espera, necesito comprobar si hay suficiente espacio en la bodega primero.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "Perfecto. Ordenaré a los porteadores que lo entreguen en el muelle.";
			link.l1 = "¡Trato hecho!";
			link.l1.go = "patria_goods_2";
		break;
		
		case "patria_goods_2":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.Goods");
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE) + 500);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE) + 500);
			SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(pchar, GOOD_SANDAL) + 50);
		break;
		
		case "patria_goods_3":
			dialog.text = "Sí, exactamente. Lo guardo aquí por decreto del barón. ¿Estás seguro de que quieres llevártelos?";
			link.l1 = "Sí.";
			link.l1.go = "patria_goods_4";
			link.l2 = "Espera, primero necesito comprobar si hay suficiente espacio en la bodega.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "Perfecto. Ordenaré a los porteadores que lo entreguen en el muelle.";
			link.l1 = "¡Trato hecho!";
			link.l1.go = "patria_goods_5";
		break;
		
		case "patria_goods_5":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.GoodsSM"); // 17-add
			SetCharacterGoods(pchar, GOOD_TOBACCO, GetCargoGoods(pchar, GOOD_TOBACCO) + 500);
			SetCharacterGoods(pchar, GOOD_EBONY, GetCargoGoods(pchar, GOOD_EBONY) + 200);
			SetCharacterGoods(pchar, GOOD_MAHOGANY, GetCargoGoods(pchar, GOOD_MAHOGANY) + 250);
			SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + 200);
			SetCharacterGoods(pchar, GOOD_SILVER, GetCargoGoods(pchar, GOOD_SILVER) + 400);
			SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(pchar, GOOD_SHIPSILK) + 200);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
