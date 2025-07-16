// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Avanti, cosa desideri?","Ne stavamo giusto parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. La gente compra roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Mh, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = "Hai le mie merci immagazzinate nel tuo magazzino. Tè, cacao e lignum vitae. Voglio prenderli.";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "Hai le mie merci da Sint Maarten conservate nel tuo magazzino. Il Barone Noel Forgue me le ha lasciate.";
                link.l2.go = "patria_goods_3";
			}
		break;
		
		case "patria_goods":
			dialog.text = "Avete ragione, capitano, ho le vostre merci. Siete sicuro di volerle prendere?";
			link.l1 = "Sì.";
			link.l1.go = "patria_goods_1";
			link.l2 = "Aspetta, devo controllare prima se c'è abbastanza spazio nella stiva.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "Perfetto. Ordinerò ai portatori di consegnarlo al molo.";
			link.l1 = "Affare fatto!";
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
			dialog.text = "Sì, esattamente. Lo tengo qui per decreto del barone. Sei sicuro di volerli prendere?";
			link.l1 = "Sì.";
			link.l1.go = "patria_goods_4";
			link.l2 = "Aspetta, devo prima verificare se c'è abbastanza spazio nella stiva.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "Perfetto. Ordinerò ai facchini di consegnarlo al molo.";
			link.l1 = "Affare fatto!";
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
