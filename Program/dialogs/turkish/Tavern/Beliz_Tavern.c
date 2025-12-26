// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm söylentiler "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Biz de tam bundan bahsediyorduk. Herhalde unuttun...","Bugün üçüncü kez soruyorsun...","Aynı şeyi papağan gibi tekrar ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unutmuşum...","Evet, gerçekten üçüncü kez oldu...","Aye...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Dinle, bu kasabaya bir simyacı geldi mi, bir hekim? İtalyan, otuz yaşlarında, adı Gino Gvineili mi?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Dinle, Fergus Hooper adında bir avcı arıyorum. Burada yaşadığını duydum. Onu nerede bulabilirim?";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz"))
			{
				link.l1 = "Yaklaşık bir buçuk ay önce Jerome Sauvernier adında biri kasabanıza geldi. Onu hatırlıyor musunuz?";
				link.l1.go = "WildRose_Tavern_1";
			}
			//<-- Дикая Роза
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Hayır, duymadım. Şifacılarımız ve hekimlerimiz var, ama o isimde biri yok.","Böylesine garip bir ismi ilk kez duyuyorum. Hayır, sözünü ettiğiniz adam buraya hiç uğramadı.","Hiç simyacımız yok. Hekimlerimiz var, ama o isimde biri yok.");
			link.l1 = "Anladım. Ne yazık. Aramaya devam edeceğim!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Fergus mi? Sık sık buraya gelir. Ama dünden beri ormanda. Merak etme, bir haftaya döner; yine rom içer, deniz maceralarını ballandıra ballandıra anlatır. Kabul etmeliyim, gerçekten iyi bir avcıdır. Onun kadar yılan yakalayabilen birini tanımıyorum.";
			link.l1 = "Yılanlar mı? Hm. Onu bulmak için buraya ne zaman geri gelmeliyim?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "En az üç gün. Şunu da bil ki, buraya her zaman en erken akşam altıda gelir ve en geç onda çıkar.";
			link.l1 = "Neye benziyor? Onu daha önce hiç görmedim.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Sakallı, orta yaşlı, kahverengi bir ceket, şapka ve uzun çizmeler giyiyor.";
			link.l1 = "Merci! Bana çok yardımcı oldun, dostum. Görüşmek üzere!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
		
		//--> Дикая Роза
		case "WildRose_Tavern_1":
			dialog.text = "Uh... Sanırım öyle. Evet, o beyefendiyi hatırlıyorum. Şık giyimli değildi ama parası vardı.";
			link.l1 = "Senin meyhanende bir kavgada yaralandı.";
			link.l1.go = "WildRose_Tavern_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tavern_2":
			dialog.text = "Peki, ne olmuş yani? Burada neredeyse her gün kavga çıkar. Denizciler sarhoş olur, laflar havada uçuşur – sonra da kimse onları durduramaz. Tecrübeli birine benziyorsun – böyle şeyler seni şaşırtmıyordur herhalde?";
			link.l1 = "Hiç de değil. Şöyle ki, bu adam eski bir tanıdığım. Burada buluşmak üzere anlaştık ama biraz geciktim. Onu nerede bulabileceğimi söyleyebilir misiniz?";
			link.l1.go = "WildRose_Tavern_3";
		break;

		case "WildRose_Tavern_3":
			dialog.text = "Neden söylemeyeyim ki size, efendim? Dediğim gibi, yeterince parası vardı – bu yüzden liman idaresinin yakınında bir ev kiraladı. Kırmızı çatılı, dikkat çeken bir yer. Orada saklanıyor, neredeyse hiç dışarı çıkmıyor, bacağını iyileştirmeye çalışıyor. Ara sıra buraya bir içki için uğruyor. Ama hiçbir zaman kesin değil – bazı günler gelir, bazı günler uğramaz.";
			link.l1 = "O halde evine gidip kendisiyle konuşurum. Bilgi için teşekkürler. Hoşça kal.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_tavern");
		break;
		//<-- Дикая Роза

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
