// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Az önce bundan bahsediyorduk. Herhalde unuttunuz...","Bugün üçüncü kez bir şey soruyorsun...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Hm, yapmam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Bana söyle, Juan ismi sana bir şey ifade ediyor mu?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "1654 Nisan'ında, Kaptan Miguel Dichoso komutasındaki bir fırkateyn limanınıza yanaştı, ardından da ortadan kayboldu. Bu isim size tanıdık geliyor mu? Belki sizden bir mal aldı ya da bir şey söyledi...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Aman kaptan, abartmayın! Bugün dükkânıma iki Juan uğradı, dün de bir tane gelmişti. Hepsini tek tek hatırlamamı mı bekliyorsunuz?";
			link.l1 = "Peki. Rahatsız ettiğim için kusura bakmayın...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Ah kaptan, o kadar çok fırkateyn ve kalyonun gelip geçtiğini gördüm ki bu süre zarfında, Miguel'ler ve Carlos'lar...";
			link.l1 = "Anladım. Yani, bana hiç yardımcı olamayacaksınız...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
