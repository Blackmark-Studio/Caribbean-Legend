// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm dedikodular "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Tam da bundan bahsediyorduk. Herhalde unuttun...","Bugün bu soruyu üçüncü kez gündeme getiriyorsun...","Aynı şeyleri papağan gibi tekrarlıyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Francois Gontier'i nerede bulabileceğimi biliyor musunuz, acaba?";
                link.l1.go = "Jamaica_ratP_1";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Dinle, bu kasabaya bir simyacı ya da hekim geldi mi? İtalyan, otuz yaşlarında, adı Gino Gvineili. Onun hakkında bir şey duydun mu?";
				link.l1.go = "guardoftruth";
			}
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("Hiçbir fikrim yok. O ismi daha önce hiç duymadım.","Bunu zaten sordun ve ben de sana cevap verdim.","Sana söyledim, bunu zaten sormuştun, Gontier.","Dinle, yürü git ve beni rahat bırak! Aklını tamamen mı kaçırdın?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Peki o zaman, aramaya devam edeceğim.","Hm, sanırım öyle...","Evet, doğru, ben de bunu sordum...","Üzgünüm, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Hayır, duymadım. Şifacılarımız ve hekimlerimiz var, ama o isimde biri yok.","Böylesine tuhaf bir ismi ilk kez duyuyorum. Hayır, bahsettiğiniz adam buraya hiç uğramadı.","Burada hiç simyacımız yok. Hekimlerimiz var, ama öyle tuhaf bir isme sahip olanlardan değil.");
			link.l1 = "Anladım. Ne yazık. Aramaya devam edeceğim!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
