// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Tam da bundan bahsediyorduk. Sanırım unuttunuz...","Bugün üçüncü kez bir soru sordunuz...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Evet, nedense unutmuşum...","Evet, gerçekten de üçüncü kez...","Hm, yapmayacağım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = " Mallarım senin ambarında duruyor. Çay, kakao ve guayak ağacı. Onları geri almak istiyorum. ";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "Sint Maarten'den gelen mallarım senin ambarında duruyor. Baron Noel Forgue onları bana bıraktı.";
                link.l2.go = "patria_goods_3";
			}
		break;
		
		case "patria_goods":
			dialog.text = "Haklısınız kaptan, mallarınız hazır. Onları gerçekten almak istediğinizden emin misiniz?";
			link.l1 = "Evet.";
			link.l1.go = "patria_goods_1";
			link.l2 = "Bir dakika, önce ambarımda yeterli yer olup olmadığını kontrol etmem gerek.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "Mükemmel. Hamallara bunu iskeleye götürmelerini emredeceğim.";
			link.l1 = "Anlaştık!";
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
			dialog.text = "Evet, tam olarak öyle. Onları burada baronun emriyle tutuyorum. Gerçekten almak istediğinizden emin misiniz?";
			link.l1 = "Evet.";
			link.l1.go = "patria_goods_4";
			link.l2 = "Bir dakika, önce ambarımda yeterli yer olup olmadığına bakmam gerek.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "Mükemmel. Hamallara bunu iskeleye götürmelerini emredeceğim.";
			link.l1 = "Anlaştık!";
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
