// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm söylentiler "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Tam da bundan bahsediyorduk. Herhalde unuttun...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Aynı şeyi papağan gibi tekrar ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+" , belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Şehrinizde François Gontier adında bir korsan olduğunu duydum. Onu nerede bulabileceğimi biliyor musunuz?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Bakın, Bertrand Pinette adında bir adamı arıyorum, onu duydunuz mu? Kısa süre önce Panama'ya geldi. Peruklu, heybetli bir beyefendi. Burada bulunmuş olabilir...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Evet, burada öyle bir adam vardı. Karanlık köşelerde dolaşıyordu... Sonra birkaç arkadaşı geldi, tam bir haydut takımı gibiydiler. Onlarla birlikte kasabadan ayrıldı.","Bunu zaten sordun ve ben de sana cevap verdim.","Sana söyledim, bunu Gontier hakkında zaten sormuştun.","Dinle, yürü git ve beni rahat bırak! Aklını tamamen mı kaçırdın?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ve nereye gitti, biliyor musun?","Hm, sanırım öyle...","Evet, doğru, bunu ben sordum...","Üzgünüm, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Buradan yürüyerek çıkmanın tek yolu var - Portobello. O da oraya doğru kaçtı. Yani onu orada ara.";
			link.l1 = "Teşekkür ederim, çok yardımcı oldunuz!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "Bertrand Pinette mi? Fransız mı? Hiç duymadım. Yok kaptan, buralarda Fransız kimseyi uzun zamandır görmedik.";
			link.l1 = "Ne yazık... Emin misiniz? O, Don Carlos de Milyar adında önemli bir hidalgo'nun arkadaşı. Buraya birlikte gelmeleri gerekiyordu.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Milyar Bey mi? O beyefendi bir yıl önce Panama'yı ziyaret etti. Aslında Don Carlos de Milyar Portobello'da yaşıyor. Kendisi yerel valinin yakın dostudur.";
			link.l1 = "Anladım. Ormanda vakit ve nefes harcamaya hiç gerek yokmuş. Teşekkürler, dostum.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
